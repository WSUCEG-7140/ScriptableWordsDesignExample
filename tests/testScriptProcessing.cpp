#include "AppendCharacterCommand.hpp"
#include "InsertCharacterAtCommand.hpp"
#include "ScriptInterpreter.hpp"
#include "StoredString.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

typedef WSU::Model::StoredString model_t;
typedef WSU::Model::ModelCommand<model_t> command_t;
typedef typename command_t::model_p_t model_p_t;
typedef WSU::Model::ScriptInterpreter<command_t> interpreter_t;

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R23_0
/// \test @ref R21_0
/// \test @ref R2_0
TEST(R23_0, scriptProcessingOneCommand)
{
    model_p_t ss_p { new WSU::Model::StoredString { "" } };
    std::string script { "[{\"command\":\"appendCharacter\", \"args\": "
                         "{\"char\": \"#\"}}]" };
    int32_t result { interpreter_t::interpret(ss_p, script) };

    GTEST_ASSERT_EQ(0, result);
    GTEST_ASSERT_EQ(1, ss_p->getString().size());
    GTEST_ASSERT_EQ(ss_p->getString(), "#");
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R23_0
/// \test @ref R21_0
/// \test @ref R2_0
/// \test @ref R3_0
TEST(R23_0, scriptProcessingMultipleCommands)
{
    model_p_t ss_p { new WSU::Model::StoredString { "" } };
    std::string script {
        "[{\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"a\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"b\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"c\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"d\"}}, {\"command\":\"insertCharacterAt\", \"args\": "
        "{\"char\": \"!\", \"at\":1}}]"
    };
    int32_t result { interpreter_t::interpret(ss_p, script) };

    GTEST_ASSERT_EQ(0, result);
    GTEST_ASSERT_EQ(5, ss_p->getString().size());
    GTEST_ASSERT_EQ(ss_p->getString(), "a!bcd");
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R23_0
TEST(R23_0, scriptFailedCommand)
{
    model_p_t ss_p { new WSU::Model::StoredString { "" } };
    std::string script { "[{\"command\":\"?!/!@#$\", \"args\": "
                         "{\"char\": \"#\"}}]" };
    int32_t result { interpreter_t::interpret(ss_p, script) };

    GTEST_ASSERT_EQ(-1, result);
    GTEST_ASSERT_EQ(0, ss_p->getString().size());
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R23_0
/// \test @ref R3_0
/// \test @ref R2_0
/// \test @ref R6_0
TEST(R6_0, scriptProcessingRemoveAt0Command)
{
    model_p_t ss_p { new WSU::Model::StoredString { "" } };
    std::string script {
        "[{\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"a\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"b\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"c\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"d\"}}, {\"command\":\"removeCharacterAt\", \"args\": "
        "{\"at\":0}}]"
    };
    int32_t result { interpreter_t::interpret(ss_p, script) };

    GTEST_ASSERT_EQ(0, result);
    GTEST_ASSERT_EQ(3, ss_p->getString().size());
    GTEST_ASSERT_EQ(ss_p->getString(), "bcd");
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R23_0
/// \test @ref R6_0
TEST(R6_0, scriptProcessingRemoveAtEndCommand)
{
    model_p_t ss_p { new WSU::Model::StoredString { "" } };
    std::string script {
        "[{\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"a\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"b\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"c\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"d\"}}, {\"command\":\"removeCharacterAt\", \"args\": "
        "{\"at\":3}}]"
    };
    int32_t result { interpreter_t::interpret(ss_p, script) };

    GTEST_ASSERT_EQ(0, result);
    GTEST_ASSERT_EQ(3, ss_p->getString().size());
    GTEST_ASSERT_EQ(ss_p->getString(), "abc");
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R6_0
/// \test @ref R23_0
TEST(R6_0, scriptProcessingRemoveAtMiddleCommand)
{
    model_p_t ss_p { new WSU::Model::StoredString { "" } };
    std::string script {
        "[{\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"a\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"b\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"c\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"d\"}}, {\"command\":\"removeCharacterAt\", \"args\": "
        "{\"at\":2}}]"
    };
    int32_t result { interpreter_t::interpret(ss_p, script) };

    GTEST_ASSERT_EQ(0, result);
    GTEST_ASSERT_EQ(3, ss_p->getString().size());
    GTEST_ASSERT_EQ(ss_p->getString(), "abd");
}
