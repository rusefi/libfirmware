#pragma once

#include <cstdint>
#include <string_view>
#include <algorithm>

namespace rusefi::stringutil {
    constexpr uint32_t DEFAULT_MAX_EXPECTED_STRING_LENGTH = 100;

    /****************************************************************/
    // TODO: refactor to constexpr
    /****************************************************************/
    bool strEqualCaseInsensitive(const char *str1, const char *str2);
    bool strEqual(const char *str1, const char *str2);
    float atoff(const char*);
    /****************************************************************/

    namespace implementation {
        // Internal implementation: pointer version with bounded length
        template <size_t MaxLen>
        constexpr uint32_t efiStrlen_impl(char const* const str) noexcept {
            if (str == nullptr) {
                return 0;
            }

            size_t i{};

            while (i < MaxLen && str[i] != '\0') {
                ++i;
            }

            return static_cast<uint32_t>(i);
        }

        template <size_t MaxLen>
        constexpr int32_t indexOf_impl(char const* const string, char const ch) noexcept {
            if (string == nullptr) {
                return -1;
            }

            uint32_t i = 0;
            while (i < MaxLen) {
                char c = string[i];
                if (c == '\0') {
                    return -1;
                }
                if (c == ch) {
                    return static_cast<int32_t>(i);
                }
                ++i;
            }

            return -1;
        }
    }

    // Generic version with default max length (for pointers)
    template <size_t MaxLen>
    constexpr uint32_t efiStrnlen(char const* const str) noexcept {
        return implementation::efiStrlen_impl<MaxLen>(str);
    }

    // Overload for native arrays: deduces size as max
    template <size_t N>
    constexpr uint32_t efiStrlen(char const (&arr)[N]) noexcept
    requires (std::is_array_v<std::remove_cvref_t<decltype(arr)>> && N > 0) {
        return implementation::efiStrlen_impl<N>(arr);
    }

    // Counts up to DEFAULT_MAX_EXPECTED_STRING_LENGTH(100) characters in the provided string
    // Use efiStrnlen<> to raise the limit
    template <size_t MaxLen = DEFAULT_MAX_EXPECTED_STRING_LENGTH, typename T>
    constexpr uint32_t efiStrlen(T str) noexcept
    requires (!std::is_array_v<std::remove_cvref_t<T>>) {
        return implementation::efiStrlen_impl<MaxLen>(str);
    }

    template <size_t MaxLen, size_t N>
    constexpr int32_t indexOfN(char const (&arr)[N], char const ch) noexcept
    requires (std::is_array_v<std::remove_cvref_t<decltype(arr)>> && N > 0) {
        return implementation::indexOf_impl<std::min(MaxLen, N)>(arr, ch);
    }

    template <size_t MaxLen, typename T>
    constexpr int32_t indexOfN(T str, char const ch) noexcept
    requires (!std::is_array_v<std::remove_cvref_t<T>>) {
        return implementation::indexOf_impl<MaxLen>(str, ch);
    }

    // Overload for native arrays
    template <size_t N>
    constexpr int32_t indexOf(char const (&arr)[N], char const ch) noexcept
    requires (std::is_array_v<std::remove_cvref_t<decltype(arr)>> && N > 0) {
        return implementation::indexOf_impl<N>(arr, ch);
    }

    // Searches up to DEFAULT_MAX_EXPECTED_STRING_LENGTH(100) characters in the provided string
    // Use indexOfN<> to raise the limit
    template <typename T>
    constexpr int32_t indexOf(T str, char const ch) noexcept
    requires (!std::is_array_v<std::remove_cvref_t<T>>) {
        return implementation::indexOf_impl<DEFAULT_MAX_EXPECTED_STRING_LENGTH>(str, ch);
    }

    namespace tests {
        constexpr char const* tstr = "hello";
        static_assert(efiStrlen(tstr) == 5);
        static_assert(efiStrlen("hello") == 5);

        constexpr char msg[12] = "world!";
        static_assert(efiStrlen(msg) == 6);

        constexpr char incomplete[12] = {'a', 'b', 'c'}; // not null-terminated
        static_assert(efiStrlen(incomplete) == 3);       // stops at non-null or 12

        constexpr char nullstr[12] = {'\0'};
        static_assert(efiStrlen(nullstr) == 0);

        static_assert(indexOf("hello", 'e') == 1);
        static_assert(indexOf("hello", 'x') == -1);

        constexpr char name[] = "example";
        static_assert(indexOf(name, 'a') == 2);

        constexpr char const* name2 = "example2S";
        static_assert(indexOf(name2, 'S') == 8);

