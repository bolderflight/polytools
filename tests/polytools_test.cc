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

#include "polytools/polytools.h"
#include "gtest/gtest.h"
#include "math.h"

/* Test polyfit with zero inputs */
TEST(Polyfit, ZeroInput) {
  std::vector<float> x, y;
  std::vector<float> p = bfs::polyfit(x, y, 0.0f);
  EXPECT_EQ(0, p.size());
}
/* Test polyfit, mismatched input sizes */
TEST(Polyfit, InputSize) {
  std::vector<float> x = {1, 2, 3};
  std::vector<float> y = {1, 2};
  std::vector<float> p = bfs::polyfit(x, y, 0.0f);
  EXPECT_EQ(0, p.size());
}
/* Test polyfit linear */
TEST(Polyfit, Linear) {
  std::vector<float> x = {1, 2, 3, 4};
  std::vector<float> y = {2, 4, 6, 8};
  std::vector<float> p = bfs::polyfit(x, y, 1.0f);
  EXPECT_EQ(2, p.size());
  EXPECT_FLOAT_EQ(2, p[0]);
  EXPECT_FLOAT_EQ(0, p[1]);
}
/* Test polyval with zero inputs */
TEST(Polyval, ZeroInput) {
  std::vector<float> p;
  float y = bfs::polyval(p, 0.0f);
  EXPECT_FLOAT_EQ(0, y);
}
/* Test polyval bias */
TEST(Polyval, Bias) {
  std::vector<float> p = {5};
  float y = bfs::polyval(p, 99.0f);
  EXPECT_FLOAT_EQ(5, y);
}
/* Test polyval linear */
TEST(Polyval, Linear) {
  std::vector<float> p = {2, 1};
  float y = bfs::polyval(p, 4.0f);
  EXPECT_FLOAT_EQ(9, y);
}
/* Test polyval vector with zero inputs */
TEST(PolyvalVector, ZeroInput) {
  std::vector<float> p;
  std::vector<float> x;
  std::vector<float> y;
  y = bfs::polyval(p, x);
  EXPECT_EQ(0, y.size());
}
/* Test polyval vector with zero inputs */
TEST(PolyvalVector, ZeroInputX) {
  std::vector<float> p = {2, 0};
  std::vector<float> x;
  std::vector<float> y;
  y = bfs::polyval(p, x);
  EXPECT_EQ(0, y.size());
}
/* Test polyval vector with zero inputs */
TEST(PolyvalVector, ZeroInputP) {
  std::vector<float> p;
  std::vector<float> x = {1, 2, 3, 4};
  std::vector<float> y;
  y = bfs::polyval(p, x);
  EXPECT_EQ(x.size(), y.size());
  for (const auto &ret : y) {
    EXPECT_FLOAT_EQ(0, ret);
  }
}
/* Test polyval vector with bias */
TEST(PolyvalVector, Bias) {
  std::vector<float> p = {5};
  std::vector<float> x = {1, 2, 3, 4};
  std::vector<float> y;
  y = bfs::polyval(p, x);
  EXPECT_EQ(x.size(), y.size());
  for (const auto &ret : y) {
    EXPECT_FLOAT_EQ(5, ret);
  }
}
/* Test polyval vector with linear */
TEST(PolyvalVector, Linear) {
  std::vector<float> p = {2, 0};
  std::vector<float> x = {1, 2, 3, 4};
  std::vector<float> y;
  y = bfs::polyval(p, x);
  EXPECT_EQ(x.size(), y.size());
  EXPECT_FLOAT_EQ(2, y[0]);
  EXPECT_FLOAT_EQ(4, y[1]);
  EXPECT_FLOAT_EQ(6, y[2]);
  EXPECT_FLOAT_EQ(8, y[3]);
}
