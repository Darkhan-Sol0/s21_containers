#ifndef S21_LIST_TPP
#define S21_LIST_TPP

#include "s21_list.h"
namespace s21 {

template <typename T>
s21::list<T>::list() : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
  this->end_ = new Node(this->size_);
  this->rend();
}

template <typename T>
s21::list<T>::list(size_type n) : list() {
  for (size_type i = 0; i < n; i++) this->push_back(T());
  this->rend();
}

template <typename T>
s21::list<T>::list(std::initializer_list<T> const& items) : list() {
  for (const auto& item : items) this->push_back(item);
  this->rend();
}

template <typename T>
s21::list<T>::list(const list& l) : list() {
  Node* node = l.head_;
  while (node != nullptr && node != l.end_) {
    this->push_back(node->value_);
    node = node->next_;
  }
  this->rend();
}

template <typename T>
s21::list<T>::list(list&& l)
    : head_(l.head_), tail_(l.tail_), end_(l.end_), size_(l.size_) {
  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.end_ = nullptr;
  l.size_ = 0;
}

template <typename T>
s21::list<T>::~list() {
  Node* temp = this->head_;
  while (temp != nullptr && temp != this->end_) {
    Node* delNode = temp;
    temp = temp->next_;
    delete delNode;
  }
  delete this->end_;
}

template <typename T>
s21::list<T>& s21::list<T>::operator=(list&& l) {
  if (this != &l) this->swap(l);
  return *this;
}

template <typename T>
typename s21::list<T>::const_reference s21::list<T>::front() {
  if (this->empty()) throw std::out_of_range("Empty");
  return this->head_->value_;
}

