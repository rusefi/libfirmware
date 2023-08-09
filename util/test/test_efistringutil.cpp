#include <gtest/gtest.h>

#include <rusefi/efistringutil.h>

TEST(Util_String, equalsIgnoreCase) {
    ASSERT_FALSE(strEqualCaseInsensitive("a", "b"));
    ASSERT_TRUE(strEqualCaseInsensitive("a", "A"));
}
