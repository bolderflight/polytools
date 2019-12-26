/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2019 Bolder Flight Systems
*/

#ifndef POLYTOOLS_H
#define POLYTOOLS_H

#include <stdlib.h>
#include <vector>

namespace polytools {

/*
* Fits a polynomial of degree, deg, to the independent, x, and 
* dependent, y, data. Returns the polynomial coefficients in
* order of descending power.
*/
std::vector<float> polyfit(std::vector<float> x, std::vector<float> y, unsigned int deg);
/*
* Performs a polynomial evaluation given a vector of polynomial
* coefficients in descending order, p, and an input value, x. 
* Returns the evaluated value.
*/
float polyval(const std::vector<float> &p, float x);
/*
* Performs a polynomial evaluation given a vector of polynomial
* coefficients in descending order, p, and a vector of input
* values, x. Returns a vector of evaluated values.
*/
std::vector<float> polyval(const std::vector<float> &p, const std::vector<float> &x);

} // polytools

#endif
