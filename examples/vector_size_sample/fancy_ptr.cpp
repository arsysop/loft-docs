/*******************************************************************************
 * Copyright (c) 2022 ArSysOp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Contributors:
 *     (ArSysOp) - initial API and implementation
 *******************************************************************************/

/*!
 * @file
 * An example of dependent types at template instantiation.
 *
 * my::custom_allocator is essentially a copy of std::allocator
 * The only difference is the allocater::pointer type which is declared as class Ptr
 * instead of builtin pointer type.
 * 
 * Consider the call graph generated for foo_adapter_custom vs. foo_adapter_default
 */

#include "fancy_ptr.h"

#include <vector>


extern "C" int foo(const int* buf, unsigned long n);

//! Imitate C++ wrapper for plain C API
int foo_adapter_default(const std::vector<int>& v) {
    return foo(&v[0], v.size());
}

typedef std::vector<int, my::custom_allocator<int>> FancyVec;

//! Imitate C++ wrapper for plain C API
int foo_adapter_custom(const FancyVec& v) {
    return foo(&v[0], v.size());
}

int foo_at_rvalue(const FancyVec& v, size_t n) {
	return v.at(n);
}

void foo_at_lvalue(FancyVec& v, size_t n) {
	v.at(n) = 42;
}
