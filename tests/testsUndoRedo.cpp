#include "Controller.hpp"
#include <gtest/gtest.h>

typedef WSU::Model::ModelCommand<WSU::Model::StoredString> command_t;
typedef typename command_t::command_p_t command_p_t;
typedef WSU::Model::ScriptInterpreter<command_t> interpreter_t;

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

    auto command = command_t::makeCommandWithName(
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

    auto command = command_t::makeCommandWithName("insertCharacterAt",
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
    int32_t result { interpreter_t::interpret(storedString_p, script) };
    auto initialString = storedString_p->getString();

    auto command = command_t::makeCommandWithName(
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

    auto command = command_t::makeCommandWithName("insertCharacterAt",
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
        auto command = command_t::makeCommandWithName("insertCharacterAt",
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

//////////////////////////////////////////////////////////////////////////////
/// \test @ref R14_0
TEST(R60_0, replaceCharacterAt)
{
    WSU::Controller::Controller controller {};

    auto storedString_p { controller.getCurrentStoredString_p() };

    {
        auto command = command_t::makeCommandWithName("insertCharacterAt",
            storedString_p, json::parse("{\"char\": \"!\", \"at\":0}"));
        controller.runCommandWithUndo(command);
    }
    {
        auto command = command_t::makeCommandWithName("insertCharacterAt",
            storedString_p, json::parse("{\"char\": \"!\", \"at\":0}"));
        controller.runCommandWithUndo(command);
    }
    {
        auto command = command_t::makeCommandWithName("insertCharacterAt",
            storedString_p, json::parse("{\"char\": \"!\", \"at\":0}"));
        controller.runCommandWithUndo(command);
    }
    {
        auto command = command_t::makeCommandWithName("replaceCharacterAt",
            storedString_p, json::parse("{\"char\": \"-\", \"at\":1}"));
        controller.runCommandWithUndo(command);
    }

    GTEST_ASSERT_EQ(storedString_p->getString(), "!-!");

    controller.undo();
    GTEST_ASSERT_EQ(storedString_p->getString(), "!!!");

    controller.redo();
    GTEST_ASSERT_EQ(storedString_p->getString(), "!-!");

    {
        auto command = command_t::makeCommandWithName("replaceCharacterAt",
            storedString_p, json::parse("{\"char\": \"@\", \"at\":0}"));
        controller.runCommandWithUndo(command);
    }

    GTEST_ASSERT_EQ(storedString_p->getString(), "@-!");

    controller.undo();
    GTEST_ASSERT_EQ(storedString_p->getString(), "!-!");

    controller.redo();
    GTEST_ASSERT_EQ(storedString_p->getString(), "@-!");
}
