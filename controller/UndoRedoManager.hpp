#ifndef UndoRedoManager_hpp
#define UndoRedoManager_hpp

#include "StoredString.hpp"
#include <string>
#include <vector>

namespace WSU {
namespace Controller {

    /// \imp \ref R12_0
    /// This class encapsulates data structures and operations related to collections of Command instances that can be undone or redone.
    ///
    /// Undo and Redo operations are part of the Controller subsystem because, the Undo and redo data structures are not part if the Model. The data structures are not save with the Model. Undo and Redo can not be part of the Presenter subsystem because teh Presenter subsystem is not allowed to know about the Model, but Undo and Redo need to know about the Model.
    class UndoRedoManager {
    private:
        std::vector<WSU::Model::StoredString::command_p_t> m_undoStack;

    public:
        void undo()
        {
            if (0 < m_undoStack.size()) {
                auto command_p = m_undoStack.back();
                m_undoStack.pop_back();
                if (nullptr != command_p) {
                    command_p->run();
                }
            }
        }

        void runCommandWithUndo(WSU::Model::StoredString::command_p_t command_p)
        {
            command_p->run();
            m_undoStack.push_back(command_p->getReciprocalCommand());
        }
    };

} // namespace Controller
} // namespace WSU

#endif /* UndoRedoManager_hpp */