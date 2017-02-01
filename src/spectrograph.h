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

/** @file spectrograph.h
 *  @brief Public functions, macros and type definitions used for
 *         generating spectrograms.
 *
 *  @author Thomas Quintana (quintana.thomas@gmail.com)
 *  @bug No known bugs.
 */

#ifndef SPECTROGRAPH_H
#define SPECTROGRAPH_H

#include <math.h>
#include <stdbool.h>

/**
 * Compute the output length of a spectrograph.
 *
 * @param n_samples The number of samples per frame.
 *
 * @return The spectrograph output length.
 */
#define spectrograph_output_len(n_samples) ((int)(floor((n_samples) / 2) + 1))

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A spectrograph is an instrument used to create spectrograms of input
 * signals.
 *
 * The spectrograms produced are a visual representations of the spectrum
 * of frequencies in the signal as it varies with time.
 */
typedef struct spectrograph spectrograph_t;

/**
 * Create a new spectrograph.
 *
 * @return A pointer to a new spectrograph.
 */
spectrograph_t* spectrograph_create(void);

/**
 * Release the resources allocated by a spectrograph.
 *
 * @return Void.
 */
void            spectrograph_destroy(spectrograph_t *sg);

/**
 * Generate a spectrogram fragment for one frame of the input signal.
 *
 * @param sg A spectrograph.
 *
 * @param input A pointer to an array of floats of length 128. 
 *
 * @param output A pointer to an array of floats which will store the resulting
 *               spectrogram fragment. The output will be of length 64 + 1.
 *
 * @return Void.
 */
bool             spectrograph_transform(spectrograph_t *sg, float *input,
                                        float *output);

#ifdef __cplusplus
}
#endif

#endif /* SPECTROGRAPH_H */
