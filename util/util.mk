RUSEFI_LIB_INC += $(RUSEFI_LIB)/util/include $(RUSEFI_LIB)/util/include/rusefi/containers $(RUSEFI_LIB)/can $(RUSEFI_LIB)/board_id

RUSEFI_LIB_CPP += \
	$(RUSEFI_LIB)/util/src/util_dummy.cpp \
	$(RUSEFI_LIB)/util/src/crc.cpp \
	$(RUSEFI_LIB)/util/src/efistringutil.cpp \
	$(RUSEFI_LIB)/util/src/fragments.cpp \
	$(RUSEFI_LIB)/util/src/math.cpp \

RUSEFI_LIB_CPP_TEST += \
	$(RUSEFI_LIB)/util/test/test_arrays.cpp \
	$(RUSEFI_LIB)/util/test/test_crc.cpp \
	$(RUSEFI_LIB)/util/test/test_cyclic_buffer.cpp \
	$(RUSEFI_LIB)/util/test/test_efistringutil.cpp \
	$(RUSEFI_LIB)/util/test/test_fragments.cpp \
	$(RUSEFI_LIB)/util/test/test_interpolation.cpp \
	$(RUSEFI_LIB)/util/test/test_scaled.cpp \
	$(RUSEFI_LIB)/util/test/test_manifest.cpp \
	$(RUSEFI_LIB)/util/test/test_wraparound.cpp \
	$(RUSEFI_LIB)/util/test/test_math.cpp \

