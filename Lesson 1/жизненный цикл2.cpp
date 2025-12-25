#include <iostream>
#include <stdexcept>
#include <algorithm>

class smart_array {
private:
    int* data;
    size_t capacity;
    size_t size;

public:
    // Конструктор
    explicit smart_array(size_t initial_capacity)
        : capacity(initial_capacity), size(0) {
        if (initial_capacity == 0) throw std::invalid_argument("Capacity > 0");
        data = new int[capacity];
    }

    // Деструктор
    ~smart_array() {
        delete[] data;
    }

    // 1. Конструктор копирования (Deep Copy)
    smart_array(const smart_array& other)
        : capacity(other.capacity), size(other.size) {
        data = new int[capacity];
        std::copy(other.data, other.data + size, data);
    }

    // 2. Оператор присваивания (Deep Copy)
    smart_array& operator=(const smart_array& other) {
        // Проверка на самоприсваивание (arr = arr)
        if (this == &other) {
            return *this;
        }

        // Удаляем старые данные
        delete[] data;

        // Копируем параметры
        capacity = other.capacity;
        size = other.size;

        // Выделяем новую память и копируем содержимое
        data = new int[capacity];
        std::copy(other.data, other.data + size, data);

        return *this;
    }

    void add_element(int value) {
        if (size >= capacity) {
            size_t new_capacity = capacity * 2;
            int* new_data = new int[new_capacity];
            std::copy(data, data + size, new_data);
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        data[size++] = value;
    }

    int get_element(size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of bounds");
        return data[index];
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        // Теперь это работает корректно благодаря оператору присваивания
        arr = new_array;

        std::cout << "Элемент в arr после присваивания: " << arr.get_element(0) << std::endl; // Выведет 44
    }
    catch (const std::exception& ex) {
        std::cout << "Ошибка: " << ex.what() << std::endl;
    }

    return 0;
}
