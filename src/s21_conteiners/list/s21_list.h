#ifndef S21_LIST_H
#define S21_LIST_H

#include "../../s21_containers.h"

namespace s21 {
template <typename T>
class list {
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

 public:
  template <typename value_type>
  class ListIterator {
   public:
    friend class list;
    Node* IterNode = nullptr;
    ListIterator() { IterNode = nullptr; }
    ListIterator(Node* node_) : IterNode(node_) {}

    reference operator*() {
      if (this->IterNode == nullptr) throw std::invalid_argument("Is NULL");
      return this->IterNode->value_;
    }

    ListIterator operator++(int) {
      ListIterator temp = *this;
      ++(*this);
      return temp;
    }

    ListIterator operator--(int) {
      ListIterator temp = *this;
      --(*this);
      return temp;
    }

    ListIterator& operator++() {
      IterNode = IterNode->next_;
      return *this;
    }

    ListIterator& operator--() {
      IterNode = IterNode->prev_;
      return *this;
    }

    ListIterator operator+(const size_type value) {
      Node* temp = IterNode;
      for (size_type i = 0; i < value; i++) {
        temp = temp->next_;
      }
      ListIterator res(temp);
      return res;
    }

    ListIterator operator-(const size_type value) {
      Node* temp = IterNode;
      for (size_type i = 0; i < value; i++) {
        temp = temp->prev_;
      }
      ListIterator res(temp);
      return res;
    }

    bool operator==(ListIterator other) {
      return this->IterNode == other.IterNode;
    }

    bool operator!=(ListIterator other) {
      return this->IterNode != other.IterNode;
    }
  };

  template <typename value_type>
  class ListConstIterator : public ListIterator<value_type> {
   public:
    ListConstIterator(ListIterator<value_type> other)
        : ListIterator<value_type>(other) {}
    const T& operator*() { return ListIterator<value_type>::operator*(); }
  };

  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  // List Functions
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);
  ~list();

  list& operator=(list&& l);

  // List Element access
  const_reference front();
  const_reference back();

  iterator begin();
  iterator end();

  // List Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // List Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();
  void sort();

  // Helper List
  // void print();
  void rend();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);
};
}  // namespace s21

#include "s21_list.tpp"

#endif