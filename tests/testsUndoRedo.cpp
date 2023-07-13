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
TEST(R12_0, undoNotEmptyStack)
{
    WSU::Controller::Controller controller {};

    auto storedString_p { controller.getCurrentStoredString_p() };
    auto initialString = storedString_p->getString();

    std::string script { "[{\"command\":\"appendCharacter\", \"args\": "
                         "{\"char\": \"#\"}}]" };
    auto command = WSU::Model::StoredString::makeCommandWithName(
        "appendCharacter", storedString_p, json::parse("{\"char\": \"#\"}"));
    controller.runCommandWithUndo(command);

    GTEST_ASSERT_EQ(storedString_p->getString(), "#");

    controller.undo();

    GTEST_ASSERT_EQ(storedString_p->getString(), initialString);
}
