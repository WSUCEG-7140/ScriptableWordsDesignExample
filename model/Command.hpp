#ifndef Command_hpp
#define Command_hpp

#include "json.hpp"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
using json = nlohmann::json;

namespace WSU {
namespace Model {

    /// This is an abstract base class for Commands that may be run at a later time. The @designpattern [Command Design Pattern](https://en.wikipedia.org/wiki/Command_pattern) provides a mechanism to encapsulate all information needed to run a Command at a later time. Command instances may be used to implement a scripting language, implement Undo and Redo, or connect View subsystem components to Commands in the Presenter (Controller) subsystem.
    /// @imp @ref R21_0
    /// @imp @ref R23_0
    ///
    /// @solid This class is an example of the Interface Segregation principle of the S.O.L.I.D design. This class declares only the interface that all Command instances must provide and avoids coupling to any other part of the system.
    /// @solid This class is an example of the Single Responsibility principle of the S.O.L.I.D design. This class declares only the interface that all Command instances must provide and avoids coupling to any other part of the system.
    /// @solid This class is an example of the Dependency Inversion principle of the S.O.L.I.D design. This class declares only the interface that all Command instances must provide and avoids coupling to any other part of the system. Other parts of teh system are implemented in terms of this interface without needing to know about concrete subclasses of this class. By not needing to know about specific subclasses, other depends on this high level interface and not any low level implementation.
    class Command {
    public:
        typedef std::shared_ptr<Command> command_p_t;

    protected:
        ///\anchor DR3_2 \dreq DR3_2 In C++, all classes that have one or more virtual method are required to have a virtual destructor.
        virtual ~Command()
        { /* Intentionally Empty */
        }

    public:
        /// \imp \ref R3_0 \anchor DR3_5 \dreq DR3_5 Use to execute commands via a script, undo, or redo an operation, it is necessary to "run" the operation.
        /// @solid This class applies the "Open for Extension but Closed for Modifications" principle of the S.O.L.I.D design principles. There may be many subclasses that each extend this class by implementing the run() member function, but no class overrides the operator()() member function. Polymorphism enables instances of subclasses to use the operator()() member without ever needing to override the operator()() member.
        /// \return A command that is reciprocal to the command being run i.e. a command that will undo whatever the command being run does.
        virtual command_p_t run() = 0;

        /// C++ has a well established idiom know as [Functors](https://www.geeksforgeeks.org/functors-in-cpp). Functors are a C++ language level implementation of the @designpattern [Command Design Pattern](https://en.wikipedia.org/wiki/Command_pattern) particularly when combined with C++11 std::bind and std::function. Providing this operator makes it seamless to use this class as a Functor along with std::bind and std::function.
        /// \anchor DR_1_0 \dreq DR_1_0: Any implementation of a Design Pattern should incorporate related language idioms as a matter of courtesy for other practitioners of the language.
        /// \return A command that is reciprocal to the command being run i.e. a command that will undo whatever the command being run does.
        command_p_t operator()() { return run(); }
    };

    /// This is an abstract base class for Commands that may modify the contents of the Model subsystem. Scripts are composed of a sequence of Commands. Undo and Redo are implemented using Commands.
    /// @imp @ref R21_0
    /// @imp @ref R23_0
    /// @solid This class relies upon the Liskov Substitution principle of the S.O.L.I.D design principles. There are never any instances of the ModelCommand class itself. Instead, pointers to instances of concrete subclasses of ModelCommand are used/substituted.
    template <typename MODEL_T> class ModelCommand : public Command {
    public:
        typedef ModelCommand<MODEL_T> own_t;
        typedef typename Command::command_p_t command_p_t;
        typedef std::shared_ptr<MODEL_T> model_p_t;

        /// Type for Factory Methods. Having a standard type simplifies use of @designpattern [Factory Methods](https://en.wikipedia.org/wiki/Factory_method_pattern) because the caller need not know any details (like special arguments) about the object(s) created by the Factory Method.
        typedef std::function<command_p_t(model_p_t model_p, const json& args)>
            factory_t;

        /// @brief This is the type used to store name to Factory associations
        typedef std::unordered_map<std::string, factory_t> factoryMap_t;

    private:
        /// @solid This demonstrates the Don't Repeat Yourself principle of S.O.L.I.D. design principles. Many Command subclasses need access to a Model and some arguments. By placing those properties here, they do not need to be repeated in every subclass.
        /// @brief JSON encode arguments to the command
        json m_args;

        /// @brief Pointer to the Model to be modified by the Command
        model_p_t m_model_p;

    protected:
        ///\anchor DR3_2 \dreq DR3_2 In C++, all classes that have one or more virtual method are required to have a virtual destructor.
        virtual ~ModelCommand()
        { /* Intentionally Empty */
        }

        /// \imp \ref R23_0 In order to recognize commands by their names in a script, it is necessary to be able to lookup commands by name. This function returns a map from name to a Factory that creates instances of the command with that name. See [Factory Design Pattern](https://www.oodesign.com/factory-pattern.html)
        static factoryMap_t& _getNameToFactoryMap()
        {
            static own_t::factoryMap_t map {};

            return map;
        }

    public:
        ModelCommand(model_p_t model_p, const json& args)
            : m_model_p(model_p)
            , m_args(args)
        {
            // Intentionally empty
        }

        const json& getArgs() const { return m_args; }

        model_p_t getModel_p() const { return m_model_p; }

        /// \imp \ref R3_1 In order to recognize commands by their names in a script, it is necessary to be able to lookup commands by name. This function returns a map from name to a Factory that creates instances of the command with that name. See [Factory Design Pattern](https://www.oodesign.com/factory-pattern.html)
        static const factoryMap_t& getNameToFactoryMap()
        {
            return own_t::_getNameToFactoryMap();
        }

        /// \imp \ref R3_1 In order to recognize commands by their names in a script, it is necessary to be able to lookup commands by name. This method provides a mechanism to associate a command Factory with the name of the command. A command Factory Method is an implantation of the @designpattern [Factory Method Design Pattern](https://en.wikipedia.org/wiki/Factory_method_pattern).
        ///
        ///\args factory : The Factory to be associated with the name, name.
        ///\args name : The name of a Command Factory
        static void registerFactoryWithName(factory_t factory, std::string name)
        {
            own_t::_getNameToFactoryMap()[name] = factory;
        }

        /// @brief  \imp \ref R3_0 As a side effect of construction, each instance of this class registers a Factory for creating Commands
        class FactoryInstaller {
        public:
            FactoryInstaller(const std::string& name, factory_t factory)
            {
                own_t::registerFactoryWithName(factory, name);
            }
        };

        /// \imp \ref R3_1 Create a Command instance using the named Factory, stored string, and arguments. The name is a human readable identifier that may be used in scripts. The arguments are [JSON](https://www.json.org/json-en.html) formatted key/value pairs where each key is a string argument name and each value is a JSON value type.
        /// \ref R3_1_1 As an implementation detail, JSON is chosen as a human readable format.
        ///
        ///\arg name : The name of a Command
        ///\arg model_p : Pointer to the Model to be modified by the Command
        ///\arg ags : JSON formatted arguments to the Command
        static command_p_t makeCommandWithName(
            std::string name, model_p_t model_p, const json& args)
        {
            command_p_t result { nullptr };
            auto factoryIt = ModelCommand::getNameToFactoryMap().find(name);

            if (getNameToFactoryMap().end() != factoryIt) {
                auto factory = factoryIt->second;
                if (nullptr != factory) {
                    result = factory(model_p, args);
                }
            }
            return result;
        }
    };

} // namespace Model
} // namespace WSU

#endif /* Command_hpp */
