#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include "../../s21_containers.h"

namespace s21 {
template <typename T>
class vector {
 public:
  // List Member type
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
  size_t capacity_;

 public:
  template <typename value_type>
  class VectorIterator {
   public:
    VectorIterator() { IterNode = nullptr; }
    VectorIterator(Node* node_) : IterNode(node_) {};
    friend class vector;
    Node* IterNode = nullptr;

    reference operator*() {
      if (!this->IterNode) throw std::invalid_argument("Is NULL");
      return this->IterNode->value_;
    }

    VectorIterator operator++(int) {
      VectorIterator temp = *this;
      ++(*this);
      return temp;
    }

    VectorIterator operator--(int) {
      VectorIterator temp = *this;
      --(*this);
      return temp;
    }

    VectorIterator& operator++() {
      IterNode = IterNode->next_;
      return *this;
    }

    VectorIterator& operator--() {
      IterNode = IterNode->prev_;
      return *this;
    }

    VectorIterator operator+(const size_type value) {
      Node* temp = IterNode;
      for (size_type i = 0; i < value; i++) {
        temp = temp->next_;
      }
      VectorIterator res(temp);
      return res;
    }

    VectorIterator operator-(const size_type value) {
      Node* temp = IterNode;
      for (size_type i = 0; i < value; i++) {
        temp = temp->prev_;
      }
      VectorIterator res(temp);
      return res;
    }

    bool operator==(VectorIterator other) {
      return this->IterNode == other.IterNode;
    }

    bool operator!=(VectorIterator other) {
      return this->IterNode != other.IterNode;
    }
  };

  template <typename value_type>
  class VectorConstIterator : public VectorIterator<value_type> {
   public:
    VectorConstIterator(VectorIterator<value_type> other)
        : VectorIterator<T>(other) {}
    const T& operator*() { return VectorIterator<value_type>::operator*(); }
  };

  using iterator = VectorIterator<T>;
  using const_iterator = VectorConstIterator<T>;

  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);
  vector(vector&& v);
  ~vector();

  vector& operator=(vector&& v);

  // Vector Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T* data();

  // Vector Iterators
  iterator begin();
  iterator end();

  // Vector Capacity
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  // Vector Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);

  // Helper vector
  void rend();
  // void print();
  void pop_front();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
};

}  // namespace s21

#include "s21_vector.tpp"

#endif