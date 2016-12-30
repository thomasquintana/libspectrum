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

/** @file vector.h
 *  @brief Public function, macros and type definitions used
 *         for manipulating floating point vectors using SIMD
 *         instructions on Intel processors.
 *
 *  @author Thomas Quintana (quintana.thomas@gmail.com)
 *  @bug No known bugs.
 */

#ifndef VECTOR_H
#define VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Add two vectors of 64 floats.
 *
 * @param a The first term.
 * @param b The second term.
 * @param c The destination for the sum of a + b.
 *
 * @return Void
 */
void vec_add_64(float *a, float *b, float *c);

/**
 * Copy a vector of 16 floats.
 *
 * @param a The source.
 * @param b The destination.
 *
 * @return Void
 */
void vec_copy_16(float *a, float *b);

/**
 * Multiply two vectors of 64 floats.
 *
 * @param a The first term.
 * @param b The second term.
 * @param c The destination for the product of a * b.
 *
 * @return Void
 */
void vec_mul_64(float *a, float *b, float *c);

/**
 * Compute the square root of each float in a vector of 64 floats.
 *
 * @param a The source.
 * @param b The destination for the square roots.
 */
void vec_sqrt_64(float *a, float *b);

/**
 * Compute the square of each float in a vector of 64 floats.
 *
 * @param a The source.
 * @param b The destination for the squares.
 */
void vec_square_64(float *a, float *b);

#ifdef __cplusplus
}
#endif

#endif /* VECTOR_H */