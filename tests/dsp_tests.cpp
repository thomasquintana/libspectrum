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

/** @file dsp_tests.cpp
 *  @brief Tests the dsp interface.
 *
 *  @author Thomas Quintana (quintana.thomas@gmail.com)
 *  @bug No known bugs.
 */

#include <cstdio>
#include <cstdlib>
#include <gtest/gtest.h>

#include "../src/dsp.h"

TEST(dsp_tests, dsp_vector_add_64) {
  /* Allocate properly aligned memory for the test vectors. */
  float *memory = (float*)aligned_alloc(32, sizeof(float) * 64 * 3);
  if (memory) {
    float *a = memory;
    float *b = &memory[64];
    float *c = &memory[128];
    /* Initialize the memory. */
    for (unsigned int idx = 0; idx < 64; idx++) {
      a[idx] = 1.0;
      b[idx] = 1.0;
    }
    /* Add both vectors. */
    dsp_vec_add_64(a, b, c);
    /* Check the results. */
    for (unsigned int idx = 0; idx < 64; idx++) {
      ASSERT_EQ(c[idx], 2.0);
    }
  }
  free(memory);
}

TEST(dsp_tests, dsp_vector_copy_16) {
  /* Allocate properly aligned memory for the test vectors. */
  float *memory = (float*)aligned_alloc(32, sizeof(float) * 64 * 2);
  if (memory) {
    float *a = memory;
    float *b = &memory[64];
    /* Initialize the memory. */
    for (unsigned int idx = 0; idx < 64; idx++) {
      a[idx] = (double)idx;
    }
    /* Add both vectors. */
    dsp_vec_copy_16(a, b);
    dsp_vec_copy_16(&a[16], &b[16]);
    dsp_vec_copy_16(&a[32], &b[32]);
    dsp_vec_copy_16(&a[48], &b[48]);
    /* Check the results. */
    for (unsigned int idx = 0; idx < 64; idx++) {
      ASSERT_EQ(b[idx], a[idx]);
    }
  }
  free(memory);
}

TEST(dsp_tests, dsp_vector_multiply_64) {
  /* Allocate properly aligned memory for the test vectors. */
  float *memory = (float*)aligned_alloc(32, sizeof(float) * 64 * 3);
  if (memory) {
    float *a = memory;
    float *b = &memory[64];
    float *c = &memory[128];
    /* Initialize the memory. */
    for (unsigned int idx = 0; idx < 64; idx++) {
      a[idx] = 2.0;
      b[idx] = 3.0;
    }
    /* Multiply both vectors. */
    dsp_vec_mul_64(a, b, c);
    /* Check the results. */
    for (unsigned int idx = 0; idx < 64; idx++) {
      ASSERT_EQ(c[idx], 6.0);
    }
  }
  free(memory);
}

TEST(dsp_tests, dsp_vector_sqrt_64) {
  /* Allocate properly aligned memory for the test vector. */
  float *memory = (float*)aligned_alloc(32, sizeof(float) * 64 * 2);
  if (memory) {
    float *a = memory;
    float *b = &memory[64];
    /* Initialize the memory. */
    for (unsigned int idx = 0; idx < 64; idx++) {
      a[idx] = 9.0;
    }
    /* Square vector a. */
    dsp_vec_sqrt_64(a, b);
    /* Check the results. */
    for (unsigned int idx = 0; idx < 64; idx++) {
      ASSERT_EQ(b[idx], 3.0);
    }
  }
  free(memory);
}

TEST(dsp_tests, dsp_vector_square_64) {
  /* Allocate properly aligned memory for the test vector. */
  float *memory = (float*)aligned_alloc(32, sizeof(float) * 64 * 2);
  if (memory) {
    float *a = memory;
    float *b = &memory[64];
    /* Initialize the memory. */
    for (unsigned int idx = 0; idx < 64; idx++) {
      a[idx] = 3.0;
    }
    /* Square vector a. */
    dsp_vec_square_64(a, b);
    /* Check the results. */
    for (unsigned int idx = 0; idx < 64; idx++) {
      ASSERT_EQ(b[idx], 9.0);
    }
  }
  free(memory);
}
