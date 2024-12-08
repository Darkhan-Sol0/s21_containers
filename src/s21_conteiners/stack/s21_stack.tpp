#ifndef S21_STACK_TPP
#define S21_STACK_TPP

#include "s21_stack.h"

namespace s21 {
template <typename T>
s21::stack<T>::stack() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
s21::stack<T>::stack(std::initializer_list<value_type> const& items) : stack() {
  for (const auto& item : items) this->push(item);
}

template <typename T>
s21::stack<T>::stack(const stack& s) : stack() {
  Node* node = s.head_;
  while (node != nullptr) {
    this->push(node->value_);
    node = node->next_;
  }
}

template <typename T>
s21::stack<T>::stack(stack&& s)
    : head_(s.head_), tail_(s.tail_), size_(s.size_) {
  s.head_ = nullptr;
  s.tail_ = nullptr;
  s.size_ = 0;
}

template <typename T>
s21::stack<T>::~stack() {
  while (!this->empty()) this->pop();
}

template <typename T>
s21::stack<T>& s21::stack<T>::operator=(stack&& s) {
  if (this != &s) this->swap(s);
  return *this;
}

template <typename T>
typename s21::stack<T>::const_reference s21::stack<T>::top() {
  if (this->empty()) throw std::out_of_range("This empty");
  return this->tail_->value_;
}

template <typename T>
bool s21::stack<T>::empty() {
  return this->size_ == 0;
}

template <typename T>
typename s21::stack<T>::size_type s21::stack<T>::size() {
  return this->size_;
}

template <typename T>
void s21::stack<T>::push(const_reference value) {
  Node* node = new Node(value);
  if (this->empty()) {
    this->head_ = node;
    this->tail_ = node;
  } else {
    this->head_->prev_ = node;
    node->next_ = this->head_;
    this->head_ = node;
  }
  this->size_++;
}

template <typename T>
void s21::stack<T>::pop() {
  if (this->empty()) throw std::out_of_range("This empty");
  Node* node = this->head_;
  if (this->head_ == this->tail_) {
    this->head_ = nullptr;
    this->tail_ = nullptr;
  } else {
    this->head_ = this->head_->next_;
    this->head_->prev_ = nullptr;
  }
  delete node;
  this->size_--;
}

template <typename T>
void s21::stack<T>::swap(stack& other) {
  Node* temp_head = this->head_;
  Node* temp_tail = this->tail_;
  size_type temp_size = this->size_;

  this->head_ = other.head_;
  this->tail_ = other.tail_;
  this->size_ = other.size_;

  other.head_ = temp_head;
  other.tail_ = temp_tail;
  other.size_ = temp_size;
}

template <typename T>
template <typename... Args>
void s21::stack<T>::insert_many_back(Args&&... args) {
  (this->push(std::forward<Args>(args)), ...);
}
}  // namespace s21

#endif