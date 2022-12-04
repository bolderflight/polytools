/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2022 Bolder Flight Systems Inc
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

#ifndef POLYTOOLS_SRC_POLYTOOLS_H_  // NOLINT
#define POLYTOOLS_SRC_POLYTOOLS_H_

#if defined(ARDUINO)
#include <Arduino.h>
#endif
#include <array>
#include <type_traits>
#include "eigen.h"  // NOLINT
#include "Eigen/Dense"
#include "Eigen/QR"

namespace bfs {

/* Linear polyfit */
template<typename T>
constexpr std::array<T, 2> linearmap(const std::array<T, 2> &x,
                                     const std::array<T, 2> &y) {
  std::array<T, 2> p;
  static_assert(std::is_floating_point<T>::value,
                "Only floating point types supported");
  /* Compute scale factor and bias */
  p[0] = (y[1] - y[0]) / (x[1] - x[0]);
  p[1] = y[0] - p[0] * x[0];
  return p;
}
/*
* Fits a polynomial of degree, DEG, to the independent, x, and
* dependent, y, data. Returns the polynomial coefficients in
* order of descending power.
*/
template<std::size_t DEG, typename T, std::size_t ARRAY_LEN>
std::array<T, DEG + 1> polyfit(const std::array<T, ARRAY_LEN> &x,
                               const std::array<T, ARRAY_LEN> &y) {
  std::array<T, DEG + 1> p;
  static_assert(std::is_floating_point<T>::value,
                "Only floating point types supported");
  static_assert(ARRAY_LEN > 0,
                "X, Y data length must be greater than 0");
  static_assert(DEG > 0,
                "Polynomial degree must be greater than 0");
  Eigen::Matrix<T, ARRAY_LEN, DEG + 1> a;
  Eigen::Matrix<T, ARRAY_LEN, 1> b;
  Eigen::Matrix<T, DEG + 1, 1> k;
  for (std::size_t i = 0; i < ARRAY_LEN; i++) {
    for (std::size_t j = 0; j <= DEG; j++) {
      a(i, j) = std::pow(x[i], j);
    }
    b(i) = y[i];
  }
  k = a.householderQr().solve(b);
  for (std::size_t i = (DEG + 1), j = 0; i > 0; i--, j++) {
    p[j] = k(i - 1);
  }
  return p;
}
/* Evaluates the coefficients p at point x, C-style array input */
template<typename T>
constexpr T polyval(T const * const p, const std::size_t len, const T x) {
  static_assert(std::is_floating_point<T>::value,
                "Only floating point types supported");
  T y = 0;
  if (len > 0) {
    y = p[0];
    for (std::size_t i = 1; i < len; i++) {
      y = y * x + p[i];
    }
  }
  return y;
}
/* Evaluates the coefficients p at point x, std::array input */
template<typename T, std::size_t N>
constexpr T polyval(const std::array<T, N> &p, const T x) {
  return polyval<T>(p.data(), p.size(), x);
}

}  // namespace bfs

#endif  // POLYTOOLS_SRC_POLYTOOLS_H_ NOLINT
