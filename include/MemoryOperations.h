#ifndef MemoryOperations_H
#define MemoryOperations_H

#include <cstddef> // fors size_t

class Pet;

///////////////////////////////////////////////////////////////////////////////
/// This class encapsulates memory operations that students must write for
/// CS-3100 at Wright State University Summer 2023.
class MemoryOperations {
public:
  ///////////////////////////////////////////////////////////////////////////
  /// This function copies Pet instances from memory at source_p to memory at
  /// destination_p. To avoid overflows, the amount of memory pointed to by
  /// both the destination_p and source_p must be sufficient to store at
  /// least count elements. This function is analogous to
  /// https://www.man7.org/linux/man-pages/man3/memmove.3.html
  ///
  ///\param destination_p : pointer to the  memory where the content is to be
  /// copied \param source_p : pointer to the source of data to be copied \param
  /// count : the number of elements to copy \return destination_p
  static Pet *memmove(Pet *destination_p, const Pet *source_p, size_t count);
};

#endif // MemoryOperations_H
