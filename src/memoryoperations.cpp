#include "MemoryOperations.h"
#include "Pet.h"

///////////////////////////////////////////////////////////////////////////////
Pet* MemoryOperations::memmove(
    Pet* destination_p, const Pet* source_p, size_t count)
{
    if (destination_p > source_p) {
        for (int32_t i = count - 1; i >= 0; --i) {
            //destination_p[i] = source_p[i];
        }
    } else {
        Pet* current_p = destination_p;
        const Pet* sourceEnd_p = source_p + count;
        while (source_p < sourceEnd_p) {
            *current_p++ = *source_p++;
        }
    }
    return destination_p;
}
