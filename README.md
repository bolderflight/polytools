# polytools
This library includes polyfit and polyval functions for fitting polynomials to data and evaluating polynomials at points.
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

## Installation
CMake is used to build this library, which is exported as a library target called *polytools*. The header is added as:

```
#include "polytools/polytools.h"
```
Note that you'll need CMake version 3.13 or above; it is recommended to build and install CMake from source, directions are located in the [CMake GitLab repository](https://github.com/Kitware/CMake).

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

This will build the library, an example executable called *polytools_example*, and an executable for testing using the Google Test framework, called *polytools_test*. The example executable source file is located at *examples/polytools_example.cc*. This code is built and tested on an AMD64 system running Linux and is likely to build on AMD64 systems running the Windows Subsystem for Linux (WSL). As an alternative, a Docker container has been [built](https://hub.docker.com/r/flybrianfly/gcc-cmake) which extends the gcc container to include CMake support and supports building this library.

## Namespace
This library is within the namespace *polytools*.

## Functions
**std::vector&ltfloat&gt polyfit(std::vector&ltfloat&gt x, std::vector&ltfloat&gt y, unsigned int deg)** polyfit returns the coefficients for a polynomial of degree, *deg*, that best fit the independent, *x*, and dependent, *y*, data. The coefficients are given in order of descending power and the length of the vector is deg + 1. The data vectors *x* and *y* should be of equal length. High order polynomials do not necessarily lead to a better fit and may be oscillatory, leading to a worse solution. Check the returned polynomial values and be cautious if coefficients are nearly zero.

```C++
std::vector<float> x = {1, 2, 3, 4};
std::vector<float> y = {2, 4, 6, 8};
std::vector<float> p = polytools::polyfit(x, y, 1);
```
**float polyval(const std::vector&ltfloat&gt &p, float x)** polyval evaluates the coefficients *p* of a polynomial at point *x*. The coefficients should be given in order of descending power.

```C++
std::vector<float> p = {2, 1};
float y = polytools::polyval(p, 2.0f); // y = 5
```

**std::vector&ltfloat&gt polyval(const std::vector&ltfloat&gt &p, const std::vector&ltfloat&gt &x)** polyval evaluates the coefficients *p* of a polynomial at a vector of points *x*, returning a vector of the results. The coefficients should be given in order of descending power.

```C++
std::vector<float> p = {2, 1};
std::vector<float> x = {1, 2, 3, 4};
std::vector<float> y = polytools::polyval(p, x); // y = {3, 5, 7, 9}
```
