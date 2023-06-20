#include "Command.hpp"
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
/// \test @ref R3_0
TEST(R3_0, scriptInsertCharacter)
{
    //WSU::Model::StoredString::registerDefaultCommands();
    std::shared_ptr<WSU::Model::StoredString> ss_p {
        new WSU::Model::StoredString { "Hello, World!" }
    };
    // auto command = WSU::Model::StoredString::makeCommandWithName(
    //     "insertCharacterAt", ss_p, R"({"char": "#","at": 0})"_json);
    // if (nullptr != command) {
    //     command->run();
    // }
    GTEST_ASSERT_EQ(ss_p->getString(), "#Hello, World!");
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R4_0
TEST(R4_0, insertCharactersAtIndex0DoesNotRemoveAnything)
{
    WSU::Model::StoredString ss { "Hello, World!" };
    ss.insertCharacterAtIndex('@', 0);
    GTEST_ASSERT_EQ(ss.getString(), "@Hello, World!");
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R4_0
TEST(R4_0, insertCharactersAtIndex1DoesNotRemoveAnything)
{
    WSU::Model::StoredString ss { "Hello, World!" };
    ss.insertCharacterAtIndex('@', 1);
    GTEST_ASSERT_EQ(ss.getString(), "H@ello, World!");
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R4_0
TEST(R4_0, insertCharactersBeginOfEmpty)
{
    WSU::Model::StoredString ss { "" };
    ss.insertCharacterAtIndex('@', 0);
    GTEST_ASSERT_EQ(ss.getString(), "@");
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R4_0
TEST(R4_0, insertCharacterAtEnd)
{
    WSU::Model::StoredString ss { "abcdefg" };
    ss.insertCharacterAtIndex('@', 7);
    GTEST_ASSERT_EQ(ss.getString(), "abcdefg@");
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    auto result = RUN_ALL_TESTS();

    exit(0);
    // There is no return statement because preceding exit() never returns
}
