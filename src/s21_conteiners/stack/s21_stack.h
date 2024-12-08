#ifndef S21_STACK_H
#define S21_STACK_H

#include "../../s21_containers.h"

namespace s21 {
template <typename T>

class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  struct Node {
    T value_;
    Node *next_;
    Node *prev_;
    Node(const T &value) : value_(value), next_(nullptr), prev_(nullptr) {};
  };
  Node *head_;
  Node *tail_;
  size_t size_;

 public:
  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();

  stack &operator=(stack &&s);

  const_reference top();
  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);
};
}  // namespace s21

#include "s21_stack.tpp"

#endif