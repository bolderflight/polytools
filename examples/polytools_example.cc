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
#include <array>
#include <vector>
#include <iostream>

int main() {
  /* Polyfit */
  std::array<float, 4> x = {1, 2, 3, 4};
  std::vector<float> y = {2, 4, 6, 8};
  std::vector<float> ret = bfs::polyfit<float>(x, y, 1);
  for (auto const & coef : ret) {
    std::cout << "polyfit coef: " << coef << std::endl;
  }
  /* Polynomial coefficients using std::array, std::vectory, and c-style */
  std::array<float, 2> p_array = {2, 0};
  std::vector<float> p_vect = {3, 1};
  float p_c_style[] = {4, 2};
  /* Evaluate x = 2 with each array of coefficients */
  std::cout << "polyval {2, 0} at x = 2: " << bfs::polyval<float>(p_array, 2) << std::endl;
  std::cout << "polyval {3, 1} at x = 2: " << bfs::polyval<float>(p_vect, 2) << std::endl;
  std::cout << "polyval {4, 2} at x = 2: " << bfs::polyval<float>(p_c_style, 2) << std::endl;
}
