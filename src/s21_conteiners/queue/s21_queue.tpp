#ifndef S21_QUEUE_TPP
#define S21_QUEUE_TPP

#include "s21_queue.h"

namespace s21 {
template <typename T>
s21::queue<T>::queue() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
s21::queue<T>::queue(std::initializer_list<value_type> const& items) : queue() {
  for (const auto& item : items) this->push(item);
}

template <typename T>
s21::queue<T>::queue(const queue& q) : queue() {
  Node* node = q.head_;
  while (node != nullptr) {
    this->push(node->value_);
    node = node->next_;
  }
}

template <typename T>
s21::queue<T>::queue(queue&& q)
    : head_(q.head_), tail_(q.tail_), size_(q.size_) {
  q.head_ = nullptr;
  q.tail_ = nullptr;
  q.size_ = 0;
}

template <typename T>
s21::queue<T>::~queue() {
  while (!this->empty()) this->pop();
}

template <typename T>
s21::queue<T>& s21::queue<T>::operator=(queue&& q) {
  if (this != &q) this->swap(q);
  return *this;
}

template <typename T>
typename s21::queue<T>::const_reference s21::queue<T>::front() {
  return this->head_->value_;
}

template <typename T>
typename s21::queue<T>::const_reference s21::queue<T>::back() {
  return this->tail_->value_;
}

template <typename T>
bool s21::queue<T>::empty() {
  return this->size_ == 0;
}

template <typename T>
typename s21::queue<T>::size_type s21::queue<T>::size() {
  return this->size_;
}

template <typename T>
void s21::queue<T>::push(const_reference value) {
  Node* node = new Node(value);
  if (this->empty()) {
    this->head_ = node;
    this->tail_ = node;
  } else {
    this->tail_->next_ = node;
    node->prev_ = this->tail_;
    this->tail_ = node;
  }
  this->size_++;
}

template <typename T>
void s21::queue<T>::pop() {
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
void s21::queue<T>::swap(queue& other) {
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

// Helper queue
// template <typename T>
// void s21::queue<T>::print() {
//   Node* node = this->head_;
//   while (node != nullptr) {
//     std::cout << node->value_ << " ";
//     node = node->next_;
//   }
//   std::cout << std::endl;
// }

template <typename T>
template <typename... Args>
void s21::queue<T>::insert_many_back(Args&&... args) {
  (this->push(std::forward<Args>(args)), ...);
}
}  // namespace s21

#endif