        constexpr char tst1[] = { ' ', ' ', ' ' };
        static_assert(indexOf(tst1, 'S') == -1); // <- Ok, we knew only 3 were present
        static_assert(indexOfN<3>(tst1, 'S') == -1);
        static_assert(indexOfN<100>(tst1, 'S') == -1); // Array was passed and size is known OK;
        constexpr char const* const tst2 = static_cast<char const*>(tst1);
        // SEGFAULT
        // static_assert(indexOfN<100>(tst2, 'S') == -1); // Array with few chars and no null-term was passed and size is unknown -> SEGFAULT
        // SEGFAULT
        static_assert(indexOfN<2>(tst2, 'S') == -1); // <- Ok, we explicitly passed size that is less or equal of real storage size
    }

    /*
        From https://en.cppreference.com/w/cpp/string/wide/iswspace
        Space (0x20, ' ')
        Form feed (0x0c, '\f')
        Line feed (0x0a, '\n')
        Carriage return (0x0d, '\r')
        Horizontal tab (0x09, '\t')
        Vertical tab (0x0b, '\v').
    */
    constexpr bool is_whitespace(char const c) {
        constexpr char matches[] = { ' ', '\f', '\n', '\r', '\t',  '\v' };
        return std::any_of(std::begin(matches), std::end(matches), [c](char c0) { return c == c0; });
    }

    constexpr bool is_digit(char const c) {
        return c >= '0' && c <= '9';
    }

    constexpr bool is_sign(char const c) {
        return c == '+' || c == '-';
    }

    // "functor" to check for ws absence in string
    struct no_ws {
        constexpr explicit no_ws(const char* const str) : data(str) { }

        constexpr explicit operator bool() const {
            const std::string_view sv{data};
            return !std::ranges::any_of(sv, is_whitespace);
        }

        const char* data;
    };

    constexpr int32_t ATOI_ERROR_CODE = -311223344;
    constexpr int32_t ATOI_MAGIC_NUMBER_OF_MAX_PRECEEDING_WHITESPACE_CHARS = 5;
    constexpr int32_t ATOI_MAX_INT32_DIGITS = 10;

    namespace tests {
        constexpr int32_t ATOI_ERROR_CODE = 10000000;
        constexpr int32_t ATOI_ERROR_CODE_BAD_STRING = ATOI_ERROR_CODE + 1;
        constexpr int32_t ATOI_ERROR_CODE_TOO_MUCH_WS = ATOI_ERROR_CODE + 2;
        constexpr int32_t ATOI_ERROR_CODE_NO_DIGIT_AFTER_SIGN = ATOI_ERROR_CODE + 3;
        constexpr int32_t ATOI_ERROR_CODE_NO_DIGITS = ATOI_ERROR_CODE + 4;
        constexpr int32_t ATOI_ERROR_CODE_TOO_MUCH_DIGITS = ATOI_ERROR_CODE + 5;
        constexpr int32_t ATOI_ERROR_CODE_OVERFLOW_RANK = ATOI_ERROR_CODE + 6;
        constexpr int32_t ATOI_ERROR_CODE_OVERFLOW_DIGIT = ATOI_ERROR_CODE + 7;
        constexpr int32_t ATOI_ERROR_CODE_NO_DATA = ATOI_ERROR_CODE + 8;
        constexpr int32_t ATOI_ERROR_CODE_TRAILING_NON_WS_CHARS = ATOI_ERROR_CODE + 9;
        constexpr int32_t ATOI_ERROR_CODE_TRAILING_CHARS = ATOI_ERROR_CODE + 10;

        enum class SafeAtoiErrorMode {
            Test,
            Prod
        };
    }

    enum class SafeAtoiTrailingCharCheckMode {
        allowOnlyWhitespace,
        allowOnlyNull,
        allowAll
    };