template <typename T>
typename s21::list<T>::const_reference s21::list<T>::back() {
  if (this->empty()) throw std::out_of_range("Empty");
  return this->tail_->value_;
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::begin() {
  return iterator(this->head_);
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::end() {
  return iterator(this->end_);
}

template <typename T>
bool s21::list<T>::empty() {
  return this->size_ == 0;
}

template <typename T>
typename s21::list<T>::size_type s21::list<T>::size() {
  return this->size_;
}

template <typename T>
typename s21::list<T>::size_type s21::list<T>::max_size() {
  return std::numeric_limits<T>::max() / sizeof(Node);
}

template <typename T>
void s21::list<T>::clear() {
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
typename s21::list<T>::iterator s21::list<T>::insert(iterator pos,
                                                     const_reference value) {
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
  this->rend();
  return iterator(addNode);
}

template <typename T>
void s21::list<T>::erase(iterator pos) {
  if (this->empty()) throw std::out_of_range("Empty");
  if (pos == this->begin() || pos.IterNode == this->head_) {
    this->pop_front();
  } else if (pos == this->end() || pos.IterNode == this->tail_) {
    this->pop_back();
  } else {
    Node* delNode = pos.IterNode;
    delNode->prev_->next_ = delNode->next_;
    delNode->next_->prev_ = delNode->prev_;
    --this->size_;
    delete delNode;
  }
  this->rend();
}

template <typename T>
void s21::list<T>::push_back(const_reference value) {
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
void s21::list<T>::pop_back() {
  if (this->empty()) throw std::out_of_range("List empty");
  Node* delNode = this->tail_;
  if (this->tail_ == this->head_) {
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
void s21::list<T>::push_front(const_reference value) {
  Node* newNode = new Node(value);
  if (this->empty()) {
    this->head_ = newNode;
    this->tail_ = newNode;
  } else {
    this->head_->prev_ = newNode;
    newNode->next_ = this->head_;
    this->head_ = newNode;
  }
  ++this->size_;
  this->rend();
}

template <typename T>
void s21::list<T>::pop_front() {
  if (this->empty()) throw std::out_of_range("List empty");
  Node* delNode = this->head_;
  if (this->head_ == this->tail_) {
    this->head_ = nullptr;
    this->tail_ = nullptr;
  } else {
    this->head_ = this->head_->next_;
    this->head_->prev_ = nullptr;
  }
  delete delNode;
  --this->size_;
  this->rend();
}

template <typename T>
void s21::list<T>::swap(list& other) {
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
void s21::list<T>::merge(list& other) {
  if (this->empty())
    this->swap(other);
  else if (other.empty())
    return;
  else {
    Node* temp = other.head_;
    while (temp != nullptr && temp != other.end_) {
      this->push_back(temp->value_);
      temp = temp->next_;
    }
    this->sort();
    this->rend();
    other.clear();
  }
}

template <typename T>
void s21::list<T>::splice(const_iterator pos, list& other) {
  if (other.empty()) return;

  if (pos == this->begin()) {
    other.tail_->next_ = this->head_;
    if (this->head_)
      this->head_->prev_ = other.tail_;
    else
      this->tail_ = other.tail_;
    this->head_ = other.head_;
  } else if (pos == this->end()) {
    other.head_->prev_ = this->tail_;
    if (this->tail_)
      this->tail_->next_ = other.head_;
    else
      this->head_ = other.head_;
    this->tail_ = other.tail_;
  } else {
    other.head_->prev_ = pos.IterNode->prev_;
    other.tail_->next_ = pos.IterNode;
    pos.IterNode->prev_->next_ = other.head_;
    pos.IterNode->prev_ = other.tail_;
  }
  this->size_ += other.size_;
  this->rend();
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
  other.rend();
}

template <typename T>
void s21::list<T>::reverse() {
  s21::list<T> tempList;
  Node* tempNode = this->head_;
  while (tempNode != nullptr && tempNode != this->end_) {
    tempList.push_front(tempNode->value_);
    tempNode = tempNode->next_;
  }
  this->swap(tempList);
  tempList.clear();
  this->rend();
}

template <typename T>
void s21::list<T>::unique() {
  if (this->empty() || this->head_ == this->tail_) return;
  Node* temp = this->head_;
  while (temp->next_ != nullptr && temp->next_ != this->end_) {
    if (temp->value_ == temp->next_->value_) {
      Node* delNode = temp->next_;
      if (delNode == this->tail_) {
        this->tail_ = temp;
        this->tail_->next_ = nullptr;
      } else {
        temp->next_ = delNode->next_;
        delNode->next_->prev_ = temp;
      }
      delete delNode;
      --this->size_;
    } else {
      temp = temp->next_;
    }
  }
  this->rend();
}

template <typename T>
void s21::list<T>::sort() {
  if (this->empty()) throw std::out_of_range("List empty");
  bool sorted;
  do {
    sorted = true;
    Node* node = this->head_;
    while (node->next_ != nullptr && node->next_ != this->end_) {
      if (node->value_ > node->next_->value_) {
        value_type temp = node->value_;
        node->value_ = node->next_->value_;
        node->next_->value_ = temp;
        sorted = false;
      }
      node = node->next_;
    }
  } while (!sorted);
  this->rend();
}

// Helper List
// template <typename T>
// void s21::list<T>::print() {
//   Node* node = this->head_;
//   while (node != this->end_ && node != nullptr) {
//     std::cout << node->value_ << " ";
//     node = node->next_;
//   }
//   std::cout << std::endl;
// }

template <typename T>
void s21::list<T>::rend() {
  this->end_->next_ = this->head_;
  this->end_->prev_ = this->tail_;
  this->end_->value_ = this->size_;
  if (this->head_ != nullptr) this->head_->prev_ = this->end_;
  if (this->tail_ != nullptr) this->tail_->next_ = this->end_;
}

template <typename T>
template <typename... Args>
typename s21::list<T>::iterator s21::list<T>::insert_many(const_iterator pos,
                                                          Args&&... args) {
  iterator tempIt = iterator(pos.IterNode);
  (this->insert(tempIt, std::forward<Args>(args)), ...);
  return tempIt;
}

template <typename T>
template <typename... Args>
void s21::list<T>::insert_many_back(Args&&... args) {
  (this->push_back(std::forward<Args>(args)), ...);
}

template <typename T>
template <typename... Args>
void s21::list<T>::insert_many_front(Args&&... args) {
  (this->push_front(std::forward<Args>(args)), ...);
}
}  // namespace s21

#endif