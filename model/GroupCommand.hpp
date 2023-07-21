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
        Command::command_p_t run() override
        {
            std::shared_ptr<GroupCommand> newGroup_p { new GroupCommand };
            for (auto command_p : m_commands) {
                newGroup_p->appendCommand(command_p->run());
            }

            // Reverse the order because reciprocal commands must execute in
            // the reverse of the order the commands were run.
            std::reverse(
                newGroup_p->m_commands.begin(), newGroup_p->m_commands.end());

            return newGroup_p;
        }
    };

} // namespace Model
} // namespace WSU

#endif