    // Mostly based on cppreference atoi page.
    // Intended to mimic the behavior of libc's atoi in a constexpr-safe way:
    // - Skips leading whitespaces (up to ATOI_MAGIC_NUMBER_OF_MAX_PRECEEDING_WHITESPACE_CHARS)
    // - Accepts an optional '+' or '-' sign
    // - Parses digits until the first non-digit
    // - If onlyAllowWhitespacesAtTheEnd is true, trailing characters must be whitespace or null
    // Returns ATOI_ERROR_CODE on invalid input, malformed format, or overflow.
    template<tests::SafeAtoiErrorMode errorMode = tests::SafeAtoiErrorMode::Prod,
             SafeAtoiTrailingCharCheckMode trailingCharsCheckMode = SafeAtoiTrailingCharCheckMode::allowAll>
    constexpr int32_t safe_atoi(char const* const string) noexcept {
        if (string == nullptr || string[0] == '\0') {
            if constexpr (errorMode == tests::SafeAtoiErrorMode::Test) {
                return tests::ATOI_ERROR_CODE_BAD_STRING;
            }

            return ATOI_ERROR_CODE;
        }

        char const* str{ string };

        while (is_whitespace(*str)) {
            if ((str - string) < ATOI_MAGIC_NUMBER_OF_MAX_PRECEEDING_WHITESPACE_CHARS) {
                ++str;
            } else {
                if constexpr (errorMode == tests::SafeAtoiErrorMode::Test) {
                    return tests::ATOI_ERROR_CODE_TOO_MUCH_WS;
                }

                return ATOI_ERROR_CODE;
            }
        }

        bool const negative{ *str == '-' };

        if (*str == '+' || *str == '-') {
            ++str;

            if (!is_digit(*str)) {
                if constexpr (errorMode == tests::SafeAtoiErrorMode::Test) {
                    return tests::ATOI_ERROR_CODE_NO_DIGIT_AFTER_SIGN;
                }

                return ATOI_ERROR_CODE;
            }
        }

        bool preceding_zero{false};

        int32_t digits{};

        // Skip preceding 0s
        while (*str == '0') {
            ++str;
            digits = 1;
            preceding_zero = true;
        }

        constexpr int32_t MAX_DIV10 = INT32_MIN / 10; // -214748364

        int32_t result{};
        while(*str != '\0') {
            if (!is_digit(*str)) {
                // Ok finish here
                if (digits) {
                    break;
                }

                if constexpr (errorMode == tests::SafeAtoiErrorMode::Test) {
                    return tests::ATOI_ERROR_CODE_NO_DIGITS;
                }

                // ill-formed string
                return ATOI_ERROR_CODE;
            }

            // Too many digits for 32-bit int
            if (digits >= (ATOI_MAX_INT32_DIGITS + (preceding_zero ? 1 : 0))) {
                if constexpr (errorMode == tests::SafeAtoiErrorMode::Test) {
                    return tests::ATOI_ERROR_CODE_TOO_MUCH_DIGITS;
                }

                return ATOI_ERROR_CODE;
            }

            int32_t const digit{ *str - '0' };

            // Will overflow
            if (result < MAX_DIV10) {
                if constexpr (errorMode == tests::SafeAtoiErrorMode::Test) {
                    return tests::ATOI_ERROR_CODE_OVERFLOW_RANK;
                }

                return ATOI_ERROR_CODE;
            }

            result *= 10;

            // Will overflow
            if (result < (INT32_MIN + digit + (negative ? 0 : 1))) {
                if constexpr (errorMode == tests::SafeAtoiErrorMode::Test) {
                    return tests::ATOI_ERROR_CODE_OVERFLOW_DIGIT;
                }
                return ATOI_ERROR_CODE;
            }

            result -= digit; // calculate in negatives to support INT32_MIN
            ++str;
            ++digits;
        }

        if (!digits && !preceding_zero) {
            if constexpr (errorMode == tests::SafeAtoiErrorMode::Test) {
                return tests::ATOI_ERROR_CODE_NO_DATA;
            }

            return ATOI_ERROR_CODE;
        }

        if constexpr (trailingCharsCheckMode != SafeAtoiTrailingCharCheckMode::allowAll) {
            if constexpr (trailingCharsCheckMode == SafeAtoiTrailingCharCheckMode::allowOnlyWhitespace) {
                while (*str != '\0' && is_whitespace(*str)) ++str;
                if (*str != '\0') {
                    if constexpr (errorMode == tests::SafeAtoiErrorMode::Test) {
                        return tests::ATOI_ERROR_CODE_TRAILING_NON_WS_CHARS;
                    }

                    return ATOI_ERROR_CODE;
                }
            } else if constexpr (trailingCharsCheckMode == SafeAtoiTrailingCharCheckMode::allowOnlyNull) {
                if (*str != '\0') {
                    if constexpr (errorMode == tests::SafeAtoiErrorMode::Test) {
                        return tests::ATOI_ERROR_CODE_TRAILING_CHARS;
                    }

                    return ATOI_ERROR_CODE;
                }
            }
        }

        return negative ? result : -result;
    }

