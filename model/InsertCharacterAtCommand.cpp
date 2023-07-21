#include "InsertCharacterAtCommand.hpp"

namespace WSU {
namespace Model {

    InsertCharacterAtCommand::base_t::FactoryInstaller
        InsertCharacterAtCommand::s_insertCharacterAtFactory {
            "insertCharacterAt",
            [](InsertCharacterAtCommand::base_t::model_p_t storedString_p,
                json args) {
                return Command::command_p_t(
                    new InsertCharacterAtCommand { storedString_p, args });
            }
        };

    /// \imp \ref R3_0 The script command can be run.
    InsertCharacterAtCommand::base_t::command_p_t
    InsertCharacterAtCommand::run()
    {
        auto result = getReciprocalCommand();
        getStoredString()->insertCharacterAtIndex(
            getArgs()["char"].get<std::string>()[0],
            getArgs()["at"].get<uint32_t>());
        return result;
    }

    InsertCharacterAtCommand::base_t::command_p_t
    InsertCharacterAtCommand::getReciprocalCommand()
    {
        auto args = json {};
        args["at"] = getArgs()["at"];

        auto reciprocalCommand_p = base_t::makeCommandWithName(
            "removeCharacterAt", getStoredString(), args);
        return reciprocalCommand_p;
    }

} // namespace Model
} // namespace WSU
