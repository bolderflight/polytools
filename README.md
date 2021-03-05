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

This will build the library, example executables called *polytools_array* and *polytools_vector*, and an executable for testing using the Google Test framework, called *polytools_test*. The example executable source files are located at *examples/polytools_array.cc* and *examples/polytools_vector.cc*.

## Namespace
This library is within the namespace *bfs*.

## Functions
Functions are provided using *std::array* for static memory allocation and *std::vector* for applications requiring dynamic memory allocation. Templates are used to specify the type used based on the input types (i.e. float, double, etc).

### Static Memory Allocation

**std::array polyfit&lt;DEG&gt;(const std::array &x, const std::array &y)** polyfit returns the coefficients for a polynomial of degree, *DEG*, that best fit the independent, *x*, and dependent, *y*, data. The coefficients are given in order of descending power and the length of the vector is deg + 1. The data vectors *x* and *y* should be of equal length. High order polynomials do not necessarily lead to a better fit and may be oscillatory, leading to a worse solution. Check the returned polynomial values and be cautious if coefficients are nearly zero.

```C++
std::array<float, 4> x = {1, 2, 3, 4};
std::array<float, 4> y = {2, 4, 6, 8};
std::array<float, 2> p = bfs::polyfit<1>(x, y);
```
**typename polyval(const std::array &p, typename x)** polyval evaluates the coefficients *p* of a polynomial at point *x*. The coefficients should be given in order of descending power.

```C++
std::array<double, 2> p = {2, 1};
double y = bfs::polyval(p, 2.0); // y = 5
```

**typename polyval(typename &ast;p, std::size_t len, typename x)** polyval evaluates the coefficients *p* of a polynomial at point *x*. The coefficients are given by passing a pointer to the coefficient array and the length of the array. The coefficients should be given in order of descending power.

```C++
std::array<double, 2> p = {2, 1};
double y = bfs::polyval(p.data(), p.size(), 2.0); // y = 5
```

**std::array polyval(const std::array &p, const std::array &x)** polyval evaluates the coefficients *p* of a polynomial at a vector of points *x*, returning a vector of the results. The coefficients should be given in order of descending power.

```C++
std::array<int, 2> p = {2, 1};
std::array<int, 4> x = {1, 2, 3, 4};
std::array<int, 4> y = bfs::polyval(p, x); // y = {3, 5, 7, 9}
```

### Dynamic Memory Allocation

**std::vector polyfit(const std::vector &x, const std::vector &y, int deg)** polyfit returns the coefficients for a polynomial of degree, *deg*, that best fit the independent, *x*, and dependent, *y*, data. The coefficients are given in order of descending power and the length of the vector is deg + 1. The data vectors *x* and *y* should be of equal length. High order polynomials do not necessarily lead to a better fit and may be oscillatory, leading to a worse solution. Check the returned polynomial values and be cautious if coefficients are nearly zero.

```C++
std::vector<float> x = {1, 2, 3, 4};
std::vector<float> y = {2, 4, 6, 8};
std::vector<float> p = bfs::polyfit(x, y, 1);
```
**typename polyval(const std::vector &p, typename x)** polyval evaluates the coefficients *p* of a polynomial at point *x*. The coefficients should be given in order of descending power.

```C++
std::vector<double> p = {2, 1};
double y = bfs::polyval(p, 2.0); // y = 5
```

**std::vector polyval(const std::vector &p, const std::vector &x)** polyval evaluates the coefficients *p* of a polynomial at a vector of points *x*, returning a vector of the results. The coefficients should be given in order of descending power.

```C++
std::vector<int> p = {2, 1};
std::vector<int> x = {1, 2, 3, 4};
std::vector<int> y = bfs::polyval(p, x); // y = {3, 5, 7, 9}
```
