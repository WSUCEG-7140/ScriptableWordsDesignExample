#ifndef GroupCommand_H
#define GroupCommand_H

#include "Command.hpp"
#include <vector>

namespace WSU {
namespace Model {

    /// \imp \ref R17_0 Instances of this class group commands so that the commands may be undone or redone as a group instead of one by one.
    class GroupCommand : public Command {
    private:
        /// @brief The collection of commands in the group
        std::vector<Command::command_p_t> m_commands;

    public:
        typedef Command base_t;

        /// @brief This function appends a command to the collection of commands encapsulated by the instance of GroupCommand that is running this function.
        /// @param command_p The command to append
        void appendCommand(Command::command_p_t command_p)
        {
            m_commands.push_back(command_p);
        }

        /// \imp \ref R17_0 Run all of the commands in teh group
        void run() override
        {
            for (auto command_p : m_commands) {
                command_p->run();
            }
        }

        /// \imp \ref R17_0
        /// @return This function returns a new GroupCommand instance containing the reciprocal commands in the collection of commands encapsulated by the GroupCommand instance running this function.
        Command::command_p_t getReciprocalCommand() override
        {
            auto newGroup = std::shared_ptr<GroupCommand> { new GroupCommand };

            for (auto command_p : m_commands) {
                newGroup->appendCommand(command_p->getReciprocalCommand());
            }

            return newGroup;
        }
    };

} // namespace Model
} // namespace WSU

#endif
