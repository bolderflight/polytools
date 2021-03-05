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
#include <vector>
#include <iostream>

int main()
{
  /* Independent and dependent data */
  std::vector<float> x = {1, 2, 3, 4};
  std::vector<float> y = {2, 4, 6, 8};
  for (unsigned int i = 0; i < x.size(); i++) {
    std::cout << "x: " << x[i] << " y: " << y[i] << std::endl;
  }
  /* Find a polynomial fit to the data */
  std::vector<float> p = bfs::polyfit(x, y, 1);
  /* Print the polynomial coefficients */
  for (const auto &coeff : p) {
    std::cout << "Polynomial Coefficient: " << coeff << std::endl;
  }
  /* Evaluate the polynomial at x[0] */
  float output = bfs::polyval(p, x[0]);
  std::cout << "Polynomial Evaluation at x = " << x[0] << ": " << output << std::endl;
  /* Evaluate the polynomial for the x vector */
  std::vector<float> outputs = bfs::polyval(p, x);
  for (unsigned int i = 1; i < outputs.size(); i++) {
    std::cout << "Polynomial Evaluation at x = " << x[i] << ": " << outputs[i] << std::endl;
  }
  return 0;
}
