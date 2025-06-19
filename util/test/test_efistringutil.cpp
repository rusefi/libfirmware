#include <gtest/gtest.h>

#include <rusefi/efistringutil.h>

TEST(Util_String, equalsIgnoreCase) {
    ASSERT_FALSE(rusefi::stringutil::strEqualCaseInsensitive("a", "b"));
    ASSERT_TRUE(rusefi::stringutil::strEqualCaseInsensitive("a", "A"));
}
