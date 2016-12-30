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

/** @file vector.c
 *  @brief Implements the vector interface.
 *
 *  @author Thomas Quintana (quintana.thomas@gmail.com)
 *  @bug No known bugs.
 */

#include <complex.h>

#include "vector.h"

inline void vec_add_64(float *a, float *b, float *c) {
  __asm__(
    "vmovaps (%0), %%ymm0\n\t"
    "vmovaps (%1), %%ymm1\n\t"
    "vaddps %%ymm0, %%ymm1, %%ymm1\n\t"
    "vmovaps %%ymm1, (%2)\n\t"
    "vmovaps 32(%0), %%ymm2\n\t"
    "vmovaps 32(%1), %%ymm3\n\t"
    "vaddps %%ymm2, %%ymm3, %%ymm3\n\t"
    "vmovaps %%ymm3, 32(%2)\n\t"
    "vmovaps 64(%0), %%ymm4\n\t"
    "vmovaps 64(%1), %%ymm5\n\t"
    "vaddps %%ymm4, %%ymm5, %%ymm5\n\t"
    "vmovaps %%ymm5, 64(%2)\n\t"
    "vmovaps 96(%0), %%ymm6\n\t"
    "vmovaps 96(%1), %%ymm7\n\t"
    "vaddps %%ymm6, %%ymm7, %%ymm7\n\t"
    "vmovaps %%ymm7, 96(%2)\n\t"
    "vmovaps 128(%0), %%ymm8\n\t"
    "vmovaps 128(%1), %%ymm9\n\t"
    "vaddps %%ymm8, %%ymm9, %%ymm9\n\t"
    "vmovaps %%ymm9, 128(%2)\n\t"
    "vmovaps 160(%0), %%ymm10\n\t"
    "vmovaps 160(%1), %%ymm11\n\t"
    "vaddps %%ymm10, %%ymm11, %%ymm11\n\t"
    "vmovaps %%ymm11, 160(%2)\n\t"
    "vmovaps 192(%0), %%ymm12\n\t"
    "vmovaps 192(%1), %%ymm13\n\t"
    "vaddps %%ymm12, %%ymm13, %%ymm13\n\t"
    "vmovaps %%ymm13, 192(%2)\n\t"
    "vmovaps 224(%0), %%ymm14\n\t"
    "vmovaps 224(%1), %%ymm15\n\t"
    "vaddps %%ymm14, %%ymm15, %%ymm15\n\t"
    "vmovaps %%ymm15, 224(%2)"
    : /* outputs */
    : "g"(a), "g"(b), "g"(c)
    :"ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7",
     "ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14",
     "ymm15"
  );
}

inline void vec_copy_16(float *a, float *b) {
  __asm__(
    "prefetchnta 64(%0)\n\t"
    "movq (%0), %%mm0\n\t"
    "movq 8(%0), %%mm1\n\t"
    "movq 16(%0), %%mm2\n\t"
    "movq 24(%0), %%mm3\n\t"
    "movq 32(%0), %%mm4\n\t"
    "movq 40(%0), %%mm5\n\t"
    "movq 48(%0), %%mm6\n\t"
    "movq 56(%0), %%mm7\n\t"
    "movntq %%mm0, (%1)\n\t"
    "movntq %%mm1, 8(%1)\n\t"
    "movntq %%mm2, 16(%1)\n\t"
    "movntq %%mm3, 24(%1)\n\t"
    "movntq %%mm4, 32(%1)\n\t"
    "movntq %%mm5, 40(%1)\n\t"
    "movntq %%mm6, 48(%1)\n\t"
    "movntq %%mm7, 56(%1)"
    : /* outputs */
    : "g"(a), "g"(b)
    :"mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7"
  );
}

inline void vec_mul_64(float *a, float *b, float *c) {
  __asm__(
    "vmovaps (%0), %%ymm0\n\t"
    "vmovaps (%1), %%ymm1\n\t"
    "vmulps %%ymm0, %%ymm1, %%ymm1\n\t"
    "vmovaps %%ymm1, (%2)\n\t"
    "vmovaps 32(%0), %%ymm2\n\t"
    "vmovaps 32(%1), %%ymm3\n\t"
    "vmulps %%ymm2, %%ymm3, %%ymm3\n\t"
    "vmovaps %%ymm3, 32(%2)\n\t"
    "vmovaps 64(%0), %%ymm4\n\t"
    "vmovaps 64(%1), %%ymm5\n\t"
    "vmulps %%ymm4, %%ymm5, %%ymm5\n\t"
    "vmovaps %%ymm5, 64(%2)\n\t"
    "vmovaps 96(%0), %%ymm6\n\t"
    "vmovaps 96(%1), %%ymm7\n\t"
    "vmulps %%ymm6, %%ymm7, %%ymm7\n\t"
    "vmovaps %%ymm7, 96(%2)\n\t"
    "vmovaps 128(%0), %%ymm8\n\t"
    "vmovaps 128(%1), %%ymm9\n\t"
    "vmulps %%ymm8, %%ymm9, %%ymm9\n\t"
    "vmovaps %%ymm9, 128(%2)\n\t"
    "vmovaps 160(%0), %%ymm10\n\t"
    "vmovaps 160(%1), %%ymm11\n\t"
    "vmulps %%ymm10, %%ymm11, %%ymm11\n\t"
    "vmovaps %%ymm11, 160(%2)\n\t"
    "vmovaps 192(%0), %%ymm12\n\t"
    "vmovaps 192(%1), %%ymm13\n\t"
    "vmulps %%ymm12, %%ymm13, %%ymm13\n\t"
    "vmovaps %%ymm13, 192(%2)\n\t"
    "vmovaps 224(%0), %%ymm14\n\t"
    "vmovaps 224(%1), %%ymm15\n\t"
    "vmulps %%ymm14, %%ymm15, %%ymm15\n\t"
    "vmovaps %%ymm15, 224(%2)"
    : /* outputs */
    : "g"(a), "g"(b), "g"(c)
    :"ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7",
     "ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14",
     "ymm15"
  );
}