    namespace tests {
        static_assert(safe_atoi<SafeAtoiErrorMode::Test, SafeAtoiTrailingCharCheckMode::allowOnlyNull>(nullptr) == ATOI_ERROR_CODE_BAD_STRING);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test, SafeAtoiTrailingCharCheckMode::allowOnlyNull>("") == ATOI_ERROR_CODE_BAD_STRING);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test, SafeAtoiTrailingCharCheckMode::allowOnlyNull>("a123") == ATOI_ERROR_CODE_NO_DIGITS);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test, SafeAtoiTrailingCharCheckMode::allowOnlyNull>("-a123") == ATOI_ERROR_CODE_NO_DIGIT_AFTER_SIGN);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test, SafeAtoiTrailingCharCheckMode::allowOnlyNull>("- 123") == ATOI_ERROR_CODE_NO_DIGIT_AFTER_SIGN);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test, SafeAtoiTrailingCharCheckMode::allowOnlyNull>(" + 123") == ATOI_ERROR_CODE_NO_DIGIT_AFTER_SIGN);
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod, SafeAtoiTrailingCharCheckMode::allowOnlyNull>("1234567") == 1234567);
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod, SafeAtoiTrailingCharCheckMode::allowOnlyNull>("  -1234567890") == -1234567890);
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod, SafeAtoiTrailingCharCheckMode::allowOnlyNull>("  +1234567890") == 1234567890);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test, SafeAtoiTrailingCharCheckMode::allowOnlyNull>("  -1234567890 ") == ATOI_ERROR_CODE_TRAILING_CHARS);
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod, SafeAtoiTrailingCharCheckMode::allowOnlyWhitespace>("  -1234567890 ") == -1234567890);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test>("+ 42") == ATOI_ERROR_CODE_NO_DIGIT_AFTER_SIGN);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test, SafeAtoiTrailingCharCheckMode::allowAll>("       ") == ATOI_ERROR_CODE_TOO_MUCH_WS);

        // Too many leading whitespaces
        static_assert(safe_atoi<SafeAtoiErrorMode::Test>("       123") == ATOI_ERROR_CODE_TOO_MUCH_WS);

        // No digits after just whitespaces
        static_assert(safe_atoi<SafeAtoiErrorMode::Test>("     ") == ATOI_ERROR_CODE_NO_DATA);

        // Only a sign, no digits
        static_assert(safe_atoi<SafeAtoiErrorMode::Test>("+") == ATOI_ERROR_CODE_NO_DIGIT_AFTER_SIGN);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test>("-") == ATOI_ERROR_CODE_NO_DIGIT_AFTER_SIGN);

        // Too many digits (11)
        static_assert(safe_atoi<SafeAtoiErrorMode::Test>("12345678901") == ATOI_ERROR_CODE_TOO_MUCH_DIGITS);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test>("111111111111111") == ATOI_ERROR_CODE_TOO_MUCH_DIGITS);

        // INT32_MAX is not representable in negative space (this will overflow)
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod>("2147483647") == 2147483647);
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod>("00000000000000000002147483647") == 2147483647);
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod>("+00000000000000000002147483647") == 2147483647);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test>("2147483648") == ATOI_ERROR_CODE_OVERFLOW_DIGIT);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test>("2147483657") == ATOI_ERROR_CODE_OVERFLOW_RANK);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test>("99999999999999999") == ATOI_ERROR_CODE_OVERFLOW_RANK);

        static_assert(safe_atoi<SafeAtoiErrorMode::Prod>("-2147483648") == -2147483648);
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod>("-00000000000000000002147483648") == -2147483648);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test>("-2147483649") == ATOI_ERROR_CODE_OVERFLOW_DIGIT);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test>("-2147483658") == ATOI_ERROR_CODE_OVERFLOW_RANK);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test>("-99999999999999999") == ATOI_ERROR_CODE_OVERFLOW_RANK);

        // Accept +0 and -0
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod>("+0") == 0);
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod>("-0") == 0);
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod>("0") == 0);
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod>(" 0 ") == 0);
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod>(" 0") == 0);
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod>("0 ") == 0);

        static_assert(safe_atoi<SafeAtoiErrorMode::Test, SafeAtoiTrailingCharCheckMode::allowOnlyWhitespace>("123abc") == ATOI_ERROR_CODE_TRAILING_NON_WS_CHARS);
        static_assert(safe_atoi<SafeAtoiErrorMode::Test, SafeAtoiTrailingCharCheckMode::allowOnlyNull>("123abc") == ATOI_ERROR_CODE_TRAILING_CHARS);
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod, SafeAtoiTrailingCharCheckMode::allowAll>("123abc") == 123);

        // Max allowed whitespace (5) - should succeed
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod>("     42") == 42);
        // 6 ws - fail
        static_assert(safe_atoi<SafeAtoiErrorMode::Prod>("      42") == stringutil::ATOI_ERROR_CODE);
    }

}
