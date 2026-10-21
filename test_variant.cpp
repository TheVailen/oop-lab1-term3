#include <gtest/gtest.h>
#include <array_ops.h>

TEST(ArrayOpsTest, CreateAndDelete) {
    std::size_t size = 5;
    int* arr = array_create(size);
    EXPECT_NE(arr, nullptr);

    array_delete(arr);
    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayOpsTest, ResizeArray) {
    std::size_t size = 3;
    int* arr = array_create(size);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    arr = array_resize(arr, size, 5);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);

    arr = array_resize(arr, 5, 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);

    array_delete(arr);
}

TEST(ArrayOpsTest, InsertMiddle) {
    std::size_t size = 3;
    int* arr = array_create(size);
    arr[0] = 1;
    arr[1] = 3;
    arr[2] = 4;

    arr = array_insert(arr, size, 1, 2);
    EXPECT_EQ(size, 4);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);

    array_delete(arr);
}

TEST(ArrayOpsTest, InsertBeginAndEnd) {
    std::size_t size = 2;
    int* arr = array_create(size);
    arr[0] = 20;
    arr[1] = 30;

    arr = array_insert(arr, size, 0, 10);
    arr = array_insert(arr, size, size, 40); 

    EXPECT_EQ(size, 4);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
    EXPECT_EQ(arr[3], 40);

    array_delete(arr);
}

TEST(ArrayOpsTest, RemoveElement) {
    std::size_t size = 4;
    int* arr = array_create(size);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;

    arr = array_remove(arr, size, 1);
    EXPECT_EQ(size, 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);
    EXPECT_EQ(arr[2], 40);

    array_delete(arr);
}

TEST(ArrayOpsTest, BinarySearchFound) {
    std::size_t size = 5;
    int* arr = array_create(size);
    arr[0] = 1;
    arr[1] = 3;
    arr[2] = 5;
    arr[3] = 7;
    arr[4] = 9;

    std::size_t index = 0;
    bool found = array_binary_search(arr, size, 7, index);
    EXPECT_TRUE(found);
    EXPECT_EQ(index, 3);

    array_delete(arr);
}

TEST(ArrayOpsTest, BinarySearchNotFoundAndEmpty) {
    std::size_t size = 4;
    int* arr = array_create(size);
    arr[0] = 2;
    arr[1] = 4;
    arr[2] = 6;
    arr[3] = 8;

    std::size_t index = 0;
    EXPECT_FALSE(array_binary_search(arr, size, 5, index));
    EXPECT_FALSE(array_binary_search(nullptr, 0, 5, index));

    array_delete(arr);
}

TEST(ArrayOpsTest, SelectionSort) {
    std::size_t size = 5;
    int* arr = array_create(size);
    arr[0] = 5;
    arr[1] = -2;
    arr[2] = 9;
    arr[3] = 0;
    arr[4] = 3;

    array_selection_sort(arr, size);

    EXPECT_EQ(arr[0], -2);
    EXPECT_EQ(arr[1], 0);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 5);
    EXPECT_EQ(arr[4], 9);

    array_delete(arr);
}

TEST(ArrayOpsTest, ReverseArray) {
    std::size_t size = 4;
    int* arr = array_create(size);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;

    array_reverse(arr, size);

    EXPECT_EQ(arr[0], 4);
    EXPECT_EQ(arr[1], 3);
    EXPECT_EQ(arr[2], 2);
    EXPECT_EQ(arr[3], 1);

    array_delete(arr);
}

TEST(ArrayOpsTest, Variant2ControlExample) {
    std::size_t size = 5;
    int* arr = array_create(size);
    arr[0] = 3;
    arr[1] = 1;
    arr[2] = 4;
    arr[3] = 1;
    arr[4] = 5;

    array_selection_sort(arr, size);
    int expected_sorted[5] = {1, 1, 3, 4, 5};
    for (std::size_t i = 0; i < size; ++i) {
        EXPECT_EQ(arr[i], expected_sorted[i]);
    }

    array_reverse(arr, size);
    int expected_reversed[5] = {5, 4, 3, 1, 1};
    for (std::size_t i = 0; i < size; ++i) {
        EXPECT_EQ(arr[i], expected_reversed[i]);
    }

    array_delete(arr);
}

TEST(ArrayOpsTest, EmptyAndSingleElementResilience) {
    int* empty_arr = array_create(0);
    EXPECT_EQ(empty_arr, nullptr);
    array_selection_sort(empty_arr, 0);
    array_reverse(empty_arr, 0);

    std::size_t size = 1;
    int* single_arr = array_create(size);
    single_arr[0] = 42;
    array_selection_sort(single_arr, size);
    array_reverse(single_arr, size);
    EXPECT_EQ(single_arr[0], 42);

    std::size_t idx = 0;
    EXPECT_TRUE(array_binary_search(single_arr, size, 42, idx));
    EXPECT_EQ(idx, 0);

    array_delete(single_arr);
}
