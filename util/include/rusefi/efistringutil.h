#pragma once

#define ATOI_ERROR_CODE 311223344

#define TO_LOWER(x) (((x)>='A' && (x)<='Z') ? (x) - 'A' + 'a' : (x))

int indexOf(const char *string, char ch);
bool strEqualCaseInsensitive(const char *str1, const char *str2);
bool strEqual(const char *str1, const char *str2);
int atoi(const char *string) noexcept;
float atoff(const char*);
