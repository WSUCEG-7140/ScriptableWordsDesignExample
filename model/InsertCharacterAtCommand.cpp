#include "InsertCharacterAtCommand.hpp"

namespace WSU {
namespace Model {

    /// \imp \ref R21_0 The script command can be looked up by a name that may occur in a script.
    StoredString::Command::FactoryInstaller
        InsertCharacterAtCommand::s_insertCharacterAtFactory {
            "insertCharacterAt",
            [](StoredString::p_t storedString_p, json args) {
                return StoredString::Command::command_p_t(
                    new InsertCharacterAtCommand { storedString_p, args });
            }
        };

    /// \imp \ref R3_0 The script command can be run.
    void InsertCharacterAtCommand::run()
    {
        getStoredString()->insertCharacterAtIndex(
            getArgs()["char"].get<std::string>()[0],
            getArgs()["at"].get<uint32_t>());
    }

} // namespace Model
} // namespace WSU
