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
    void InsertCharacterAtCommand::run()
    {
        getStoredString()->insertCharacterAtIndex(
            getArgs()["char"].get<std::string>()[0],
            getArgs()["at"].get<uint32_t>());
    }

} // namespace Model
} // namespace WSU
