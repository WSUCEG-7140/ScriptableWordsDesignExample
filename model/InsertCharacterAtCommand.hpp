
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

    /// \imp \ref R3_0 This class provides a concrete implementation of the Command design pattern in order to insert a character at an index in a string.
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

        /// @brief As a side effect of creating this static instance, a FActory is registered to enable construction of Command instances based on the name of the Command.
        static StoredString::Command::FactoryInstaller
            s_insertCharacterAtFactory;
    };

} // namespace Model
} // namespace WSU

#endif /* InsertCharacterAtCommand_hpp */
