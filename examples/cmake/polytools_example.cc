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
#include <array>
#include <iostream>

int main() {
  /* Polyfit independent (x) and dependent (y) data */
  std::array<float, 4> x = {1, 2, 3, 4};
  std::array<float, 4> y = {2, 4, 6, 8};
  /*
  * Templated polynomial degree, returns an array of polynomial coefficients,
  * length degree + 1, in order of descending power.
  */
  std::array<float, 2> p = bfs::polyfit<1>(x, y);
  for (std::size_t i = 0; i < p.size(); i++) {
    std::cout << "polyfit coef: " << p[i] << std::endl;
  }
  /* Evaluate at x = 2 using std::array */
  std::cout << "polyval at x = 2: " << bfs::polyval(p, 2.0f) << std::endl;
  /* Evaluate at x = 3 using c-style array */
  std::cout << "polyval at x = 3: " << bfs::polyval(p.data(), p.size(), 3.0f) << std::endl;
}
