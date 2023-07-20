#ifndef GroupCommand_H
#define GroupCommand_H

#include "Command.hpp"

/// \imp \ref R17_0 Instances of this class group commands so that the commands may be undone or redone as a group instead of one by one.
class GroupCommand : : public ModelCommand<StoredString> {
public:
    typedef ModelCommand<StoredString> base_t;

    GroupCommand(base_t::model_p_t storedString_p, const json& args)
        : base_t(storedString_p, args)
    {
        // Intentionally empty
    }
};

#endif
