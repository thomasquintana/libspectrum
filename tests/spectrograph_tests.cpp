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

/** @file spectrograph_tests.cpp
 *  @brief Tests the spectrograph interface.
 *
 *  @author Thomas Quintana (quintana.thomas@gmail.com)
 *  @bug No known bugs.
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <gtest/gtest.h>

#include "../src/spectrograph.h"

/* Generate a 1Khz sine wave @ 8Khz. */
#define SINE_WAVE_GEN(N) ((short)(16384 * sin((2 * M_PI * N * 1000) / 8000)))

float SINE_WAVE_SPECTRUM[] = {
   0.61954495,   1.12492855,   2.42907652,   4.15571902,
   6.06182028,   8.05515637,  10.12603837,  12.30362502,
  14.63940728,  17.20615141,  20.10788745,  23.50533011,
  27.67780171,  33.20623799,  41.79307197,  87.33182255,
  93.25104276,  87.33181032,  41.79771645,  33.22506646,
  27.72558696,  23.60269014,  20.28211196,  17.49225161,
  15.08132192,  12.95533479,  11.05186107,   9.32724819,
   7.74974728,   6.2955359 ,   4.94628127,   3.68757754,
   2.50790562,   1.39791868,   0.34993869,  -0.64240671,
  -1.5844508 ,  -2.48068704,  -3.33492015,  -4.15038258,
  -4.92982648,  -5.67560028,  -6.38972175,  -7.07397378,
  -7.73011351,  -8.36065801,  -8.97458334,  -5.49305719,
  -9.52947353,  -6.15512849, -11.11342815, -11.56410521,
  -11.99920997, -12.40875895, -12.79006799, -13.14145894,
  -13.46143262, -13.74850397, -14.00118499, -14.21801563,
  -14.39761459, -14.5387386 , -14.64034268, -14.70163519, 
  -14.72212203
};

TEST(spectrograph_tests, spectrograph_sine_wave_test) {
  float *memory = (float*)malloc(sizeof(float) * 8000 * 2);
  if (memory) {
    float *sine_wave_buffer = memory;
    float *output_buffer = &memory[8000];
    for (unsigned int idx = 0; idx < 8000; idx++) {
      sine_wave_buffer[idx] = (float)SINE_WAVE_GEN(idx);
    }
    spectrograph_t *spectrograph = spectrograph_create();
    ASSERT_FALSE(spectrograph == NULL);
    spectrograph_transform(spectrograph, sine_wave_buffer, output_buffer);
    for (unsigned int idx = 0; idx < 64 + 1; idx++) {
      ASSERT_FALSE(fabs(output_buffer[idx] - SINE_WAVE_SPECTRUM[idx]) > 0.05);
    }
    spectrograph_destroy(spectrograph);
  }
  free(memory);
}