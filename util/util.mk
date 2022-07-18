RUSEFI_LIB_INC += $(RUSEFI_LIB)/util/include

RUSEFI_LIB_CPP += \
	$(RUSEFI_LIB)/util/src/util_dummy.cpp \
	$(RUSEFI_LIB)/util/src/crc.cpp \
	$(RUSEFI_LIB)/util/src/fragments.cpp \
	$(RUSEFI_LIB)/util/src/math.cpp \

RUSEFI_LIB_CPP_TEST += \
	$(RUSEFI_LIB)/util/test/test_arrays.cpp \
	$(RUSEFI_LIB)/util/test/test_framgents.cpp \
	$(RUSEFI_LIB)/util/test/test_math.cpp \

