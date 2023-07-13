#include "Controller.hpp"
#include "ScriptInterpreter.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R12_0
TEST(R12_0, undoEmptyStack)
{
    WSU::Controller::Controller controller {};

    auto storedString_p { controller.getCurrentStoredString_p() };
    auto initialString = controller.getCurrentStoredString_p()->getString();

    controller.undo();

    GTEST_ASSERT_EQ(initialString, storedString_p->getString());
}

///////////////////////////////////////////////////////////////////////////////
/// \test @ref R12_0
TEST(R12_0, appendCharacter)
{
    WSU::Controller::Controller controller {};

    auto storedString_p { controller.getCurrentStoredString_p() };
    auto initialString = storedString_p->getString();

    auto command = WSU::Model::StoredString::makeCommandWithName(
        "appendCharacter", storedString_p, json::parse("{\"char\": \"#\"}"));
    controller.runCommandWithUndo(command);

    GTEST_ASSERT_EQ(storedString_p->getString(), "#");

    controller.undo();

    GTEST_ASSERT_EQ(storedString_p->getString(), initialString);
}

//////////////////////////////////////////////////////////////////////////////
/// \test @ref R12_0
TEST(R12_0, insertCharacterAt)
{
    WSU::Controller::Controller controller {};

    auto storedString_p { controller.getCurrentStoredString_p() };
    auto initialString = storedString_p->getString();

    auto command
        = WSU::Model::StoredString::makeCommandWithName("insertCharacterAt",
            storedString_p, json::parse("{\"char\": \"!\", \"at\":0}"));
    controller.runCommandWithUndo(command);

    GTEST_ASSERT_EQ(storedString_p->getString(), "!");

    controller.undo();

    GTEST_ASSERT_EQ(storedString_p->getString(), initialString);
}

//////////////////////////////////////////////////////////////////////////////
/// \test @ref R12_0
TEST(R12_0, removeCharacterAt)
{
    WSU::Controller::Controller controller {};

    auto storedString_p { controller.getCurrentStoredString_p() };

    std::string script {
        "[{\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"a\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"b\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"c\"}}, {\"command\":\"appendCharacter\", \"args\": "
        "{\"char\": \"d\"}}, {\"command\":\"insertCharacterAt\", \"args\": "
        "{\"char\": \"!\", \"at\":1}}]"
    };
    int32_t result { WSU::Model::ScriptInterpreter::interpret(
        storedString_p, script) };
    auto initialString = storedString_p->getString();

    auto command = WSU::Model::StoredString::makeCommandWithName(
        "removeCharacterAt", storedString_p, json::parse("{\"at\":0}"));
    controller.runCommandWithUndo(command);

    GTEST_ASSERT_EQ(storedString_p->getString(), "!bcd");

    controller.undo();

    GTEST_ASSERT_EQ(storedString_p->getString(), initialString);
}
