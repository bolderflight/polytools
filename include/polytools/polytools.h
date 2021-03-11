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

#include <array>
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
template<int DEG, typename TYPE, std::size_t ARRAY_SIZE>
std::array<TYPE, DEG + 1> polyfit(const std::array<TYPE, ARRAY_SIZE> &x,
                                  const std::array<TYPE, ARRAY_SIZE> &y) {
  static_assert(DEG >= 0, "Polyfit polynomial degree less than 0");
  std::array<TYPE, DEG + 1> ret;
  if (ARRAY_SIZE == 0) {
    return ret;
  }
  Eigen::Matrix<TYPE, ARRAY_SIZE, DEG + 1> a;
  Eigen::Matrix<TYPE, ARRAY_SIZE, 1> b;
  Eigen::Matrix<TYPE, DEG + 1, 1> p;
  for (std::size_t i = 0; i < x.size(); i++) {
    for (std::size_t j = 0; j <= DEG; j++) {
      a(i, j) = powf(x[i], j);
    }
    b(i) = y[i];
  }
  p = a.householderQr().solve(b);
  for (std::size_t i = (DEG + 1), j = 0; i > 0; i--, j++) {
    ret[j] = p(i - 1);
  }
  return ret;
}
template<typename TYPE>
std::vector<TYPE> polyfit(const std::vector<TYPE> &x,
                          const std::vector<TYPE> &y,
                          int deg) {
  std::vector<TYPE> ret;

  if ((deg < 0) ||
     (x.size() != y.size()) ||
     ((x.size() == 0) || (y.size() == 0))) {
    return ret;
  }
  ret.resize(deg + 1);
  Eigen::Matrix<TYPE, Eigen::Dynamic, Eigen::Dynamic> a(x.size(), deg + 1);
  Eigen::Matrix<TYPE, Eigen::Dynamic, 1> b(x.size());
  Eigen::Matrix<TYPE, Eigen::Dynamic, 1> p(deg + 1);
  for (std::size_t i = 0; i < x.size(); i++) {
    for (std::size_t j = 0; j <= deg; j++) {
      a(i, j) = powf(x[i], j);
    }
    b(i) = y[i];
  }
  p = a.householderQr().solve(b);
  for (std::size_t i = (deg + 1), j = 0; i > 0; i--, j++) {
    ret[j] = p(i - 1);
  }
  return ret;
}
/*
* Performs a polynomial evaluation given a C-style array (pointer & length) 
* of polynomial coefficients in descending order, p, and an input value, x. 
* Returns the evaluated value.
*/
template<typename TYPE>
TYPE polyval(const TYPE * const p, const std::size_t len, const TYPE x) {
  if (!p) {return 0;}
  if (len > 0) {
    TYPE y = p[0];
    for (std::size_t i = 1; i < len; i++) {
      y = y * x + p[i];
    }
    return y;
  } else {
    return 0;
  }
}
/*
* Performs a polynomial evaluation given an array of polynomial
* coefficients in descending order, p, and an input value, x. 
* Returns the evaluated value.
*/
template<typename TYPE, std::size_t ARRAY_SIZE>
TYPE polyval(const std::array<TYPE, ARRAY_SIZE> &p, TYPE x) {
  if (p.size() > 0) {
    TYPE y = p[0];
    for (std::size_t i = 1; i < p.size(); i++) {
      y = y * x + p[i];
    }
    return y;
  } else {
    return 0;
  }
}
/*
* Performs a polynomial evaluation given a vector of polynomial
* coefficients in descending order, p, and an input value, x. 
* Returns the evaluated value.
*/
template<typename TYPE>
TYPE polyval(const std::vector<TYPE> &p, TYPE x) {
  if (p.size() > 0) {
    TYPE y = p[0];
    for (std::size_t i = 1; i < p.size(); i++) {
      y = y * x + p[i];
    }
    return y;
  } else {
    return 0;
  }
}
/*
* Performs a polynomial evaluation given an array of polynomial
* coefficients in descending order, p, and an array of input
* values, x. Returns an array of evaluated values.
*/
template<typename TYPE, std::size_t SIZE_P, std::size_t SIZE_X>
std::array<TYPE, SIZE_X> polyval(const std::array<TYPE, SIZE_P> &p,
                                 const std::array<TYPE, SIZE_X> &x) {
  std::array<TYPE, SIZE_X> y;
  if (p.size() > 0) {
    for (std::size_t i = 0; i < x.size(); i++) {
      y[i] = p[0];
      for (std::size_t j = 1; j < p.size(); j++) {
        y[i] = y[i] * x[i] + p[j];
      }
    }
  }
  return y;
}
/*
* Performs a polynomial evaluation given a vector of polynomial
* coefficients in descending order, p, and a vector of input
* values, x. Returns a vector of evaluated values.
*/
template<typename TYPE>
std::vector<TYPE> polyval(const std::vector<TYPE> &p,
                          const std::vector<TYPE> &x) {
  std::vector<TYPE> y(x.size());
  if (p.size() > 0) {
    for (std::size_t i = 0; i < x.size(); i++) {
      y[i] = p[0];
      for (std::size_t j = 1; j < p.size(); j++) {
        y[i] = y[i] * x[i] + p[j];
      }
    }
  }
  return y;
}

}  // namespace bfs

#endif  // INCLUDE_POLYTOOLS_POLYTOOLS_H_
