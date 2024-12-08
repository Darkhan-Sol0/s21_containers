#ifndef S21_MULTISET_TPP
#define S21_MULTISET_TPP

#include "s21_multiset.h"

namespace s21 {
template <typename Key>
s21::multiset<Key>::multiset()
    : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
  this->end_ = new Node(this->size_);
  this->rend();
}

template <typename Key>
s21::multiset<Key>::multiset(std::initializer_list<value_type> const& items)
    : multiset() {
  for (const auto& item : items) this->insert(item);
  this->rend();
}

template <typename Key>
s21::multiset<Key>::multiset(const multiset& ms) : multiset() {
  Node* node = ms.head_;
  while (node != nullptr && node != ms.end_) {
    this->insert(node->value_);
    node = node->next_;
  }
  this->rend();
}

template <typename Key>
s21::multiset<Key>::multiset(multiset&& ms)
    : head_(ms.head_), tail_(ms.tail_), end_(ms.end_), size_(ms.size_) {
  ms.head_ = nullptr;
  ms.tail_ = nullptr;
  ms.end_ = nullptr;
  ms.size_ = 0;
}

template <typename Key>
s21::multiset<Key>::~multiset() {
  Node* temp = this->head_;
  while (temp != nullptr && temp != this->end_) {
    Node* delNode = temp;
    temp = temp->next_;
    delete delNode;
  }
  delete this->end_;
}

template <typename Key>
s21::multiset<Key>& s21::multiset<Key>::operator=(multiset&& ms) {
  if (this != &ms) {
    this->clear();
    this->swap(ms);
  }
  return *this;
}

// Multiset Iterators
template <typename Key>
typename s21::multiset<Key>::iterator s21::multiset<Key>::begin() {
  return iterator(this->head_);
}

template <typename Key>
typename s21::multiset<Key>::iterator s21::multiset<Key>::end() {
  return iterator(this->end_);
}

// Multiset Capacity
template <typename Key>
bool s21::multiset<Key>::empty() {
  return this->size_ == 0;
}

template <typename Key>
typename s21::multiset<Key>::size_type s21::multiset<Key>::size() {
  return this->size_;
}

template <typename Key>
typename s21::multiset<Key>::size_type s21::multiset<Key>::max_size() {
  return std::numeric_limits<Key>::max() / sizeof(value_type);
}

// Multiset Modifiers
template <typename Key>
void s21::multiset<Key>::clear() {
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

template <typename Key>
typename s21::multiset<Key>::iterator s21::multiset<Key>::insert(
    const value_type& value) {
  Node* newNode = new Node(value);

  if (this->empty()) {
    this->head_ = newNode;
    this->tail_ = newNode;
  } else {
    Node* prevNode = getPrevNode(value);

    if (prevNode->value_ > value) {
      prevNode->prev_ = newNode;
      newNode->next_ = prevNode;
      if (prevNode == this->head_) this->head_ = newNode;
    } else {
      if (prevNode->next_) {
        prevNode->next_->prev_ = newNode;
        newNode->next_ = prevNode->next_;
      }
      prevNode->next_ = newNode;
      newNode->prev_ = prevNode;
      if (prevNode == this->tail_) this->tail_ = newNode;
    }
  }
  ++this->size_;
  this->rend();

  return iterator(newNode);
}

template <typename Key>
void s21::multiset<Key>::erase(iterator pos) {
  if (this->empty()) throw std::out_of_range("Multiset empty");
  if (pos.IterNode == nullptr) throw std::invalid_argument("None data");
  Node* delNode = pos.IterNode;
  if (delNode == this->head_ && delNode == this->tail_) {
    this->head_ = nullptr;
    this->tail_ = nullptr;
  } else if (delNode == this->head_) {
    this->head_ = this->head_->next_;
    this->head_->prev_ = nullptr;
  } else if (delNode == this->tail_) {
    this->tail_ = this->tail_->prev_;
    this->tail_->next_ = nullptr;
  } else {
    delNode->prev_->next_ = delNode->next_;
    delNode->next_->prev_ = delNode->prev_;
  }
  delete delNode;
  --this->size_;
  this->rend();
}

template <typename Key>
void s21::multiset<Key>::swap(multiset& other) {
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

template <typename Key>
void s21::multiset<Key>::merge(multiset& other) {
  Node* addNode = other.head_;
  while (addNode != nullptr && addNode != other.end_) {
    // std::cout << addNode->value_ << std::endl;
    this->insert(addNode->value_);
    addNode = addNode->next_;
  }
  other.clear();
}

// Multiset Lookup
template <typename Key>
typename s21::multiset<Key>::size_type s21::multiset<Key>::count(
    const Key& key) {
  size_type res = 0;
  Node* node = this->head_;
  while (node != nullptr && node != this->end_) {
    if (node->value_ == key) res++;
    node = node->next_;
  }
  return res;
}

template <typename Key>
typename s21::multiset<Key>::iterator s21::multiset<Key>::find(const Key& key) {
  Node* node = this->head_;
  while (node != nullptr && node != this->end_) {
    if (node->value_ == key) break;
    node = node->next_;
  }
  if (node == this->end_) node = nullptr;
  return iterator(node);
}

template <typename Key>
bool s21::multiset<Key>::contains(const Key& key) {
  Node* node = this->head_;
  while (node != nullptr && node != this->end_) {
    if (node->value_ == key) break;
    node = node->next_;
  }
  if (node == this->end_) node = nullptr;
  return node ? true : false;
}

template <typename Key>
std::pair<typename s21::multiset<Key>::iterator,
          typename s21::multiset<Key>::iterator>
s21::multiset<Key>::equal_range(const Key& key) {
  return {this->lower_bound(key), this->upper_bound(key)};
}

template <typename Key>
typename s21::multiset<Key>::iterator s21::multiset<Key>::lower_bound(
    const Key& key) {
  Node* node = this->head_;
  while (node != nullptr && node != this->end_) {
    if (node->value_ != key)
      node = node->next_;
    else
      break;
  }
  if (node == this->end_) node = nullptr;
  return (iterator(node));
}

template <typename Key>
typename s21::multiset<Key>::iterator s21::multiset<Key>::upper_bound(
    const Key& key) {
  Node* node = lower_bound(key).IterNode;
  while (node != nullptr && node != this->end_) {
    if (node->next_->value_ <= key)
      node = node->next_;
    else
      break;
  }
  return iterator(node);
}

// Helper Multiset

template <typename Key>
void s21::multiset<Key>::rend() {
  this->end_->prev_ = this->tail_;
  this->end_->next_ = this->head_;
  this->end_->value_ = this->size_;
  if (this->head_) this->head_->prev_ = this->end_;
  if (this->tail_) this->tail_->next_ = this->end_;
}

template <typename Key>
typename s21::multiset<Key>::Node* s21::multiset<Key>::getPrevNode(
    const Key& key) {
  Node* prevNode = this->head_;
  while (prevNode->next_ != nullptr && prevNode->next_ != this->end_) {
    if (prevNode->next_->value_ <= key)
      prevNode = prevNode->next_;
    else
      break;
  }
  return prevNode;
}

template <typename Key>
template <typename... Args>
std::vector<std::pair<typename s21::multiset<Key>::iterator, bool>>
s21::multiset<Key>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> res;
  for (const auto& arg : {args...}) res.push_back({this->insert(arg), true});
  return res;
}

}  // namespace s21

#endif