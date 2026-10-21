#include <array_ops.h>
#include <iostream>

int* array_create(std::size_t size) {
    if (size == 0) {
        return nullptr;
    }
    return new int[size];
}

void array_delete(int*& arr) {
    delete[] arr;
    arr = nullptr;
}

int* array_resize(int* arr, std::size_t size, std::size_t new_size) {
    if (new_size == 0) {
        array_delete(arr);
        return nullptr;
    }

    int* new_arr = array_create(new_size);
    
    std::size_t min_size;
    if (size > new_size) {
        min_size = new_size;
    } else {
        min_size = size;
    }

    for (std::size_t i = 0; i < min_size; ++i) {
        new_arr[i] = arr[i];
    }

    array_delete(arr);

    return new_arr;
}

void array_print(const int* arr, std::size_t size) {
    if (size == 0 || arr == nullptr) {
        std::cout << "(пусто)" << std::endl;
        return;
    }
    for (std::size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int* array_insert(int* arr, std::size_t& size, std::size_t pos, int value) {
    if (pos > size) {
        pos = size;
    }

    int* res_arr = array_resize(arr, size, size + 1);

    for (std::size_t i = size; i > pos; --i) {
        res_arr[i] = res_arr[i - 1];
    }

    res_arr[pos] = value;
    size += 1;

    return res_arr;
}

int* array_remove(int* arr, std::size_t& size, std::size_t pos) {
    if (size == 0 || arr == nullptr || pos >= size) {
        return arr;
    }

    for (std::size_t i = pos; i < size - 1; ++i) {
        arr[i] = arr[i + 1];
    }

    int* res_arr = array_resize(arr, size, size - 1);
    size -= 1;

    return res_arr;
}

bool array_binary_search(const int* arr, std::size_t size, int target, std::size_t& out_index) {
    if (size == 0 || arr == nullptr) {
        return false;
    }

    int left = 0;
    int right = static_cast<int>(size) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            out_index = static_cast<std::size_t>(mid);
            return true;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return false;
}

void array_selection_sort(int* arr, std::size_t size) {
    if (size <= 1 || arr == nullptr) {
        return;
    }

    for (std::size_t i = 0; i < size - 1; ++i) {
        std::size_t min_index = i;
        for (std::size_t j = i + 1; j < size; ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        if (min_index != i) {
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}

void array_reverse(int* arr, std::size_t size) {
    if (size <= 1 || arr == nullptr) {
        return;
    }

    std::size_t left = 0;
    std::size_t right = size - 1;

    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        left++;
        right--;
    }
}
