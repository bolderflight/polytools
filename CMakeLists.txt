cmake_minimum_required(VERSION 3.14)
# Project information
project(PolyTools
  VERSION 4.1.0
  DESCRIPTION  "Polynomial tools; polyfit and polyval."
  LANGUAGES CXX
)
# Fetch eigen
include(FetchContent)
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://github.com/bolderflight/eigen.git
  GIT_TAG v3.0.2
)
FetchContent_MakeAvailable(eigen)
# Add the library target
add_library(polytools INTERFACE)
# Link libraries
target_link_libraries(polytools
  INTERFACE
    eigen
)
# Setup include directories 
target_include_directories(polytools INTERFACE src/
)

# Example and unit testing if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  # Add the example target
  add_executable(polytools_example examples/cmake/polytools_example.cc)
  # Add the includes
  target_include_directories(polytools_example PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  # Link libraries to the example target
  target_link_libraries(polytools_example
    PRIVATE 
      polytools
  )
  # Fetch google test
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
  )
  FetchContent_MakeAvailable(googletest)
  enable_testing()
  include(GoogleTest)
  # Add the test target
  add_executable(polytools_test tests/polytools_test.cc)
  # Add the includes
  target_include_directories(polytools_test PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  # Link libraries to the test target
  target_link_libraries(polytools_test
    PRIVATE 
      polytools
      gtest_main 
      gtest
      gmock
  )
  # Discover unit tests
  gtest_discover_tests(polytools_test)
endif()
