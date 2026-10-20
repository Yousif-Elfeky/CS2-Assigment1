#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class stack {
 public:
  stack() : m_data(nullptr), m_size(0), m_capacity(0) {}

  stack(const stack& other) : m_data(nullptr), m_size(0), m_capacity(0) {
    if (other.m_size == 0) return;
    m_data = new T[other.m_size];
    m_capacity = other.m_size;

    for (size_t i = 0; i < other.m_size; ++i) {
      m_data[i] = other.m_data[i];
    }

    m_size = other.m_size;
  }

  stack& operator=(const stack& other) {
    if (this == &other) return *this;

    stack copy(other);
    swap(copy);

    return *this;
  }

  ~stack() { delete[] m_data; }

  // l/rvalue
  void push(const T& value) {
    ensureCapacity(m_size + 1);
    m_data[m_size] = value;
    ++m_size;
  }
  void push(T&& value) {
    ensureCapacity(m_size + 1);
    m_data[m_size] = std::move(value);
    ++m_size;
  }

  bool pop() {
    if (empty()) return false;
    --m_size;
    return true;
  }

  // add both const and non const meothds
  T& top() {
    if (empty()) throw std::out_of_range("stack::top on empty stack");
    return m_data[m_size - 1];
  }

  const T& top() const {
    if (empty()) throw std::out_of_range("stack::top on empty stack");
    return m_data[m_size - 1];
  }

  bool empty() const { return m_size == 0; }

  size_t size() const { return m_size; }

  void clear() { m_size = 0; }

  void swap(stack& other) noexcept {
    T* tempData = m_data;
    m_data = other.m_data;
    other.m_data = tempData;

    size_t tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;

    size_t tempCapacity = m_capacity;
    m_capacity = other.m_capacity;
    other.m_capacity = tempCapacity;
  }

 private:
  void ensureCapacity(size_t needed) {
    if (needed <= m_capacity) return;

    size_t newCapacity = m_capacity == 0 ? 4 : m_capacity * 2;

    while (newCapacity < needed) newCapacity *= 2;

    T* newData = new T[newCapacity];

    for (size_t i = 0; i < m_size; ++i) {
      newData[i] = std::move(m_data[i]);
    }

    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
  }

  T* m_data;
  size_t m_size;
  size_t m_capacity;
};
