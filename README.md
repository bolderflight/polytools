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

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

This will build the library, an example executable called *polytools_example*, and an executable for testing using the Google Test framework, called *polytools_test*. The example executable source files are located at *examples/polytools_example.cc*.

## Namespace
This library is within the namespace *bfs*.

## Functions
Functions are provided using *std::span*, which works with *std::array*, *std::vector*, and c-style array inputs. Templates are used to specify the type used based on the input types (i.e. float, double, etc).

**std::vector polyfit(std::span x, std::span y, const int deg)** polyfit returns the coefficients for a polynomial of degree, *deg*, that best fit the independent, *x*, and dependent, *y*, data. The coefficients are given in order of descending power and the length of the vector is deg + 1. The data spans *x* and *y* should be of equal length. High order polynomials do not necessarily lead to a better fit and may be oscillatory, leading to a worse solution. Check the returned polynomial values and be cautious if coefficients are nearly zero.

```C++
std::array<float, 4> x = {1, 2, 3, 4};
std::array<float, 4> y = {2, 4, 6, 8};
std::vector<float> p = bfs::polyfit<float>(x, y, 1);
```
**typename polyval(std::span p, const typename x)** polyval evaluates the coefficients *p* of a polynomial at point *x*. The coefficients should be given in order of descending power.

```C++
std::vector<double> p = {2, 1};
double y = bfs::polyval<double>(p, 2.0); // y = 5
```
