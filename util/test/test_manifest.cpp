#include <gtest/gtest.h>

#include <rusefi/manifest.h>

TEST(Util, manifest) {
    int year = compilationYear();
    ASSERT_TRUE(year >= 2023 && year <= 2123);

    int month = compilationMonth();
    ASSERT_TRUE(month >= 1 && month <= 12);
}