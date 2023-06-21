
#ifndef InsertCharacterAtCommand_hpp
#define InsertCharacterAtCommand_hpp

#include "StoredString.hpp"
#include "json.hpp"
#include <functional>
#include <memory>
#include <string>
using json = nlohmann::json;

namespace WSU {
namespace Model {

    /// \imp \ref R3_0 This class provides a concrete implementation of the Command design patter in order to insert a character at an index ina string.
    class InsertCharacterAtCommand : public StoredString::Command {
    public:
        InsertCharacterAtCommand(
            StoredString::p_t storedString_p, const json& args)
            : StoredString::Command(storedString_p, args)
        {
            // Intentionally empty
        }

        /// \imp \ref R3_0 \anchor DR3_5 \dreq DR3_5 Use to execute commands via
        /// a script, undo, or redo an operation, it is necessary to "run" the
        /// operation.
        virtual void run();

        /// \imp \ref Rx_0 In order to be able to undo a command, the reciprocal of the command is needed.
        /// \imp \ref Rx_2 In order to redo an undo command, the reciprocal of the command executed as part of undo is needed.
        virtual command_p_t makeReciprocalCommand();

        /// \imp \ref R3_0 In order to create a script of commands, it is necessary to have string representations of the commands
        /// \anchor DR3_6 \dreq DR3_6 A script will consist of a sequence of commands identified by their string representations
        /// anchor DR3_7  \dreq DR3_7 String representations are human readable
        virtual std::string getStringRepresentation()
        {
            return "Insert Character At";
        }

        /// @brief As a side effect of creating this static instance, a FActory is registered to enable construction of Command instances based on the name of the Command.
        static StoredString::Command::FactoryInstaller
            s_insertCharacterAtFactory;
    };

} // namespace Model
} // namespace WSU

#endif /* InsertCharacterAtCommand_hpp */
