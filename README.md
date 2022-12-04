[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

![Bolder Flight Systems Logo](img/logo-words_75.png) &nbsp; &nbsp; ![Arduino Logo](img/arduino_logo_75.png)

# Polytools
This library includes polyfit and polyval functions for fitting polynomials to data and evaluating polynomials at points. This library is compatible with Arduino ARM and with CMake build systems. It would also be easy to include with other projects, since it is a header only library consisting of a single file.
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

# Installation

## Arduino
Use the Arduino Library Manager to install this library or clone to your Arduino/libraries folder. Additionally, the [Bolder Flight Systems Eigen library](https://github.com/bolderflight/eigen) must be installed. This library is added as:

```C++
#include "polytools.h"
```

An example Arduino executable is located at *examples/arduino/polytools_example/polytools_example.ino*. Teensy 3.x, 4.x, and LC devices are used for testing under Arduino and this library should be compatible with other ARM devices. This library is *not* expected to work on AVR devices.

## CMake
CMake is used to build this library, which is exported as a library target called *polytools*. The header is added as:

```C++
#include "polytools.h"
```

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

This will build the library, an example executable called *polytools_example*, and an executable for testing using the Google Test framework, called *polytools_test*. The example executable source files are located at *examples/cmake/polytools_example.cc*.

# Namespace
This library is within the namespace *bfs*.

# Functions

**std::array<T, DEG + 1> polyfit(const std::array<T, ARRAY_LEN> &x, const std::array<T, ARRAY_LEN> &y** polyfit is templated with respect to the degree of the polynomial, the type, and the length of the input data; however, template deduction should recognize the type and input data length. Polyfit returns the coefficients for a polynomial of degree, *DEG*, that best fit the independent, *x*, and dependent, *y*, data. The coefficients are given in order of descending power and the length of the returned polynomial coefficients is DEG + 1. High order polynomials do not necessarily lead to a better fit and may be oscillatory, leading to a worse solution. Check the returned polynomial values and be cautious if coefficients are nearly zero.

```C++
std::array<float, 4> x = {1, 2, 3, 4};
std::array<float, 4> y = {2, 4, 6, 8};
std::array<float, 2> p = bfs::polyfit<1>(x, y);
```
**T polyval(T const * const p, const std::size_t len, const T x)** polyval evaluates the coefficients *p*, length *len*, of a polynomial at point *x*. The coefficients should be given in order of descending power.

```C++
float y = bfs::polyval(p.data(), p.size(), 2.0f); // y = 4
```

**T polyval(const std::array<T, N> &p, const T x)** polyval evaluates the coefficients *p* of a polynomial at point *x*. The coefficients should be given in order of descending power.

```C++
float y = bfs::polyval(p, 3.0f); // y = 6
```
