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
 *  @brief Public functions, macros and types used for
 *         digital signal processing.
 *
 *  @author Thomas Quintana (quintana.thomas@gmail.com)
 *  @bug No known bugs.
 */

#ifndef DSP_H
#define DSP_H

/**
 * Compute the Hann function.
 *
 * @param n The index at time t.
 * @param N The number of samples per frame.
 */
#define hann_func(n, N) (0.5 * (1 - cos((2 * M_PI * (n)) / ((N) - 1))))

#endif /* DSP_H */