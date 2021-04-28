# Changelog

## v3.0.0
- Updated to use std::span, so only 1 version of polyfit and polyval needs to be maintained

## v2.0.1
- Fixed the const-ness of the C style polyval

## v2.0.0
- Updated to namespace *bfs*

## v1.1.4
- Updated CMakeLists to use GitHub for eigen repo
- Updated CONTRIBUTING to point to the contributing repo

## v1.1.3
- Added a c-style polyval where the polynomial coefficient array is passed as a pointer and a length

## v1.0.3
- Updated contributing
- Modified *fetch_content* from ssh to https for dependencies

## v1.0.2
- Updated to MIT license.

## v1.0.1
- Cleaned up the includes; had some extra libraries, which were used for debugging and causing issues cross-compiling for Cortex.

## v1.0.0
- Initial baseline.
