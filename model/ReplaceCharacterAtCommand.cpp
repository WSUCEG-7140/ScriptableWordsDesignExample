#include "ReplaceCharacterAtCommand.hpp"
#include "GroupCommand.hpp"

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
        std::shared_ptr<GroupCommand> newGroup_p { new GroupCommand };
        const auto index = getArgs()["at"].get<uint32_t>();
        const auto newCharacter = getArgs()["char"].get<std::string>()[0];

        {
            auto command = base_t::makeCommandWithName("removeCharacterAt",
                getStoredString(),
                json::parse("{\"at\":" + std::to_string(index) + "}"));
            newGroup_p->appendCommand(command);
        }
        {
            std::string argsString { "{\"char\": \"" };
            argsString.push_back(newCharacter);
            argsString += "\", \"at\":" + std::to_string(index) + "}";
            auto command = base_t::makeCommandWithName("insertCharacterAt",
                getStoredString(), json::parse(argsString));
            newGroup_p->appendCommand(command);
        }

        newGroup_p->run();
    }

    /// \imp \ref R12_0 reciprocal Commands are needed to implement Undo.
    /// @return The reciprocal Command
    ReplaceCharacterAtCommand::base_t::command_p_t
    ReplaceCharacterAtCommand::getReciprocalCommand()
    {
        std::shared_ptr<GroupCommand> newGroup_p { new GroupCommand };
        const auto index = getArgs()["at"].get<uint32_t>();
        auto characterToReplace = getStoredString()->getString()[index];

        {
            auto command = base_t::makeCommandWithName("removeCharacterAt",
                getStoredString(),
                json::parse("{\"at\":" + std::to_string(index) + "}"));
            newGroup_p->appendCommand(command);
        }
        {
            std::string argsString { "{\"char\": \"" };
            argsString.push_back(characterToReplace);
            argsString += "\", \"at\":" + std::to_string(index) + "}";
            auto command = base_t::makeCommandWithName("insertCharacterAt",
                getStoredString(), json::parse(argsString));
            newGroup_p->appendCommand(command);
        }
        return newGroup_p;
    }

} // namespace Model
} // namespace WSU
