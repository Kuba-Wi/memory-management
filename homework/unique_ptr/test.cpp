#include "gtest/gtest.h"
#include "unique_ptr.hpp"
#include <string>
#include <memory>


TEST(UniquePtrTest, StarOperatorShouldReturnObject) {
    cs::unique_ptr<int> ptr(new int{42});
    *ptr = 1;

    ASSERT_TRUE(*ptr == 1);
}

TEST(UniquePtrTest, ArrowOperatorShouldReturnObject) {
    cs::unique_ptr<std::string> ala(new std::string{"Ala"});

    ASSERT_TRUE(ala->size() == 3);
}

TEST(UniquePtrTest, GetFunctionShouldReturnRawPointerAndResetChangePointer) {
    cs::unique_ptr<int> ptr;
    ASSERT_TRUE(ptr.get() == nullptr);

    ptr.reset(new int{42});
    ASSERT_TRUE(ptr.get() != nullptr);
    ASSERT_TRUE(*ptr.get() == 42);
}

TEST(UniquePtrTest, CopyingConstructorShouldSetNullptr) {
    cs::unique_ptr<int> temp(new int{42});
    cs::unique_ptr<int> main_ptr = std::move(temp);

    ASSERT_TRUE(temp.get() == nullptr);
    ASSERT_TRUE(main_ptr.get() != nullptr);
    ASSERT_TRUE(*main_ptr == 42);
}

TEST(UniquePtrTest, CopyAssignOperatorShouldSetNullptr) {
    cs::unique_ptr<int> temp(new int{42});
    cs::unique_ptr<int> main_ptr;
    main_ptr = std::move(temp);

    ASSERT_TRUE(temp.get() == nullptr);
    ASSERT_TRUE(main_ptr.get() != nullptr);
    ASSERT_TRUE(*main_ptr == 42);
}

TEST(UniquePtrTest, CopyAssignOperatorShouldAssignWhenMainPtrIsNotNullptr) {
    cs::unique_ptr<int> temp(new int{42});
    cs::unique_ptr<int> main_ptr(new int{1});
    main_ptr = std::move(temp);

    ASSERT_TRUE(temp.get() == nullptr);
    ASSERT_TRUE(main_ptr.get() != nullptr);
    ASSERT_TRUE(*main_ptr == 42);
}

TEST(UniquePtrTest, ReleaseFunctionShouldSetNullptrAndReturnPointer) {
    cs::unique_ptr<int> temp(new int{42});
    int* ptr = temp.release();

    ASSERT_TRUE(*ptr == 42);
    delete ptr;
}

TEST(UniquePtrTest, MakeUniqueFunctionShouldMakeAPointer) {
    auto ptr = cs::make_unique<int>(2);
    ASSERT_EQ(*ptr, 2);
    
    auto ptr_to_pair = cs::make_unique<std::pair<std::string, int>>("word", 42);
    ASSERT_EQ(*ptr_to_pair, std::make_pair(std::string("word"), 42));
}

TEST(UniquePtrTest, MakeUniqueFunctionShouldWorkWithMove) {
    constexpr int value = 2;
    auto ptr_to_move = std::make_unique<int>(value);
    auto ptr = cs::make_unique<std::unique_ptr<int>>(std::move(ptr_to_move));
    ASSERT_EQ(**ptr, value);
    ASSERT_EQ(ptr_to_move, nullptr);
}
