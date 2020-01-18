/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2019 Bolder Flight Systems
*/

#include "polytools/polytools.h"
#include "Eigen/Core"
#include "Eigen/Dense"
#include "Eigen/QR"

namespace polytools {

std::vector<float> polyfit(std::vector<float> x, std::vector<float> y,
                          unsigned int deg) {
  std::vector<float> ret;
  if (x.size() != y.size()) {
    return ret;
  }
  if ((x.size() == 0) || (y.size() == 0)) {
    return ret;
  }
  ret.resize(deg + 1);
  Eigen::MatrixXf a(x.size(), deg + 1);
  Eigen::VectorXf b(x.size());
  Eigen::VectorXf p(deg + 1);
  for (unsigned int i = 0; i < x.size(); i++) {
    for (unsigned int j = 0; j <= deg; j++) {
      a(i, j) = powf(x[i], j);
    }
    b(i) = y[i];
  }
  p = a.householderQr().solve(b);
  for (unsigned int i = (deg + 1), j = 0; i > 0; i--, j++) {
    ret[j] = p(i - 1);
  }
  return ret;
}

float polyval(const std::vector<float> &p, float x) {
  if (p.size() > 0) {
    float y = p[0];
    for (unsigned int i = 1; i < p.size(); i++) {
      y = y * x + p[i];
    }
    return y;
  } else {
    return 0.0f;
  }
}

std::vector<float> polyval(const std::vector<float> &p,
                          const std::vector<float> &x) {
  std::vector<float> y;
  if (p.size() > 0) {
    y.resize(x.size(), 0.0f);
    for (unsigned int i = 0; i < x.size(); i++) {
      y[i] = p[0];
      for (unsigned int j = 1; j < p.size(); j++) {
        y[i] = y[i] * x[i] + p[j];
      }
    }
  } else {
    y.resize(x.size(), 0.0f);
  }
  return y;
}

}  // namespace polytools
