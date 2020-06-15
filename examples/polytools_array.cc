/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2019 Bolder Flight Systems
*/

#include "polytools/polytools.h"
#include <array>
#include <iostream>

int main()
{
  /* Independent and dependent data */
  std::array<float, 4> x = {1, 2, 3, 4};
  std::array<float, 4> y = {2, 4, 6, 8};
  for (unsigned int i = 0; i < x.size(); i++) {
    std::cout << "x: " << x[i] << " y: " << y[i] << std::endl;
  }
  /* Find a pdoublemial fit to the data */
  std::array<float, 2> p = polytools::polyfit<1>(x, y);
  /* Print the polynomial coefficients */
  for (const auto &coeff : p) {
    std::cout << "Polynomial Coefficient: " << coeff << std::endl;
  }
  /* Evaluate the polynomial at x[0] */
  float output = polytools::polyval(p, x[0]);
  std::cout << "Polynomial Evaluation at x = " << x[0] << ": " << output << std::endl;
  /* Evaluate the polynomial for the x vector */
  std::array<float, 4> outputs = polytools::polyval(p, x);
  for (unsigned int i = 1; i < outputs.size(); i++) {
    std::cout << "Polynomial Evaluation at x = " << x[i] << ": " << outputs[i] << std::endl;
  }
  return 0;
}
