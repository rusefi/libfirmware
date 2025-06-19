#include <cstring>
#include <cstdint>
#include <cmath>
#include <cctype>
#include <rusefi/efistringutil.h>
#include <rusefi/rusefi_math.h>

namespace rusefi::stringutil {

	bool strEqualCaseInsensitive(const char *str1, const char *str2) {
		int len1 = efiStrlen(str1);
		int len2 = efiStrlen(str2);
		if (len1 != len2) {
			return false;
		}
		for (int i = 0; i < len1; i++) {
			if (std::tolower(str1[i]) != std::tolower(str2[i])) {
				return false;
			}
		}
		return true;
	}

	bool strEqual(const char *str1, const char *str2) {
		// todo: there must be a standard function?!
		int len1 = efiStrlen(str1);
		int len2 = efiStrlen(str2);
		if (len1 != len2) {
			return false;
		}
		for (int i = 0; i < len1; i++) {
			if (str1[i] != str2[i]) {
				return false;
			}
		}
		return true;
	}

	/**
	 * string to float. NaN input is supported
	 *
	 * @return NAN in case of invalid string
	 * todo: explicit value for error code? probably not, NaN is only returned in case of an error
	 */
	float atoff(const char *param) {
		static char todofixthismesswithcopy[DEFAULT_MAX_EXPECTED_STRING_LENGTH];

		uint32_t totallen = efiStrlen(param);
		if (totallen > sizeof(todofixthismesswithcopy) - 1) {
			return (float) NAN;
		}
		strcpy(todofixthismesswithcopy, param);
		char *string = todofixthismesswithcopy;
		if (indexOf(string, 'n') != -1 || indexOf(string, 'N') != -1) {
			return (float) NAN;
		}

		// todo: is there a standard function?
		// unit-tested by 'testMisc()'
		int dotIndex = indexOf(string, '.');
		if (dotIndex == -1) {
			// just an integer
			int result = safe_atoi(string);
			if (absI(result) == ATOI_ERROR_CODE) {
				return (float) NAN;
			}
			return (float) result;
		}
		// todo: this needs to be fixed
		string[dotIndex] = 0;
		int integerPart = safe_atoi(string);
		if (absI(integerPart) == ATOI_ERROR_CODE) {
			return (float) NAN;
		}
		string += (dotIndex + 1);
		int decimalLen = efiStrlen(string);
		int decimal = safe_atoi(string);
		if (absI(decimal) == ATOI_ERROR_CODE) {
			return (float) NAN;
		}
		float divider = 1.0;
		// todo: reuse 'pow10' function which we have anyway
		for (int i = 0; i < decimalLen; i++) {
			divider = divider * 10.0;
		}
		return integerPart + decimal / divider;
	}
}
