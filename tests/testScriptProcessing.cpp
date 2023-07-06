#include "AppendCharacterCommand.hpp"
#include "InsertCharacterAtCommand.hpp"
#include "ScriptInterpreter.hpp"
#include "StoredString.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R3_0
TEST(R23_0, scriptProcessingOneCommand)
{
    std::shared_ptr<WSU::Model::StoredString> ss_p {
        new WSU::Model::StoredString { "" }
    };
    std::string script { "[{\"command\":\"appendCharacter\", \"args\": "
                         "{\"char\": \"#\"}}]" };
    int32_t result { WSU::Model::ScriptInterpreter::interpret(ss_p, script) };

    GTEST_ASSERT_EQ(0, result);
    GTEST_ASSERT_EQ(1, ss_p->getString().size());
    GTEST_ASSERT_EQ(ss_p->getString(), "#");
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R3_0
TEST(R23_0, scriptProcessingMultipleCommands)
{
    std::shared_ptr<WSU::Model::StoredString> ss_p {
        new WSU::Model::StoredString { "" }
    };
    std::string script {
        "[{\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"a\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"b\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"c\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"d\"}}, {\"command\":\"insertCharacterAt\", \"args\": "
        "{\"char\": \"!\", \"at\":1}}]"
    };
    int32_t result { WSU::Model::ScriptInterpreter::interpret(ss_p, script) };

    GTEST_ASSERT_EQ(0, result);
    GTEST_ASSERT_EQ(5, ss_p->getString().size());
    GTEST_ASSERT_EQ(ss_p->getString(), "a!bcd");
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R3_0
TEST(R23_0, scriptFailedCommand)
{
    std::shared_ptr<WSU::Model::StoredString> ss_p {
        new WSU::Model::StoredString { "" }
    };
    std::string script { "[{\"command\":\"?!/!@#$\", \"args\": "
                         "{\"char\": \"#\"}}]" };
    int32_t result { WSU::Model::ScriptInterpreter::interpret(ss_p, script) };

    GTEST_ASSERT_EQ(-1, result);
    GTEST_ASSERT_EQ(0, ss_p->getString().size());
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R3_0
TEST(R23_0, scriptProcessingRemoveAt0Command)
{
    std::shared_ptr<WSU::Model::StoredString> ss_p {
        new WSU::Model::StoredString { "" }
    };
    std::string script {
        "[{\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"a\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"b\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"c\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"d\"}}, {\"command\":\"removeCharacterAt\", \"args\": "
        "{\"at\":0}}]"
    };
    int32_t result { WSU::Model::ScriptInterpreter::interpret(ss_p, script) };

    GTEST_ASSERT_EQ(0, result);
    GTEST_ASSERT_EQ(3, ss_p->getString().size());
    GTEST_ASSERT_EQ(ss_p->getString(), "bcd");
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R3_0
TEST(R23_0, scriptProcessingRemoveAtEndCommand)
{
    std::shared_ptr<WSU::Model::StoredString> ss_p {
        new WSU::Model::StoredString { "" }
    };
    std::string script {
        "[{\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"a\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"b\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"c\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"d\"}}, {\"command\":\"removeCharacterAt\", \"args\": "
        "{\"at\":3}}]"
    };
    int32_t result { WSU::Model::ScriptInterpreter::interpret(ss_p, script) };

    GTEST_ASSERT_EQ(0, result);
    GTEST_ASSERT_EQ(3, ss_p->getString().size());
    GTEST_ASSERT_EQ(ss_p->getString(), "abc");
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R3_0
TEST(R23_0, scriptProcessingRemoveAtMiddleCommand)
{
    std::shared_ptr<WSU::Model::StoredString> ss_p {
        new WSU::Model::StoredString { "" }
    };
    std::string script {
        "[{\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"a\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"b\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"c\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"d\"}}, {\"command\":\"removeCharacterAt\", \"args\": "
        "{\"at\":2}}]"
    };
    int32_t result { WSU::Model::ScriptInterpreter::interpret(ss_p, script) };

    GTEST_ASSERT_EQ(0, result);
    GTEST_ASSERT_EQ(3, ss_p->getString().size());
    GTEST_ASSERT_EQ(ss_p->getString(), "abd");
}
