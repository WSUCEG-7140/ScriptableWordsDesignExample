#include "ReplaceCharacterAtCommand.hpp"

namespace WSU {
namespace Model {

    ReplaceCharacterAtCommand::base_t::FactoryInstaller
        ReplaceCharacterAtCommand::s_insertCharacterAtFactory {
            "replaceCharacterAt",
            [](ReplaceCharacterAtCommand::base_t::model_p_t storedString_p,
                json args) {
                return Command::command_p_t(
                    new ReplaceCharacterAtCommand { storedString_p, args });
            }
        };

    /// \imp \ref R3_0 The script command can be run.
    void ReplaceCharacterAtCommand::run()
    {
        const auto index = getArgs()["at"].get<uint32_t>();
        getStoredString()->removeCharacterAtIndex(index);
        getStoredString()->insertCharacterAtIndex(
            getArgs()["char"].get<std::string>()[0], index);
    }

} // namespace Model
} // namespace WSU
