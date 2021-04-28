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

#ifndef INCLUDE_POLYTOOLS_POLYTOOLS_H_
#define INCLUDE_POLYTOOLS_POLYTOOLS_H_

#include <span>
#include <vector>
#include "Eigen/Core"
#include "Eigen/Dense"
#include "Eigen/QR"


namespace bfs {

/*
* Fits a polynomial of degree, deg, to the independent, x, and
* dependent, y, data. Returns the polynomial coefficients in
* order of descending power.
*/
template<typename T>
std::vector<T> polyfit(std::span<const T> x,
                       std::span<const T> y,
                       const int deg) {
  std::vector<T> ret;
  if ((deg < 0) ||
     (x.size() != y.size()) ||
     (x.size() == 0)) {
    return ret;
  }
  ret.resize(deg + 1);
  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> a(x.size(), deg + 1);
  Eigen::Matrix<T, Eigen::Dynamic, 1> b(x.size());
  Eigen::Matrix<T, Eigen::Dynamic, 1> p(deg + 1);
  for (std::size_t i = 0; i < x.size(); i++) {
    for (std::size_t j = 0; j <= deg; j++) {
      a(i, j) = std::pow(x[i], j);
    }
    b(i) = y[i];
  }
  p = a.householderQr().solve(b);
  for (std::size_t i = (deg + 1), j = 0; i > 0; i--, j++) {
    ret[j] = p(i - 1);
  }
  return ret;
}
/* Evaluates the coefficients p at point x */
template<typename T>
T polyval(std::span<const T> p, const T x) {
  T y = 0;
  if (p.size() > 0) {
    y = p[0];
    for (std::size_t i = 1; i < p.size(); i++) {
      y = y * x + p[i];
    }
  }
  return y;
}

}  // namespace bfs

#endif  // INCLUDE_POLYTOOLS_POLYTOOLS_H_
