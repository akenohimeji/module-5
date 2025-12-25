#include <iostream>
#include <stdexcept>
#include <algorithm> 

class smart_array {
private:
    int* data;          
    size_t capacity;    
    size_t size;        

public:
    explicit smart_array(size_t initial_capacity)
        : capacity(initial_capacity), size(0) {
        if (initial_capacity == 0) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }
        data = new int[capacity];
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
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    ~smart_array() {
        delete[] data;
    }

    smart_array(const smart_array&) = delete;
    smart_array& operator=(const smart_array&) = delete;
};

int main() {
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);

        arr.add_element(42);

        std::cout << "Element at index 1: " << arr.get_element(1) << std::endl;
        std::cout << "Element at index 5: " << arr.get_element(5) << std::endl;

    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
