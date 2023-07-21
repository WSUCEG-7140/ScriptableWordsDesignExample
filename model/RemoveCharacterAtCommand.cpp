#include "RemoveCharacterAtCommand.hpp"
#include <iostream>

namespace WSU {
namespace Model {

    /// \imp \ref R21_0 The script command can be looked up by a name that may occur in a script.
    RemoveCharacterAtCommand::base_t::FactoryInstaller
        RemoveCharacterAtCommand::s_removeCharacterAtFactory {
            "removeCharacterAt",
            [](StoredString::p_t storedString_p, json args) {
                return RemoveCharacterAtCommand::base_t::command_p_t(
                    new RemoveCharacterAtCommand { storedString_p, args });
            }
        };

    /// \imp \ref R6_0 The script command can be run.
    RemoveCharacterAtCommand::base_t::command_p_t
    RemoveCharacterAtCommand::run()
    {
        auto result = getReciprocalCommand();
        getStoredString()->removeCharacterAtIndex(
            getArgs()["at"].get<uint32_t>());
        return result;
    }

    RemoveCharacterAtCommand::base_t::command_p_t
    RemoveCharacterAtCommand::getReciprocalCommand()
    {
        json args {};
        auto index = getArgs()["at"];
        args["char"] = std::string { getStoredString()->getString()[index] };
        args["at"] = index;

        auto reciprocalCommand_p = base_t::makeCommandWithName(
            "insertCharacterAt", getStoredString(), args);
        return reciprocalCommand_p;
    }
} // namespace Model
} // namespace WSU
