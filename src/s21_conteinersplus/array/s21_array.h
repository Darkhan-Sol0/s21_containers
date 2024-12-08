#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include "../../s21_containersplus.h"

namespace s21 {
template <typename T>
class array {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

 private:
  struct Node {
    T value_;
    Node* next_;
    Node* prev_;
    Node(const T& value) : value_(value), next_(nullptr), prev_(nullptr) {};
  };
  Node* head_;
  Node* tail_;
  Node* end_;
  size_t size_;

 public:
  template <typename value_type>
  class ArrayIterator {
   public:
    friend class array;
    Node* IterNode = nullptr;
    ArrayIterator() { IterNode = nullptr; }
    ArrayIterator(Node* node_) : IterNode(node_) {}

    reference operator*() {
      if (this->IterNode == nullptr) throw std::invalid_argument("Is NULL");
      return this->IterNode->value_;
    }

    ArrayIterator operator++(int) {
      ArrayIterator temp = *this;
      ++(*this);
      return temp;
    }

    ArrayIterator operator--(int) {
      ArrayIterator temp = *this;
      --(*this);
      return temp;
    }

    ArrayIterator& operator++() {
      IterNode = IterNode->next_;
      return *this;
    }

    ArrayIterator& operator--() {
      IterNode = IterNode->prev_;
      return *this;
    }

    ArrayIterator operator+(const size_type value) {
      Node* temp = IterNode;
      for (size_type i = 0; i < value; i++) {
        temp = temp->next_;
      }
      ArrayIterator res(temp);
      return res;
    }

    ArrayIterator operator-(const size_type value) {
      Node* temp = IterNode;
      for (size_type i = 0; i < value; i++) {
        temp = temp->prev_;
      }
      ArrayIterator res(temp);
      return res;
    }

    bool operator==(ArrayIterator other) {
      return this->IterNode == other.IterNode;
    }

    bool operator!=(ArrayIterator other) {
      return this->IterNode != other.IterNode;
    }
  };

  template <typename value_type>
  class ArrayConstIterator : public ArrayIterator<value_type> {
   public:
    ArrayConstIterator(ArrayIterator<value_type> other)
        : ArrayIterator<value_type>(other) {}
    const T& operator*() { return ArrayIterator<value_type>::operator*(); }
  };

  using iterator = ArrayIterator<T>;
  using const_iterator = ArrayConstIterator<T>;

  // Array Member functions
  array();
  array(std::initializer_list<value_type> const& items);
  array(const array& a);
  array(array&& a);
  ~array();

  array& operator=(array&& a);

  // Array Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // Array Iterators
  iterator begin();
  iterator end();

  // Array Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Array Modifiers
  void swap(array& other);
  void fill(const_reference value);

  // Helper Array
  void rend();

  void push(const_reference value);
  void clear();
};

}  // namespace s21

#include "s21_array.tpp"

#endif