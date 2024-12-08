#ifndef S21_MAP_TPP
#define S21_MAP_TPP

#include "s21_map.h"
namespace s21 {

template <typename Key, typename T>
s21::map<Key, T>::map()
    : root_(nullptr), max_(nullptr), min_(nullptr), end_(nullptr), size_(0) {
  this->end_ = new Node(this->size_, 0);
  this->rend();
}

template <typename Key, typename T>
s21::map<Key, T>::map(std::initializer_list<value_type> const& items) : map() {
  for (const auto& item : items) this->insert(item);
  this->rend();
}

template <typename Key, typename T>
s21::map<Key, T>::map(const map& m) : map() {
  for (auto i = iterator(m.min_); i != iterator(m.end_); ++i)
    this->insert(i.IterNode->key_, i.IterNode->value_);
}

template <typename Key, typename T>
s21::map<Key, T>::map(map&& m)
    : root_(m.root_), max_(m.max_), min_(m.min_), end_(m.end_), size_(m.size_) {
  m.root_ = nullptr;
  m.max_ = nullptr;
  m.min_ = nullptr;
  m.end_ = nullptr;
  m.size_ = 0;
}

template <typename Key, typename T>
s21::map<Key, T>::~map() {
  this->delNodes(this->root_);
  this->root_ = nullptr;
  this->min_ = nullptr;
  this->max_ = nullptr;
  this->size_ = 0;
  delete this->end_;
}

template <typename Key, typename T>
s21::map<Key, T>& s21::map<Key, T>::operator=(map&& m) {
  if (this != &m) {
    this->clear();

    this->swap(m);
  }
  return (*this);
}

// Map Element access
template <typename Key, typename T>
T& s21::map<Key, T>::at(const Key& key) {
  if (!this->contains(key)) throw std::out_of_range("No key");
  Node* node = this->getNode(key);
  return node->value_;
}

template <typename Key, typename T>
T& s21::map<Key, T>::operator[](const Key& key) {
  if (!this->contains(key)) throw std::out_of_range("No key");
  Node* node = this->getNode(key);
  return node->value_;
}

// Map Iterators
template <typename Key, typename T>
typename s21::map<Key, T>::iterator s21::map<Key, T>::begin() {
  return iterator(this->min_);
}

template <typename Key, typename T>
typename s21::map<Key, T>::iterator s21::map<Key, T>::end() {
  return iterator(this->end_);
}

// Map Capacity
template <typename Key, typename T>
bool s21::map<Key, T>::empty() {
  return this->size_ == 0;
}

template <typename Key, typename T>
typename s21::map<Key, T>::size_type s21::map<Key, T>::size() {
  return this->size_;
}

template <typename Key, typename T>
typename s21::map<Key, T>::size_type s21::map<Key, T>::max_size() {
  return std::numeric_limits<T>::max() / sizeof(value_type);
}

// Map Modifiers
template <typename Key, typename T>
void s21::map<Key, T>::clear() {
  this->delNodes(this->root_);
  this->root_ = nullptr;
  this->min_ = nullptr;
  this->max_ = nullptr;
  this->size_ = 0;
  this->rend();
}

template <typename Key, typename T>
std::pair<typename s21::map<Key, T>::iterator, bool> s21::map<Key, T>::insert(
    const value_type& value) {
  bool res = true;
  Node* newNode = this->getNode(value.first);
  if (newNode)
    res = false;
  else {
    Node* newNode = new Node(value.first, value.second);
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

template <typename Key, typename T>
std::pair<typename s21::map<Key, T>::iterator, bool> s21::map<Key, T>::insert(
    const Key& key, const T& obj) {
  return this->insert({key, obj});
}

template <typename Key, typename T>
std::pair<typename s21::map<Key, T>::iterator, bool>
s21::map<Key, T>::insert_or_assign(const Key& key, const T& obj) {
  bool res = true;
  Node* newNode = this->getNode(key);
  if (newNode) {
    res = false;
    newNode->value_ = obj;
  } else {
    Node* newNode = new Node(key, obj);
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

template <typename Key, typename T>
void s21::map<Key, T>::erase(iterator pos) {
  if (this->empty()) throw std::out_of_range("Map empty");
  if (pos.IterNode == nullptr) throw std::invalid_argument("Bad request");
  Node* delNode = pos.IterNode;
  if (delNode == this->end_) delNode = this->max_;
  s21::map<Key, T> newMap;

  for (auto i = iterator(this->min_); i != this->end(); ++i) {
    if (i.IterNode == delNode) continue;
    newMap.insert(i.IterNode->key_, i.IterNode->value_);
  }

  this->clear();
  this->swap(newMap);
  this->rend();
}

template <typename Key, typename T>
void s21::map<Key, T>::swap(map& other) {
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

template <typename Key, typename T>
void s21::map<Key, T>::merge(map& other) {
  if (other.empty()) return;

  for (auto i = iterator(other.min_); i != iterator(other.end_); ++i)
    this->insert(*i);

  other.clear();
}

// Map Lookup
template <typename Key, typename T>
bool s21::map<Key, T>::contains(const Key& key) {
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

// Helper Map

// template <typename Key, typename T>
// void s21::map<Key, T>::print() {
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

template <typename Key, typename T>
void s21::map<Key, T>::rend() {
  this->end_->key_ = this->size_;
  this->end_->value_ = 0;
  this->end_->owner_ = this->root_;
  if (this->root_) this->root_->owner_ = this->end_;
  this->takeMin();
  this->takeMax();
}

template <typename Key, typename T>
void s21::map<Key, T>::takeMin() {
  Node* node = this->root_;
  while (node != nullptr && node->left_ != nullptr) node = node->left_;
  this->min_ = node;
}

template <typename Key, typename T>
void s21::map<Key, T>::takeMax() {
  Node* node = this->root_;
  while (node != nullptr && node->right_ != nullptr) node = node->right_;
  this->max_ = node;
}

template <typename Key, typename T>
typename s21::map<Key, T>::Node* s21::map<Key, T>::getNode(const Key& key) {
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
  return (res ? node : nullptr);
}

template <typename Key, typename T>
typename s21::map<Key, T>::Node* s21::map<Key, T>::serchParentNode(
    const Key& key) {
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

template <typename Key, typename T>
void s21::map<Key, T>::delNodes(Node* node) {
  if (node) {
    this->delNodes(node->left_);
    this->delNodes(node->right_);
    delete node;
  }
}

template <typename Key, typename T>
template <typename... Args>
std::vector<std::pair<typename s21::map<Key, T>::iterator, bool>>
s21::map<Key, T>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> res;
  for (const auto& arg : {args...}) res.push_back(this->insert(arg));
  return res;
}

}  // namespace s21

#endif