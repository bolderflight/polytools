# polytools
This library includes polyfit and polyval functions for fitting polynomials to data and evaluating polynomials at points.

## Installation
CMake is used to build this library, which is exported as a library target called *polytools*. The header is added as:

```
#include "polytools/polytools.h"
```

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

This will build the library, an example executable called *polytools_example*, and an executable for testing using the Google Test framework, called *polytools_test*. The example executable source file is located at *examples/polytools_example.cc*.

## Functions
**std::vector<float> polyfit(std::vector<float> x, std::vector<float> y, unsigned int deg)** polyfit returns the coefficients for a polynomial of degree, *deg*, that best fit the independent, *x*, and dependent, *y*, data. The coefficients are given in order of descending power and the length of the vector is deg + 1. The data vectors *x* and *y* should be of equal length. High order polynomials do not necessarily lead to a better fit and may be oscillatory, leading to a worse solution. Check the returned polynomial values and be cautious if coefficients are nearly zero.

```C++
std::vector<float> x = {1, 2, 3, 4};
std::vector<float> y = {2, 4, 6, 8};
std::vector<float> p = polyfit(x, y, 1);
```
**float polyval(const std::vector<float> &p, float x)** polyval evaluates the coefficients *p* of a polynomial at point *x*. The coefficients should be given in order of descending power.

```C++
std::vector<float> p = {2, 1};
float y = polyval(p, 2.0f); // y = 5
```

**std::vector<float> polyval(const std::vector<float> &p, const std::vector<float> &x)** polyval evaluates the coefficients *p* of a polynomial at a vector of points *x*, returning a vector of the results. The coefficients should be given in order of descending power.

```C++
std::vector<float> p = {2, 1};
std::vector<float> x = {1, 2, 3, 4};
std::vector<float> y = polyval(p, x); // y = {3, 5, 7, 9}
```
