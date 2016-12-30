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

/** @file dsp.h
 *  @brief Public type and function definitions used for
 *         digital signal processing.
 *
 *  @author Thomas Quintana (quintana.thomas@gmail.com)
 *  @bug No known bugs.
 */

#ifndef DSP_H
#define DSP_H

/**
 * Compute the Hanning Window function.
 *
 * @param t The index at time t.
 * @param l The number of samples per frame.
 */
#define dsp_hann_wnd(t, l) (0.5 * (1 - cos((2 * M_PI * (t)) / ((l) - 1))))

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 */
void dsp_vec_add_64(float *a, float *b, float *c);

/**
 *
 */
void dsp_vec_copy_16(float *a, float *b);

/**
 *
 */
void dsp_vec_mul_64(float *a, float *b, float *c);

/**
 *
 */
void dsp_vec_sqrt_64(float *a, float *b);

/**
 *
 */
void dsp_vec_square_64(float *a, float *b);

#ifdef __cplusplus
}
#endif

#endif /* DSP_H */