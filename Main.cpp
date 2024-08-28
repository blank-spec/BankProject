#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
using namespace std;

template <typename T>
class Vector {
 private:
  unsigned int capacity;
  int size;
  T* data;

  void clearMemory() {
    destroy(data, data + size);
    delete[] data;
  }

  void resize(int newCapacity) noexcept {
    if (newCapacity <= capacity) {
      return;
    }

    T* newData = new T[newCapacity];
    uninitialized_move(data, data + size, newData);
    destroy(data, data + size);

    delete[] data;
    data = newData;
    capacity = newCapacity;
  }

 public:
  Vector() : size(0), capacity(1) { data = new T[capacity]; }

  ~Vector() { clearMemory(); }

  Vector(Vector&& other) noexcept
      : size(other.size), capacity(other.capacity), data(other.data) {
    other.size = 0;
    other.capacity = 0;
    other.data = nullptr;
  }

  Vector& operator=(Vector&& other) noexcept {
    if (this != &other) {
      clearMemory();

      size = other.size;
      capacity = other.capacity;
      data = other.data;

      other.size = 0;
      other.capacity = 0;
      other.data = nullptr;
    }
    return *this;
  }

  Vector(const Vector&) = delete;
  Vector& operator=(const Vector&) = delete;

  void reserve(int newCapacity) {
    if (newCapacity > capacity) {
      resize(newCapacity);
    }
  }

  void push_back(const T& value) {
    if (size == capacity) {
      resize(capacity * 2);
    }
    data[size++] = std::move(value);
  }

  void pop_back() {
    if (size > 0) {
      --size;
      data[size].~T();
    } else {
      throw out_of_range("Vector is empty");
    }
  }

  T& operator[](int index) {
    if (index < 0 || index >= size) {
      throw out_of_range("Index out of range");
    }
    return data[index];
  }

  void print() const {
    for (size_t i = 0; i < size; ++i) {
      cout << data[i] << ' ';
    }
    cout << endl;
  }

  int getSize() const { return size; }
};

int main() {
  Vector<int> vec;

  return EXIT_SUCCESS;
}