#ifndef S21_VECTOR_TPP
#define S21_VECTOR_TPP

#include "s21_vector.h"

namespace s21 {
template <typename T>
s21::vector<T>::vector()
    : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0), capacity_(0) {
  this->end_ = new Node(this->size_);
  this->rend();
}

template <typename T>
s21::vector<T>::vector(size_type n) : vector() {
  for (size_type i = 0; i < n; i++) this->push_back(T());
  this->rend();
}

template <typename T>
s21::vector<T>::vector(std::initializer_list<value_type> const& items)
    : vector() {
  for (const auto& item : items) this->push_back(item);
  this->rend();
}

template <typename T>
s21::vector<T>::vector(const vector& v) : vector() {
  Node* node = v.head_;
  while (node != nullptr && node != v.end_) {
    this->push_back(node->value_);
    node = node->next_;
  }
  this->rend();
}

template <typename T>
s21::vector<T>::vector(vector&& v)
    : head_(v.head_),
      tail_(v.tail_),
      end_(v.end_),
      size_(v.size_),
      capacity_(v.capacity_) {
  v.head_ = nullptr;
  v.tail_ = nullptr;
  v.end_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
}

template <typename T>
s21::vector<T>::~vector() {
  Node* temp = this->head_;
  while (temp != nullptr && temp != this->end_) {
    Node* delNode = temp;
    temp = temp->next_;
    delete delNode;
  }
  delete this->end_;
}

template <typename T>
s21::vector<T>& s21::vector<T>::operator=(vector&& v) {
  if (this != &v) this->swap(v);
  return *this;
}

// Vector Element access
template <typename T>
typename s21::vector<T>::reference s21::vector<T>::at(size_type pos) {
  if (pos >= this->size_) throw std::out_of_range("Out of range");
  Node* node = this->head_;
  for (size_type i = 0; i < pos; i++) node = node->next_;
  return node->value_;
}

template <typename T>
typename s21::vector<T>::reference s21::vector<T>::operator[](size_type pos) {
  if (pos > this->size_) throw std::out_of_range("Out of range");
  Node* node = this->head_;
  for (size_type i = 0; i < pos; i++) node = node->next_;
  return node->value_;
}

template <typename T>
typename s21::vector<T>::const_reference s21::vector<T>::front() {
  if (this->empty()) throw std::out_of_range("Empty");
  return this->head_->value_;
}

template <typename T>
typename s21::vector<T>::const_reference s21::vector<T>::back() {
  if (this->empty()) throw std::out_of_range("Empty");
  return this->tail_->value_;
}

template <typename T>
T* s21::vector<T>::data() {
  return &(this->head_->value_);
}

// Vector Iterators
template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::begin() {
  return iterator(this->head_);
}

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::end() {
  return iterator(this->end_);
}

// Vector Capacity
template <typename T>
bool s21::vector<T>::empty() {
  return this->size_ == 0;
}

template <typename T>
typename s21::vector<T>::size_type s21::vector<T>::size() {
  return this->size_;
}

template <typename T>
typename s21::vector<T>::size_type s21::vector<T>::max_size() {
  return std::numeric_limits<T>::max() / sizeof(Node);
}

template <typename T>
void s21::vector<T>::reserve(size_type size) {
  if (size > this->capacity_) this->capacity_ = size;
}

template <typename T>
typename s21::vector<T>::size_type s21::vector<T>::capacity() {
  return this->capacity_;
}

template <typename T>
void s21::vector<T>::shrink_to_fit() {
  if (this->size_ < this->capacity_) this->capacity_ = this->size_;
}

// Vector Modifiers
template <typename T>
void s21::vector<T>::clear() {
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

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::insert(
    iterator pos, const_reference value) {
  Node* addNode = new Node(value);
  if (this->empty()) {
    this->head_ = addNode;
    this->tail_ = addNode;
  } else {
    if (pos == this->begin()) {
      addNode->next_ = this->head_;
      this->head_->prev_ = addNode;
      this->head_ = addNode;
    } else if (pos == this->end() || pos.IterNode == this->tail_) {
      addNode->prev_ = this->tail_;
      this->tail_->next_ = addNode;
      this->tail_ = addNode;
    } else {
      addNode->prev_ = pos.IterNode->prev_;
      addNode->next_ = pos.IterNode;
      pos.IterNode->prev_->next_ = addNode;
      pos.IterNode->prev_ = addNode;
    }
  }
  ++this->size_;
  this->reserve(this->size_);
  this->rend();
  return iterator(addNode);
}

template <typename T>
void s21::vector<T>::erase(iterator pos) {
  if (this->empty()) throw std::out_of_range("Vector empty");
  Node* delNode = pos.IterNode;
  if (delNode == this->end_) delNode = this->tail_;
  s21::vector<T> newVec;
  for (auto i = iterator(this->head_); i != this->end(); ++i) {
    if (i.IterNode == delNode) continue;
    newVec.push_back(i.IterNode->value_);
  }
  this->swap(newVec);
  newVec.clear();
  this->rend();
}

template <typename T>
void s21::vector<T>::push_back(const_reference value) {
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
  this->reserve(this->size_);
  this->rend();
}

template <typename T>
void s21::vector<T>::pop_back() {
  if (this->empty()) throw std::out_of_range("Vector empty");
  Node* delNode = this->tail_;
  if (this->head_ == this->tail_) {
    this->head_ = nullptr;
    this->tail_ = nullptr;
  } else {
    this->tail_ = this->tail_->prev_;
    this->tail_->next_ = nullptr;
  }
  delete delNode;
  --this->size_;
  this->rend();
}

template <typename T>
void s21::vector<T>::swap(vector& other) {
  Node* tempHead = other.head_;
  Node* tempTail = other.tail_;
  Node* tempEnd = other.end_;
  size_type tempSize = other.size_;
  size_type tempCapa = other.capacity_;

  other.head_ = this->head_;
  other.tail_ = this->tail_;
  other.end_ = this->end_;
  other.size_ = this->size_;
  other.capacity_ = this->capacity_;

  this->head_ = tempHead;
  this->tail_ = tempTail;
  this->end_ = tempEnd;
  this->size_ = tempSize;
  this->capacity_ = tempCapa;
}

// Helper vector
template <typename T>
void s21::vector<T>::rend() {
  this->end_->next_ = this->head_;
  this->end_->prev_ = this->tail_;
  this->end_->value_ = this->size_;
  if (this->head_) this->head_->prev_ = this->end_;
  if (this->tail_) this->tail_->next_ = this->end_;
}

// template <typename T>
// template <typename... Args>
// typename s21::vector<T>::iterator s21::vector<T>::insert_many(
//     const_iterator pos, Args&&... args) {
//   iterator tempIt = iterator(pos.IterNode);
//   (void(std::initializer_list<int>{
//       (tempIt = this->insert(tempIt, std::forward<Args>(args)), ++tempIt,
//        0)...}));
//   return tempIt;
// }

template <typename T>
template <typename... Args>
typename s21::vector<T>::iterator s21::vector<T>::insert_many(
    const_iterator pos, Args&&... args) {
  iterator tempIt = iterator(pos.IterNode);
  (this->insert(tempIt, std::forward<Args>(args)), ...);
  return tempIt;
}

template <typename T>
template <typename... Args>
void s21::vector<T>::insert_many_back(Args&&... args) {
  (this->push_back(std::forward<Args>(args)), ...);
}

}  // namespace s21

#endif