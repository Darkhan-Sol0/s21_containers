#ifndef S21_SET_TPP
#define S21_SET_TPP
#include "s21_set.h"

namespace s21 {
template <typename Key>
s21::set<Key>::set()
    : root_(nullptr), max_(nullptr), min_(nullptr), end_(nullptr), size_(0) {
  this->end_ = new Node(this->size_);
  this->rend();
}

template <typename Key>
s21::set<Key>::set(std::initializer_list<value_type> const& items) : set() {
  for (const auto& item : items) this->insert(item);
  this->rend();
}

template <typename Key>
s21::set<Key>::set(const set& s) : set() {
  for (auto i = iterator(s.min_); i != iterator(s.end_); ++i)
    this->insert(i.IterNode->value_);
  this->rend();
}

template <typename Key>
s21::set<Key>::set(set&& s)
    : root_(s.root_), max_(s.max_), min_(s.min_), end_(s.end_), size_(s.size_) {
  s.root_ = nullptr;
  s.max_ = nullptr;
  s.min_ = nullptr;
  s.end_ = nullptr;
  s.size_ = 0;
}

template <typename Key>
s21::set<Key>::~set() {
  this->delNodes(this->root_);
  this->root_ = nullptr;
  this->min_ = nullptr;
  this->max_ = nullptr;
  this->size_ = 0;
  delete this->end_;
}

template <typename Key>
s21::set<Key>& s21::set<Key>::operator=(set&& s) {
  if (this != &s) {
    this->clear();
    this->swap(s);
  }
  return (*this);
}

// Set Iterators
template <typename Key>
typename s21::set<Key>::iterator s21::set<Key>::begin() {
  return iterator(this->min_);
}

template <typename Key>
typename s21::set<Key>::iterator s21::set<Key>::end() {
  return iterator(this->end_);
}

// Set Capacity
template <typename Key>
bool s21::set<Key>::empty() {
  return this->size_ == 0;
}

template <typename Key>
typename s21::set<Key>::size_type s21::set<Key>::size() {
  return this->size_;
}

template <typename Key>
typename s21::set<Key>::size_type s21::set<Key>::max_size() {
  return std::numeric_limits<Key>::max() / sizeof(value_type);
}

// Set Modifiers
template <typename Key>
void s21::set<Key>::clear() {
  this->delNodes(this->root_);
  this->root_ = nullptr;
  this->min_ = nullptr;
  this->max_ = nullptr;
  this->size_ = 0;
  this->rend();
}

template <typename Key>
std::pair<typename s21::set<Key>::iterator, bool> s21::set<Key>::insert(
    const value_type& value) {
  bool res = true;
  Node* newNode = this->getNode(value);
  if (newNode)
    res = false;
  else {
    Node* newNode = new Node(value);
    if (this->empty()) {
      this->root_ = newNode;
    } else {
      Node* parent = this->serchParentNode(newNode->key_);
      if (newNode->key_ < parent->key_) {
        parent->left_ = newNode;
        newNode->owner_ = parent;
      } else if (newNode->key_ > parent->key_) {
        parent->right_ = newNode;
        newNode->owner_ = parent;
      }
    }
    ++this->size_;
    this->rend();
  }
  return {iterator(newNode), res};
}

template <typename Key>
void s21::set<Key>::erase(iterator pos) {
  if (this->empty()) throw std::out_of_range("Map empty");
  if (pos.IterNode == nullptr) throw std::invalid_argument("Bad request");
  Node* delNode = pos.IterNode;
  if (delNode == this->end_) delNode = this->max_;
  s21::set<Key> newMap;

  for (auto i = iterator(this->min_); i != this->end(); ++i) {
    if (i.IterNode == delNode) continue;
    newMap.insert(i.IterNode->value_);
  }

  this->clear();
  this->swap(newMap);
  this->rend();
}

template <typename Key>
void s21::set<Key>::swap(set& other) {
  Node* tempRoot = other.root_;
  Node* tempMin = other.min_;
  Node* tempMax = other.max_;
  Node* tempEnd = other.end_;
  size_type tempSize = other.size_;

  other.root_ = this->root_;
  other.min_ = this->min_;
  other.max_ = this->max_;
  other.end_ = this->end_;
  other.size_ = this->size_;

  this->root_ = tempRoot;
  this->min_ = tempMin;
  this->max_ = tempMax;
  this->end_ = tempEnd;
  this->size_ = tempSize;
}

template <typename Key>
void s21::set<Key>::merge(set& other) {
  if (other.empty()) return;

  for (auto i = iterator(other.min_); i != iterator(other.end_); ++i)
    this->insert(*i);

  other.clear();
}

// Set Lookup
template <typename Key>
typename s21::set<Key>::iterator s21::set<Key>::find(const Key& key) {
  Node* node = this->root_;
  while (node != nullptr && node != this->end_) {
    if (node->key_ > key)
      node = node->left_;
    else if (node->key_ < key)
      node = node->right_;
    else {
      break;
    }
  }
  return iterator(node);
}

template <typename Key>
bool s21::set<Key>::contains(const Key& key) {
  bool res = false;
  Node* node = this->root_;
  while (node != nullptr && node != this->end_) {
    if (node->key_ > key)
      node = node->left_;
    else if (node->key_ < key)
      node = node->right_;
    else {
      res = true;
      break;
    }
  }
  return res;
}

// Helper Set

template <typename Key>
void s21::set<Key>::rend() {
  this->end_->key_ = this->size_;
  this->end_->value_ = this->size_;
  this->end_->owner_ = this->root_;
  if (this->root_) this->root_->owner_ = this->end_;
  this->takeMin();
  this->takeMax();
}

template <typename Key>
void s21::set<Key>::takeMin() {
  Node* node = this->root_;
  while (node != nullptr && node->left_ != nullptr) node = node->left_;
  this->min_ = node;
}

template <typename Key>
void s21::set<Key>::takeMax() {
  Node* node = this->root_;
  while (node != nullptr && node->right_ != nullptr) node = node->right_;
  this->max_ = node;
}

template <typename Key>
void s21::set<Key>::delNodes(Node* node) {
  if (node) {
    delNodes(node->left_);
    delNodes(node->right_);
    delete node;
  }
}

template <typename Key>
typename s21::set<Key>::Node* s21::set<Key>::getNode(value_type value) {
  bool res = false;
  Node* node = this->root_;
  while (node != nullptr && node != this->end_) {
    if (node->key_ > value)
      node = node->left_;
    else if (node->key_ < value)
      node = node->right_;
    else {
      res = true;
      break;
    }
  }
  return (res ? node : nullptr);
}

template <typename Key>
typename s21::set<Key>::Node* s21::set<Key>::serchParentNode(const Key& key) {
  Node* parent = this->root_;
  Node* child = parent;

  while (child != nullptr) {
    parent = child;
    if (key < parent->key_)
      child = child->left_;
    else if (key > parent->key_)
      child = child->right_;
  }
  return parent;
}

// template <typename Key>
// void s21::set<Key>::print() {
//   if (!this->empty())
//     for (auto i = iterator(this->min_); i != this->end(); ++i)
//       std::cout << "owner: "
//                 << (i.IterNode->owner_ && i.IterNode->owner_ != this->end_
//                         ? i.IterNode->owner_->key_
//                         : -99)
//                 << std::endl
//                 << "node: " << i.IterNode->key_ << std::endl
//                 << "left-> "
//                 << (i.IterNode->left_ ? i.IterNode->left_->key_ : -99)
//                 << " right-> "
//                 << (i.IterNode->right_ ? i.IterNode->right_->key_ : -99)
//                 << std::endl
//                 << std::endl;
//   std::cout << std::endl;
// }

template <typename Key>
template <typename... Args>
std::vector<std::pair<typename s21::set<Key>::iterator, bool>>
s21::set<Key>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> res;
  for (const auto& arg : {args...}) res.push_back(this->insert(arg));
  return res;
}

}  // namespace s21

#endif