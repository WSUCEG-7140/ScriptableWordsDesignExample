#include "StoredString.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R1_0
TEST(R1_0, zeroCharacters)
{
    WSU::Model::StoredString ss {};
    GTEST_ASSERT_EQ(0, ss.getString().size());
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R1_0
TEST(R1_0, moreThanZeroCharacters)
{
    WSU::Model::StoredString ss { "Hello, World!" };
    GTEST_ASSERT_EQ(13, ss.getString().size());
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    auto result = RUN_ALL_TESTS();

    exit(0);
    // There is no return statement because preceding exit() never returns
}
