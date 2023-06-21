#include "InsertCharacterAtCommand.hpp"

namespace WSU {
namespace Model {

    StoredString::Command::FactoryInstaller
        InsertCharacterAtCommand::s_insertCharacterAtFactory {
            "insertCharacterAt",
            [](StoredString::p_t storedString_p, json args) {
                return StoredString::Command::command_p_t(
                    new InsertCharacterAtCommand { storedString_p, args });
            }
        };

    void InsertCharacterAtCommand::run()
    {
        getStoredString()->insertCharacterAtIndex(
            getArgs()["char"].get<std::string>()[0],
            getArgs()["at"].get<uint32_t>());
    }

    /// \imp \ref Rx_0 In order to be able to undo a command, the reciprocal of the command is needed.
    /// \imp \ref Rx_2 In order to redo an undo command, the reciprocal of the command executed as part of undo is needed.
    StoredString::Command::command_p_t
    InsertCharacterAtCommand::makeReciprocalCommand()
    {
        return nullptr;
    }

} // namespace Model
} // namespace WSU
