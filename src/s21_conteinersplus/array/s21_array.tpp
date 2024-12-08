#ifndef S21_ARRAY_TPP
#define S21_ARRAY_TPP

#include "s21_array.h"
namespace s21 {
template <typename T>
s21::array<T>::array()
    : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
  this->end_ = new Node(this->size_);
  this->rend();
}

template <typename T>
s21::array<T>::array(std::initializer_list<value_type> const& items) : array() {
  for (const auto& item : items) this->push(item);
  this->rend();
}

template <typename T>
s21::array<T>::array(const array& a) : array() {
  Node* node = a.head_;
  while (node != nullptr && node != a.end_) {
    this->push(node->value_);
    node = node->next_;
  }
  this->rend();
}

template <typename T>
s21::array<T>::array(array&& a)
    : head_(a.head_), tail_(a.tail_), end_(a.end_), size_(a.size_) {
  a.head_ = nullptr;
  a.tail_ = nullptr;
  a.end_ = nullptr;
  a.size_ = 0;
}

template <typename T>
s21::array<T>::~array() {
  Node* temp = this->head_;
  while (temp != nullptr && temp != this->end_) {
    Node* delNode = temp;
    temp = temp->next_;
    delete delNode;
  }
  delete this->end_;
}

template <typename T>
s21::array<T>& s21::array<T>::operator=(array&& a) {
  if (this != &a) {
    this->clear();
    this->swap(a);
  }
  return *this;
}

// Array Element access
template <typename T>
typename s21::array<T>::reference s21::array<T>::at(size_type pos) {
  if (pos >= this->size_) throw std::out_of_range("Out of range");
  Node* node = this->head_;
  for (size_type i = 0; i < pos; i++) node = node->next_;
  return node->value_;
}

template <typename T>
typename s21::array<T>::reference s21::array<T>::operator[](size_type pos) {
  if (pos >= this->size_) throw std::out_of_range("Out of range");
  Node* node = this->head_;
  for (size_type i = 0; i < pos; i++) node = node->next_;
  return node->value_;
}

template <typename T>
typename s21::array<T>::const_reference s21::array<T>::front() {
  return this->head_->value_;
}

template <typename T>
typename s21::array<T>::const_reference s21::array<T>::back() {
  return this->tail_->value_;
}

template <typename T>
typename s21::array<T>::iterator s21::array<T>::data() {
  return iterator(this->head_);
}

// Array Iterators
template <typename T>
typename s21::array<T>::iterator s21::array<T>::begin() {
  return iterator(this->head_);
}

template <typename T>
typename s21::array<T>::iterator s21::array<T>::end() {
  return iterator(this->end_);
}

// Array Capacity
template <typename T>
bool s21::array<T>::empty() {
  return this->size_ == 0;
}

template <typename T>
typename s21::array<T>::size_type s21::array<T>::size() {
  return this->size_;
}

template <typename T>
typename s21::array<T>::size_type s21::array<T>::max_size() {
  return this->size_;
}

// Array Modifiers
template <typename T>
void s21::array<T>::swap(array& other) {
  Node* tempHead = other.head_;
  Node* tempTail = other.tail_;
  Node* tempEnd = other.end_;
  size_type tempSize = other.size_;

  other.head_ = this->head_;
  other.tail_ = this->tail_;
  other.end_ = this->end_;
  other.size_ = this->size_;

  this->head_ = tempHead;
  this->tail_ = tempTail;
  this->end_ = tempEnd;
  this->size_ = tempSize;
}

template <typename T>
void s21::array<T>::fill(const_reference value) {
  Node* node = this->head_;
  for (size_type i = 0; i < this->size_; i++) {
    node->value_ = value;
    node = node->next_;
  }
}

// Helpers Array

template <typename T>
void s21::array<T>::rend() {
  this->end_->next_ = this->head_;
  this->end_->prev_ = this->tail_;
  this->end_->value_ = this->size_;
  if (this->head_ != nullptr) this->head_->prev_ = this->end_;
  if (this->tail_ != nullptr) this->tail_->next_ = this->end_;
}

template <typename T>
void s21::array<T>::push(const_reference value) {
  Node* newNode = new Node(value);
  if (this->empty()) {
    this->head_ = newNode;
    this->tail_ = newNode;
  } else {
    this->tail_->next_ = newNode;
    newNode->prev_ = this->tail_;
    this->tail_ = newNode;
  }
  ++this->size_;
  this->rend();
}

template <typename T>
void s21::array<T>::clear() {
  Node* node = this->head_;
  while (node != nullptr && node != this->end_) {
    Node* delNode = node;
    node = node->next_;
    delete delNode;
  }
  this->head_ = nullptr;
  this->tail_ = nullptr;
  this->size_ = 0;
  this->rend();
}

}  // namespace s21

#endif