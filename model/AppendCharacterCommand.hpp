
#ifndef AppendCharacter_hpp
#define AppendCharacter_hpp

#include "StoredString.hpp"
#include "json.hpp"
#include <functional>
#include <memory>
#include <string>
using json = nlohmann::json;

namespace WSU {
namespace Model {

    /// \imp \ref R2_0 This class provides a concrete implementation of the Command design pattern in order to append a character to a string.
    class AppendCharacterCommand : public StoredString::Command {
    public:
        AppendCharacterCommand(
            StoredString::p_t storedString_p, const json& args)
            : StoredString::Command(storedString_p, args)
        {
            // Intentionally empty
        }

        /// \imp \ref R2_0
        virtual void run();

        /// @brief As a side effect of creating this static instance, a FActory is registered to enable construction of Command instances based on the name of the Command.
        static StoredString::Command::FactoryInstaller s_appendCharacterFactory;
    };

} // namespace Model
} // namespace WSU

#endif /* AppendCharacter_hpp */
