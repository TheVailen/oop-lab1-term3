#include <array_ops.h>
#include <iostream>

void clear_input() {
    std::cin.clear();
    while (std::cin.get() != '\n') {
    }
}

int main() {
    int* arr = nullptr;
    std::size_t size = 0;

    while (true) {
        std::cout << "\n--- Меню семейства А (Вариант 2) ---\n";
        std::cout << "1. Создать массив\n";
        std::cout << "2. Напечатать\n";
        std::cout << "3. Вставить элемент\n";
        std::cout << "4. Удалить элемент\n";
        std::cout << "5. Изменить размер\n";
        std::cout << "6. Бинарный поиск (Печать результата)\n";
        std::cout << "7. Алгоритм варианта (Сортировка выбором + Разворот)\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите пункт: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Ошибка ввода! Введите число.\n";
            clear_input();
            continue;
        }

        if (choice == 0) {
            array_delete(arr);
            std::cout << "Память освобождена. Выход из программы.\n";
            break;
        }

        if (choice == 1) {
            std::size_t new_size;
            std::cout << "Введите размер массива: ";
            if (!(std::cin >> new_size)) {
                std::cout << "Ошибка ввода размера!\n";
                clear_input();
                continue;
            }

            if (arr != nullptr) {
                array_delete(arr);
            }

            size = new_size;
            arr = array_create(size);

            if (size > 0) {
                std::cout << "Введите элементы массива (" << size << " шт.): ";
                for (std::size_t i = 0; i < size; ++i) {
                    while (!(std::cin >> arr[i])) {
                        std::cout << "Ошибка! Введите целое число для элемента [" << i << "]: ";
                        clear_input();
                    }
                }
            }
            std::cout << "Массив создан (длина " << size << "): ";
            array_print(arr, size);

        } else if (choice == 2) {
            std::cout << "Текущий массив (длина " << size << "): ";
            array_print(arr, size);

        } else if (choice == 3) {
            std::size_t pos;
            int value;
            std::cout << "Введите индекс для вставки (от 0 до " << size << "): ";
            if (!(std::cin >> pos) || pos > size) {
                std::cout << "Некорректный индекс!\n";
                clear_input();
                continue;
            }
            std::cout << "Введите значение: ";
            if (!(std::cin >> value)) {
                std::cout << "Ошибка ввода значения!\n";
                clear_input();
                continue;
            }

            arr = array_insert(arr, size, pos, value);
            std::cout << "После вставки (длина " << size << "): ";
            array_print(arr, size);

        } else if (choice == 4) {
            if (size == 0) {
                std::cout << "Массив пуст, удалять нечего!\n";
                continue;
            }
            std::size_t pos;
            std::cout << "Введите индекс для удаления (от 0 до " << size - 1 << "): ";
            if (!(std::cin >> pos) || pos >= size) {
                std::cout << "Некорректный индекс!\n";
                clear_input();
                continue;
            }

            arr = array_remove(arr, size, pos);
            std::cout << "После удаления (длина " << size << "): ";
            array_print(arr, size);

        } else if (choice == 5) {
            std::size_t new_size;
            std::cout << "Введите новый размер: ";
            if (!(std::cin >> new_size)) {
                std::cout << "Ошибка ввода размера!\n";
                clear_input();
                continue;
            }

            std::size_t old_size = size;
            arr = array_resize(arr, size, new_size);
            size = new_size;

            for (std::size_t i = old_size; i < size; ++i) {
                arr[i] = 0;
            }

            std::cout << "После изменения размера (длина " << size << "): ";
            array_print(arr, size);

        } else if (choice == 6) {
            if (size == 0) {
                std::cout << "Массив пуст!\n";
                continue;
            }
            int target;
            std::cout << "Введите число для бинарного поиска: ";
            if (!(std::cin >> target)) {
                std::cout << "Ошибка ввода!\n";
                clear_input();
                continue;
            }

            array_selection_sort(arr, size);
            std::cout << "Массив отсортирован для поиска: ";
            array_print(arr, size);

            std::size_t out_index = 0;
            bool found = array_binary_search(arr, size, target, out_index);
            if (found) {
                std::cout << "Элемент " << target << " найден! Его индекс (в отсортированном массиве): " << out_index << "\n";
            } else {
                std::cout << "Элемент " << target << " не найден.\n";
            }

        } else if (choice == 7) {
            if (size == 0) {
                std::cout << "Массив пуст! Сначала создайте массив.\n";
                continue;
            }
            std::cout << "Исходный массив: ";
            array_print(arr, size);

            array_selection_sort(arr, size);
            std::cout << "После сортировки выбором по возрастанию: ";
            array_print(arr, size);

            array_reverse(arr, size);
            std::cout << "После разворота двумя указателями: ";
            array_print(arr, size);

        } else {
            std::cout << "Неизвестный пункт меню!\n";
        }
    }

    return 0;
}
