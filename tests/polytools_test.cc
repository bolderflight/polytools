/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2021 Bolder Flight Systems Inc
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#include "polytools.h"
#include "gtest/gtest.h"
#include <cmath>
/* Test polyfit linear */
TEST(Polyfit, Linear) {
  std::array<float, 4> x = {1, 2, 3, 4};
  std::array<float, 4> y = {2, 4, 6, 8};
  std::array<float, 2> p = bfs::polyfit<1>(x, y);
  EXPECT_EQ(2, p.size());
  EXPECT_FLOAT_EQ(2, p[0]);
  EXPECT_FLOAT_EQ(0, p[1]);
}
/* Test polyval with zero inputs */
TEST(Polyval, ZeroInput) {
  std::vector<float> p;
  float y = bfs::polyval<float>(p.data(), p.size(), 0.0f);
  EXPECT_FLOAT_EQ(0, y);
}
/* Test polyval bias */
TEST(Polyval, Bias) {
  std::vector<float> p = {5};
  float y = bfs::polyval<float>(p.data(), p.size(), 99.0f);
  EXPECT_FLOAT_EQ(5, y);
}
/* Test polyval linear */
TEST(Polyval, Linear) {
  std::vector<float> p = {2, 1};
  float y = bfs::polyval<float>(p.data(), p.size(), 4.0f);
  EXPECT_FLOAT_EQ(9, y);
}
