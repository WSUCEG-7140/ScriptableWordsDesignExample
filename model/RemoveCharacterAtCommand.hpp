
#ifndef RemoveCharacterAtCommand_hpp
#define RemoveCharacterAtCommand_hpp

#include "Command.hpp"
#include "StoredString.hpp"
using json = nlohmann::json;

namespace WSU {
namespace Model {

    /// \imp \ref R6_0 This class provides a concrete implementation of the @designpattern [Command Design Pattern](https://en.wikipedia.org/wiki/Command_pattern) in order to remove a character at an index in a string.
    class RemoveCharacterAtCommand : public ModelCommand<StoredString> {
    public:
        typedef ModelCommand<StoredString> base_t;

        RemoveCharacterAtCommand(
            base_t::model_p_t storedString_p, const json& args)
            : base_t(storedString_p, args)
        {
            // Intentionally empty
        }

        /// \imp \ref R3_0 \anchor DR3_5 \dreq DR3_5 Use to execute commands via
        /// a script, undo, or redo an operation, it is necessary to "run" the
        /// operation.
        command_p_t run() override;

        base_t::model_p_t getStoredString() { return getModel_p(); }

    private:
        /// @brief This function returns a command that performs the reciprocal operation of the Command instance. The reciprocal Command is a Command that undoes whatever this Command does.
        ///
        /// \imp \ref R12_0 reciprocal Commands are needed to implement Undo.
        /// @return The reciprocal Command
        virtual command_p_t getReciprocalCommand();

        /// @brief As a side effect of creating this static instance, a Factory is registered to enable construction of Command instances based on the name of the Command. @designpattern [Factory Methods](https://en.wikipedia.org/wiki/Factory_method_pattern)
        static base_t::FactoryInstaller s_removeCharacterAtFactory;
    };

} // namespace Model
} // namespace WSU

#endif /* RemoveCharacterAtCommand_hpp */
