Modules:
- `util`: General purpose math functions, interpolation, array handling, etc.

Set variable `$(RUSEFI_LIB)` to the path to the folder that contains this readme.

Include the mk files of the modules that you want, then add:
- `$(RUSEFI_LIB_INC)` to your list of includes
- `$(RUSEFI_LIB_CPP)` to your list of c++ input files
