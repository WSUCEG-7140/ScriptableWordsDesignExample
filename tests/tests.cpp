#include "MemoryOperations.h"
#include "Pet.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

///////////////////////////////////////////////////////////////////////////////
/// Immutable test data
static const Pet s_pets[5] { { 12, "Hershey" }, { 15, "Jade" }, { 14, "Abby" },
    { 12, "Sooner" }, { 2, "Elsa" } };

///////////////////////////////////////////////////////////////////////////////
/// Compile time constant calculated from amount of memory used
static constexpr size_t s_petsNumber { sizeof(s_pets) / sizeof(Pet) };

///////////////////////////////////////////////////////////////////////////////
/// Comparison used by test cases to determine pass/fail
static bool s_equals(const Pet* left_p, const Pet* right_p)
{
    return (left_p->m_age == right_p->m_age)
        && (left_p->m_name == right_p->m_name);
}

///////////////////////////////////////////////////////////////////////////////
static bool s_allEqual(const Pet left[], const Pet right[], size_t count)
{
    bool result { true };
    while (result && 0 < count) {
        --count;
        result = s_equals(&left[count], &right[count]);
    }
    return result;
}
///////////////////////////////////////////////////////////////////////////////
TEST(memoryoperations, init)
{
    Pet pets[1];
    Pet pet0 { 0, "Anonymous" };
    GTEST_ASSERT_EQ(true, s_equals(&pet0, &pets[0]));
}

///////////////////////////////////////////////////////////////////////////////
TEST(memoryoperations, memmoveCopy)
{ // verify that memmove actually copies
    Pet pets[s_petsNumber];
    MemoryOperations::memmove(pets, s_pets, s_petsNumber);
    GTEST_ASSERT_EQ(true, s_allEqual(pets, s_pets, s_petsNumber));
}

///////////////////////////////////////////////////////////////////////////////
TEST(memoryoperations, memmoveCopyOverSelf)
{ // verify copy collection over itself does not change collection
    Pet pets[s_petsNumber];
    MemoryOperations::memmove(pets, s_pets, s_petsNumber);
    MemoryOperations::memmove(pets, pets, s_petsNumber);
    GTEST_ASSERT_EQ(true, s_allEqual(pets, s_pets, s_petsNumber));
}

///////////////////////////////////////////////////////////////////////////////
TEST(memoryoperations, memmoveCopyOverSelfNext)
{ // verify copy each item to next index within same collection
    Pet pets[s_petsNumber];
    MemoryOperations::memmove(pets, s_pets, s_petsNumber);
    MemoryOperations::memmove(&pets[1], pets, s_petsNumber - 1);
    GTEST_ASSERT_EQ(false, s_allEqual(pets, s_pets, s_petsNumber));
    GTEST_ASSERT_EQ(true, s_allEqual(&pets[1], s_pets, s_petsNumber - 1));
    GTEST_ASSERT_EQ(true, s_equals(&pets[0], &s_pets[0]));
}

///////////////////////////////////////////////////////////////////////////////
TEST(memoryoperations, memmoveCopyLast)
{ // verify whatever is copied last replaces content
    Pet pets0[s_petsNumber];
    Pet pets1[s_petsNumber];
    MemoryOperations::memmove(pets1, s_pets, s_petsNumber);
    MemoryOperations::memmove(pets1, pets0, s_petsNumber);
    GTEST_ASSERT_EQ(false, s_allEqual(pets1, s_pets, s_petsNumber));
    GTEST_ASSERT_EQ(true, s_allEqual(pets1, pets0, s_petsNumber));
}

///////////////////////////////////////////////////////////////////////////////
TEST(memoryoperations, memmoveReturnValue)
{ // verify address returned from memmove()
    Pet pets[s_petsNumber];
    GTEST_ASSERT_EQ(
        pets, MemoryOperations::memmove(pets, s_pets, s_petsNumber));
}

///////////////////////////////////////////////////////////////////////////////
TEST(memoryoperations, memmoveCopyOverSelfPrevious)
{ // verify copy each item to previous index within same collection
    Pet pets[s_petsNumber];
    MemoryOperations::memmove(&pets[0], &s_pets[0], s_petsNumber);
    MemoryOperations::memmove(&pets[0], &pets[1], s_petsNumber - 1);
    GTEST_ASSERT_EQ(true, s_allEqual(&pets[0], &s_pets[1], s_petsNumber - 1));
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    auto result = RUN_ALL_TESTS();

    std::cout << ((0 != result) ? "\nOne or more tests failed.\n" : "\n");

    exit(0);
    return 0;
}
