#ifndef UndoRedoManager_hpp
#define UndoRedoManager_hpp

#include "Command.hpp"
#include <vector> // Used for stacks

namespace WSU {
namespace Controller {

    /// \imp \ref R12_0
    /// \imp \ref R14_0
    /// This class encapsulates data structures and operations related to collections of Command instances that can be undone or redone.
    ///
    /// Undo and Redo operations are part of the Controller subsystem because, the Undo and redo data structures are not part if the stringModel. The data structures are not saved with the Model. Undo and Redo can not be part of the View subsystem because the View subsystem is not allowed to know about the Model, but Undo and Redo need to know about the Model.
    /// Redo is implemented as undoing an Undo.
    ///
    /// @solid The use of pointers to the abstract Model::Command interface is an example of the Dependency Inversion principle of the S.O.L.I.D design principles. This class depends only on the abstract interface with no dependence on any concrete implementation.
    /// @solid The use of pointers to the abstract Model::Command interface relies upon the Liskov Substitution principle of the S.O.L.I.D design principles. There are never any instances of the Command class itself. Instead, pointers to instances of concrete subclasses of Command are used/substituted.
    class UndoRedoManager {
    public:
        typedef std::shared_ptr<Model::Command> command_p_t;

    private:
        /// @brief Storage for Commands to be executed when previously run Commands are undone.
        ///
        /// \imp \ref R12_0
        std::vector<command_p_t> m_undoStack;

        /// @brief Storage for Commands to be executed to redo previously undone Commands.
        ///
        /// \imp \ref R14_0
        std::vector<command_p_t> m_redoStack;

        ///  @brief this variable is true if and only if an Undo operation is
        /// in progress;
        /// \imp \ref R14_0
        bool m_isInUndo { false };

    public:
        /// @brief This function undoes whatever the last Command run via runCommandWithUndo() did.
        ///
        /// \imp \ref R12_0
        void undo()
        {
            m_isInUndo = true;
            if (0 < m_undoStack.size()) {
                auto command_p = m_undoStack.back();
                m_undoStack.pop_back();
                if (nullptr != command_p) {
                    runCommandWithUndo(command_p);
                }
            }
            m_isInUndo = false;
        }

        /// @brief This function redoes a command that was previous undone.
        ///
        /// \imp \ref R14_0
        void redo()
        {
            if (0 < m_redoStack.size()) {
                auto command_p = m_redoStack.back();
                m_redoStack.pop_back();
                if (nullptr != command_p) {
                    runCommandWithUndo(command_p);
                }
            }
        }

        /// @brief This function runs the specified Command and push the reciprocal Command on the undo stack for optional future undo.
        ///
        /// \imp \ref R12_0
        /// @param command_p The command to run
        void runCommandWithUndo(command_p_t command_p)
        {
            if (!m_isInUndo) {
                m_undoStack.push_back(command_p->getReciprocalCommand());
                command_p->run();
            } else {
                m_redoStack.push_back(command_p->getReciprocalCommand());
                command_p->run();
            }
        }
    };

} // namespace Controller
} // namespace WSU

#endif /* UndoRedoManager_hpp */