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
    controller.runCommandWithUndo(command);

    GTEST_ASSERT_EQ(storedString_p->getString(), "bcd");

    controller.undo();
    controller.undo();

    GTEST_ASSERT_EQ(storedString_p->getString(), initialString);
}

//////////////////////////////////////////////////////////////////////////////
/// \test @ref R14_0
TEST(R14_0, insertCharacterAt)
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

    controller.redo();

    GTEST_ASSERT_EQ(storedString_p->getString(), "!");
}

//////////////////////////////////////////////////////////////////////////////
/// \test @ref R14_0
TEST(R14_0, insertCharacterAt_multi)
{
    WSU::Controller::Controller controller {};

    auto storedString_p { controller.getCurrentStoredString_p() };
    auto initialString = storedString_p->getString();

    for (int32_t i = 0; i < 2000; ++i) {
        auto command
            = WSU::Model::StoredString::makeCommandWithName("insertCharacterAt",
                storedString_p, json::parse("{\"char\": \"!\", \"at\":0}"));
        controller.runCommandWithUndo(command);
    }
    GTEST_ASSERT_EQ(2000, storedString_p->getString().size());

    controller.undo();
    controller.undo();
    controller.undo();
    controller.undo();
    controller.undo();

    GTEST_ASSERT_EQ(1995, storedString_p->getString().size());

    controller.redo();
    controller.redo();
    controller.redo();
    controller.redo();
    controller.redo();

    GTEST_ASSERT_EQ(2000, storedString_p->getString().size());

    for (int32_t i = 0; i < 2000; ++i) {
        controller.undo();
    }
    GTEST_ASSERT_EQ(0, storedString_p->getString().size());

    for (int32_t i = 0; i < 2000; ++i) {
        controller.redo();
    }
    GTEST_ASSERT_EQ(2000, storedString_p->getString().size());
}
