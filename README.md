## Modules:
- `util`: General purpose math functions, interpolation, array handling, etc.

## Including modules in your project:

Set variable `$(RUSEFI_LIB)` to the path to the folder that contains this readme.

Include the mk files of the modules that you want, then add:
- `$(RUSEFI_LIB_INC)` to your list of includes
- `$(RUSEFI_LIB_CPP)` to your list of c++ input files

Currently, C++17 is required to compile these libraries.

## Unit tests:

Simply run `make && build/libfirmware_test` from the root directory. Just requires normal GCC or clang, on Mac/Linux/WSL/probably mingw32.
