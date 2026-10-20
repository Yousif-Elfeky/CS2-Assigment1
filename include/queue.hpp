#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class queue {
 public:
  queue() : m_data(nullptr), m_capacity(0), m_size(0), m_head(0) {}

  queue(const queue& other)
      : m_data(nullptr), m_capacity(0), m_size(0), m_head(0) {
    if (other.m_size == 0) return;

    m_data = new T[other.m_size];
    m_capacity = other.m_size;

    for (size_t i = 0; i < other.m_size; ++i) {
      m_data[i] = other.m_data[(other.m_head + i) % other.m_capacity];
    }

    m_size = other.m_size;
  }

  queue& operator=(const queue& other) {
    if (this == &other) return *this;

    queue copy(other);
    swap(copy);

    return *this;
  }

  ~queue() { delete[] m_data; }

  // l/rvalue
  void push(const T& value) {
    ensureCapacity(m_size + 1);
    m_data[(m_head + m_size) % m_capacity] = value;
    ++m_size;
  }

  void push(T&& value) {
    ensureCapacity(m_size + 1);
    m_data[(m_head + m_size) % m_capacity] = std::move(value);
    ++m_size;
  }

  bool pop() {
    if (empty()) return false;
    m_head = (m_head + 1) % m_capacity;
    --m_size;
    if (m_size == 0) m_head = 0;
    return true;
  }

  T& front() {
    if (empty()) throw std::out_of_range("queue::front on empty queue");
    return m_data[m_head];
  }

  const T& front() const {
    if (empty()) throw std::out_of_range("queue::front on empty queue");
    return m_data[m_head];
  }

  T& back() {
    if (empty()) throw std::out_of_range("queue::back on empty queue");
    return m_data[(m_head + m_size - 1) % m_capacity];
  }

  const T& back() const {
    if (empty()) throw std::out_of_range("queue::back on empty queue");
    return m_data[(m_head + m_size - 1) % m_capacity];
  }

  bool empty() const { return m_size == 0; }

  size_t size() const { return m_size; }

  void clear() {
    m_size = 0;
    m_head = 0;
  }

  void swap(queue& other) noexcept {
    T* tempData = m_data;
    m_data = other.m_data;
    other.m_data = tempData;

    size_t tempCapacity = m_capacity;
    m_capacity = other.m_capacity;
    other.m_capacity = tempCapacity;

    size_t tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;

    size_t tempHead = m_head;
    m_head = other.m_head;
    other.m_head = tempHead;
  }

 private:
  void ensureCapacity(size_t needed) {
    if (needed <= m_capacity) return;

    size_t newCapacity = m_capacity == 0 ? 4 : m_capacity * 2;
    while (newCapacity < needed) newCapacity *= 2;

    T* newData = new T[newCapacity];
    for (size_t i = 0; i < m_size; ++i) {
      newData[i] = std::move(m_data[(m_head + i) % m_capacity]);
    }

    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
    m_head = 0;
  }

  T* m_data;
  size_t m_capacity;
  size_t m_size;
  size_t m_head;
};
