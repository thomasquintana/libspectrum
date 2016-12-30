/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/** @file spectrograph.c
 *  @brief Implements the spectrograph interface.
 *
 *  @author Thomas Quintana (quintana.thomas@gmail.com)
 *  @bug No known bugs.
 */

/* C Run-time */
#include <stdlib.h>
#include <string.h>

/* Intel Integrated Performance Primitives */
#include "ipp.h"

/* Spectrograph Run-time */
#include "dsp.h"
#include "spectrograph.h"
#include "vector.h"

typedef struct spectrograph {
  float              *constant_buffers;
  Ipp32fc            *io_buffers;
  Ipp8u              *fft_buffers;
  float              *work_buffers;
  /* Constants */
  float              *hann_wnd;
  float              *power_spec_coeff;
  /* FFT */
  Ipp32fc            *fft_input_buffer;
  Ipp32fc            *fft_output_buffer;
  IppsFFTSpec_C_32fc *fft_spec;
  Ipp8u              *fft_spec_buffer;
  Ipp8u              *fft_work_buffer;
} spectrograph_t;

spectrograph_t* spectrograph_create(void) {
  spectrograph_t *sg = (spectrograph_t*)malloc(sizeof(spectrograph_t));
  if (sg == NULL) {
    return NULL;
  }
  /* Initialize the FFT run-time. */
  Ipp32fc *io_buffers = ippsMalloc_32fc(128 * 2);
  if (io_buffers == NULL) {
    free(sg);
    return NULL;
  }
  sg->io_buffers = io_buffers;
  sg->fft_input_buffer = io_buffers;
  sg->fft_output_buffer = &io_buffers[128];
  int init_buff_len, spec_buff_len, work_buff_len;
  IppStatus status = ippsFFTGetSize_C_32fc(7, IPP_FFT_NODIV_BY_ANY,
    ippAlgHintNone, &spec_buff_len, &init_buff_len, &work_buff_len);
  if (status != ippStsNoErr) {
    ippFree(io_buffers);
    free(sg);
    return NULL;
  }
  Ipp8u *fft_buffers = ippsMalloc_8u(spec_buff_len + work_buff_len);
  if (fft_buffers == NULL) {
    ippFree(io_buffers);
    free(sg);
    return NULL;
  }
  sg->fft_buffers = fft_buffers;
  sg->fft_spec_buffer = fft_buffers;
  sg->fft_work_buffer = &fft_buffers[spec_buff_len];
  Ipp8u *init_buffer = NULL;
  if (init_buff_len > 0) {
    init_buffer = ippsMalloc_8u(init_buff_len);
    if (init_buffer == NULL) {
      ippFree(io_buffers);
      ippFree(fft_buffers);
      free(sg);
      return NULL;
    }
  }
  status = ippsFFTInit_C_32fc(&sg->fft_spec, 7, IPP_FFT_NODIV_BY_ANY,
    ippAlgHintNone, sg->fft_spec_buffer, init_buffer);
  if (init_buffer != NULL) {
    ippFree(init_buffer);
  }
  if (status != ippStsNoErr) {
    ippFree(io_buffers);
    ippFree(fft_buffers);
    free(sg);
    return NULL;
  }
  /* Initialize the spectrograph run-time. */
  unsigned int constants_buffer_size = sizeof(float) * 128 * 2;
  float *constant_buffers = (float*)aligned_alloc(32, constants_buffer_size);
  if (constant_buffers == NULL) {
    ippFree(io_buffers);
    ippFree(fft_buffers);
    free(sg);
    return NULL;
  }
  sg->constant_buffers = constant_buffers;
  sg->hann_wnd = constant_buffers;
  sg->power_spec_coeff = &constant_buffers[128];
  for (unsigned int idx = 0; idx < 128; idx++) {
    sg->hann_wnd[idx] = hann_func(idx, 128);
    sg->power_spec_coeff[idx] = 0.0078125f;
  }
  unsigned int work_buffer_size = sizeof(float) * 128 * 3;
  float *work_buffers = (float*)aligned_alloc(32, work_buffer_size);
  if (work_buffers == NULL) {
    ippFree(io_buffers);
    ippFree(fft_buffers);
    free(constant_buffers);
    free(sg);
    return NULL;
  }
  sg->work_buffers = work_buffers;
  return sg;
}

void spectrograph_destroy(spectrograph_t *sg) {
  ippFree(sg->io_buffers);
  ippFree(sg->fft_buffers);
  free(sg->constant_buffers);
  free(sg->work_buffers);
  free(sg);
}

bool spectrograph_transform(spectrograph_t *sg, float *input, float *output) {
  float *buffer = sg->work_buffers;
  vec_copy_16(input, buffer);
  vec_copy_16(&input[16], &buffer[16]);
  vec_copy_16(&input[32], &buffer[32]);
  vec_copy_16(&input[48], &buffer[48]);
  vec_copy_16(&input[64], &buffer[64]);
  vec_copy_16(&input[80], &buffer[80]);
  vec_copy_16(&input[96], &buffer[96]);
  vec_copy_16(&input[112], &buffer[112]);
  /* Apply the hanning window to the input frame. */
  vec_mul_64(sg->hann_wnd, buffer, buffer);
  vec_mul_64(&sg->hann_wnd[64], &buffer[64], &buffer[64]);
  /* Perform the FFT */
  memset(sg->fft_input_buffer, 0, sizeof(Ipp32fc) * 128);
  for (unsigned int idx = 0; idx < 128; idx++) {
    sg->fft_input_buffer[idx].re = buffer[idx];
  }
  IppStatus status = ippsFFTFwd_CToC_32fc(sg->fft_input_buffer,
    sg->fft_output_buffer, sg->fft_spec, sg->fft_work_buffer);
  if (status != ippStsNoErr) {
    return false;
  }
  float *real = &buffer[128];
  float *imag = &buffer[200];
  for (unsigned int idx = 0; idx < 64 + 1; idx++) {
    real[idx] = sg->fft_output_buffer[idx].re;
    imag[idx] = sg->fft_output_buffer[idx].im;
  }
  /* Compute the magnitude spectrum. */
  vec_square_64(real, real);
  vec_square_64(imag, imag);
  vec_add_64(real, imag, buffer);
  vec_sqrt_64(buffer, buffer);
  /* Compute the power spectrum. */
  vec_square_64(buffer, buffer);
  vec_mul_64(buffer, sg->power_spec_coeff, buffer);
  /* Handle the final sample. */
  buffer[64] = sqrtf(real[64] * real[64] + imag[64] * imag[64]);
  buffer[64] *= buffer[64];
  buffer[64] *= 0.0078125f;
  /* Compute the log power spectrum. */
  for (unsigned int idx = 0; idx < 64 + 1; idx++) {
    if (buffer[idx] < 1e-30) {
      buffer[idx] = 1e-30;
    }
    output[idx] = 10 * log10f(buffer[idx]);
  }
  return true;
}
