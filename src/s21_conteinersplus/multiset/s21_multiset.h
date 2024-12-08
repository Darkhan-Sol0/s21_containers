#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "../../s21_containersplus.h"

namespace s21 {
template <typename Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

 private:
  struct Node {
    Key value_;
    Node* prev_;  // Lessed
    Node* next_;  // Granded
    Node(const Key& value) : value_(value), prev_(nullptr), next_(nullptr) {};
  };
  Node* head_;
  Node* tail_;
  Node* end_;
  Node* min_;
  size_type size_;

 public:
  template <typename key_type, typename value_type>
  class MultisetIterator {
   public:
    MultisetIterator() { IterNode = nullptr; }
    MultisetIterator(Node* node_) : IterNode(node_) {}
    friend class Multiset;
    Node* IterNode = nullptr;
    reference operator*() {
      if (!this->IterNode) throw std::invalid_argument("Is NULL");
      return this->IterNode->value_;
    }

    MultisetIterator operator++(int) {
      MultisetIterator temp = *this;
      ++(*this);
      return temp;
    }

    MultisetIterator operator--(int) {
      MultisetIterator temp = *this;
      --(*this);
      return temp;
    }

    MultisetIterator& operator++() {
      if (IterNode) {
        if (IterNode->right_) {
          IterNode = IterNode->right_;
          while (IterNode->left_) IterNode = IterNode->left_;
        } else {
          Node* parent = IterNode->owner_;
          while (parent && IterNode == parent->right_) {
            IterNode = parent;
            parent = parent->owner_;
          }
          IterNode = parent;
        }
      }
      return *this;
    }

    MultisetIterator& operator--() {
      if (IterNode) {
        if (IterNode->left_) {
          IterNode = IterNode->left_;
          while (IterNode->right_) IterNode = IterNode->right_;
        } else {
          Node* parent = IterNode->owner_;
          while (parent && IterNode == parent->left_) {
            IterNode = parent;
            parent = parent->owner_;
          }
          IterNode = parent;
        }
      }
      return *this;
    }

    value_type* operator->() {
      if (!IterNode) throw std::invalid_argument("IS NULL");
      return &(this->IterNode->value_);
    }

    bool operator==(MultisetIterator other) {
      return this->IterNode == other.IterNode;
    }

    bool operator!=(MultisetIterator other) {
      return this->IterNode != other.IterNode;
    }
  };

  template <typename key_type, typename value_type>
  class MultisetConstIterator : public MultisetIterator<key_type, value_type> {
   public:
    MultisetConstIterator(const MultisetIterator<key_type, value_type> other)
        : MultisetIterator<key_type, value_type>(other) {}
    const Key& operator*() {
      return MultisetIterator<key_type, value_type>::operator*();
    }
  };

  using iterator = MultisetIterator<Key, Key>;
  using const_iterator = MultisetConstIterator<Key, Key>;

  // Multiset Member functions
  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms);
  ~multiset();
  multiset& operator=(multiset&& ms);

  // Multiset Iterators
  iterator begin();
  iterator end();

  // Multiset Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Multiset Modifiers
  void clear();
  iterator insert(const value_type& value);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  // Multiset Lookup
  size_type count(const Key& key);
  iterator find(const Key& key);
  bool contains(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);

  // Helper Multiset

  void rend();
  Node* getPrevNode(const Key& key);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};
}  // namespace s21

#include "s21_multiset.tpp"

#endif