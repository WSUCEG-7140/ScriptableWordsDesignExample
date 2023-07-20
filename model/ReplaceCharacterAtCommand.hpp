#ifndef ReplaceCharacterAtCommand_hpp
#define ReplaceCharacterAtCommand_hpp

#include "GroupCommand.hpp"
#include "StoredString.hpp"
using json = nlohmann::json;

namespace WSU {
namespace Model {

    /// \imp \ref R60_0 This class provides a concrete implementation of the @designpattern [Command Design Pattern](https://en.wikipedia.org/wiki/Command_pattern) in order to replace a character at an index in a string.
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
        virtual base_t::command_p_t getReciprocalCommand();

        /// @brief As a side effect of creating this static instance, a Factory is registered to enable construction of Command instances based on the name of the Command. @designpattern [Factory Methods](https://en.wikipedia.org/wiki/Factory_method_pattern)
        static base_t::FactoryInstaller s_insertCharacterAtFactory;
    };

} // namespace Model
} // namespace WSU

#endif /* InsertCharacterAtCommand_hpp */
