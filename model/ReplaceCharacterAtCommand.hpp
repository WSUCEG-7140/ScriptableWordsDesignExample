#ifndef ReplaceCharacterAtCommand_hpp
#define ReplaceCharacterAtCommand_hpp

#include "GroupCommand.hpp"
#include "StoredString.hpp"
using json = nlohmann::json;

namespace WSU {
namespace Model {

    /// \imp \ref R60_0 This class provides a concrete implementation of the Command design pattern in order to replace a character at an index in a string.
    class ReplaceCharacterAtCommand : public ModelCommand<StoredString> {
    private:
        std::shared_ptr<GroupCommand> m_group_p { new GroupCommand };

    public:
        typedef ModelCommand<StoredString> base_t;

        ReplaceCharacterAtCommand(
            base_t::model_p_t storedString_p, const json& args)
            : base_t(storedString_p, args)
        {
            // Intentionally empty
        }

        /// \imp \ref R60_0
        virtual void run();

        base_t::model_p_t getStoredString() { return getModel_p(); }

        /// \imp \ref R12_0 reciprocal Commands are needed to implement Undo.
        /// @return The reciprocal Command
        virtual base_t::command_p_t getReciprocalCommand()
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
                auto command = base_t::makeCommandWithName("insertCharacterAt",
                    getStoredString(),
                    json::parse("{\"char\": \""
                        + std::to_string(characterToReplace)
                        + "\", \"at\":" + std::to_string(index) + "}"));
                newGroup_p->appendCommand(command);
            }
            return newGroup_p;
        }

        /// @brief As a side effect of creating this static instance, a FActory is registered to enable construction of Command instances based on the name of the Command.
        static base_t::FactoryInstaller s_insertCharacterAtFactory;
    };

} // namespace Model
} // namespace WSU

#endif /* InsertCharacterAtCommand_hpp */
