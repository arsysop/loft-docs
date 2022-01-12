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

#include <gtest/gtest.h>
#include <vector>

template <typename T>
class VectorTest : public ::testing::test {
    protected:
        using Vector = std::vector<T>; 
}

TYPED_TEST_SUITE_P(VectorTest);

TYPED_TEST_P(VectorTest, Clearing) {
    std::vector<TypeParam> vect{0};
    vect.clear();
    EXPECT_EQ(vect.empty(), true);
}

REGISTER_TYPED_TEST_SUITE_P(
    VectorTest, 
    Clearing);
using TestedTypes = ::testing::Types<int>;
INSTANTIATE_TYPED_TEST_SUITE_P(VectorTesting, VectorTest, TestedTypes);