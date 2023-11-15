#pragma once

// https://stackoverflow.com/questions/46899202/how-to-split-date-and-time-macros-into-individual-components-for-variabl
constexpr int compilationDatePortion(const int startIndex, const int totalChars) {

    int result = 0;
    for (int i = startIndex + totalChars - 1, multiplier = 1;
         i >= startIndex;
         i--, multiplier *= 10) {
        const char c = __DATE__[i];
        if (c != ' ') {
            result += (c - '0') * multiplier;
        }
    }

    return result;
}

constexpr int compilationYear() {
    return compilationDatePortion(7, 4);
}

constexpr int compilationDay() {
    return compilationDatePortion(4, 2);
}

// https://stackoverflow.com/questions/19760221/c-get-the-month-as-number-at-compile-time

#define __COMPILATION_MONTH__ (\
  __DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? 1 : 6) \
: __DATE__ [2] == 'b' ? 2 \
: __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 3 : 4) \
: __DATE__ [2] == 'y' ? 5 \
: __DATE__ [2] == 'l' ? 7 \
: __DATE__ [2] == 'g' ? 8 \
: __DATE__ [2] == 'p' ? 9 \
: __DATE__ [2] == 't' ? 10 \
: __DATE__ [2] == 'v' ? 11 \
: 12)

constexpr int compilationMonth() {
    return __COMPILATION_MONTH__;
}