inline void vec_sqrt_64(float *a, float *b) {
  __asm__(
    "vmovaps (%0), %%ymm0\n\t"
    "vsqrtps %%ymm0, %%ymm1\n\t"
    "vmovaps %%ymm1, (%1)\n\t"
    "vmovaps 32(%0), %%ymm2\n\t"
    "vsqrtps %%ymm2, %%ymm3\n\t"
    "vmovaps %%ymm3, 32(%1)\n\t"
    "vmovaps 64(%0), %%ymm4\n\t"
    "vsqrtps %%ymm4, %%ymm5\n\t"
    "vmovaps %%ymm5, 64(%1)\n\t"
    "vmovaps 96(%0), %%ymm6\n\t"
    "vsqrtps %%ymm6, %%ymm7\n\t"
    "vmovaps %%ymm7, 96(%1)\n\t"
    "vmovaps 128(%0), %%ymm8\n\t"
    "vsqrtps %%ymm8, %%ymm9\n\t"
    "vmovaps %%ymm9, 128(%1)\n\t"
    "vmovaps 160(%0), %%ymm10\n\t"
    "vsqrtps %%ymm10, %%ymm11\n\t"
    "vmovaps %%ymm11, 160(%1)\n\t"
    "vmovaps 192(%0), %%ymm12\n\t"
    "vsqrtps %%ymm12, %%ymm13\n\t"
    "vmovaps %%ymm13, 192(%1)\n\t"
    "vmovaps 224(%0), %%ymm14\n\t"
    "vsqrtps %%ymm14, %%ymm15\n\t"
    "vmovaps %%ymm15, 224(%1)"
    : /* outputs */
    : "g"(a), "g"(b)
    :"ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7",
     "ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14",
     "ymm15"
  );
}

inline void vec_square_64(float *a, float *b) {
  __asm__(
    "vmovaps (%0), %%ymm0\n\t"
    "vmovaps (%0), %%ymm1\n\t"
    "vmulps %%ymm0, %%ymm1, %%ymm1\n\t"
    "vmovaps %%ymm1, (%1)\n\t"
    "vmovaps 32(%0), %%ymm2\n\t"
    "vmovaps 32(%0), %%ymm3\n\t"
    "vmulps %%ymm2, %%ymm3, %%ymm3\n\t"
    "vmovaps %%ymm3, 32(%1)\n\t"
    "vmovaps 64(%0), %%ymm4\n\t"
    "vmovaps 64(%0), %%ymm5\n\t"
    "vmulps %%ymm4, %%ymm5, %%ymm5\n\t"
    "vmovaps %%ymm5, 64(%1)\n\t"
    "vmovaps 96(%0), %%ymm6\n\t"
    "vmovaps 96(%0), %%ymm7\n\t"
    "vmulps %%ymm6, %%ymm7, %%ymm7\n\t"
    "vmovaps %%ymm7, 96(%1)\n\t"
    "vmovaps 128(%0), %%ymm8\n\t"
    "vmovaps 128(%0), %%ymm9\n\t"
    "vmulps %%ymm8, %%ymm9, %%ymm9\n\t"
    "vmovaps %%ymm9, 128(%1)\n\t"
    "vmovaps 160(%0), %%ymm10\n\t"
    "vmovaps 160(%0), %%ymm11\n\t"
    "vmulps %%ymm10, %%ymm11, %%ymm11\n\t"
    "vmovaps %%ymm11, 160(%1)\n\t"
    "vmovaps 192(%0), %%ymm12\n\t"
    "vmovaps 192(%0), %%ymm13\n\t"
    "vmulps %%ymm12, %%ymm13, %%ymm13\n\t"
    "vmovaps %%ymm13, 192(%1)\n\t"
    "vmovaps 224(%0), %%ymm14\n\t"
    "vmovaps 224(%0), %%ymm15\n\t"
    "vmulps %%ymm14, %%ymm15, %%ymm15\n\t"
    "vmovaps %%ymm15, 224(%1)"
    : /* outputs */
    : "g"(a), "g"(b)
    :"ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7",
     "ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14",
     "ymm15"
  );
}
