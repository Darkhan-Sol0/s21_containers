#ifndef S21_SET_H
#define S21_SET_H

#include "../../s21_containers.h"

namespace s21 {
template <typename Key>

class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

 private:
  struct Node {
    Key key_;
    Key value_;
    Node* left_;   // less
    Node* right_;  // granded
    Node* owner_;
    Node(const Key& key)
        : key_(key),
          value_(key),
          left_(nullptr),
          right_(nullptr),
          owner_(nullptr) {};
  };
  Node* root_;
  Node* max_;
  Node* min_;
  Node* end_;
  size_t size_;

 public:
  template <typename key_type, typename value_type>
  class SetIterator {
   public:
    SetIterator() { IterNode = nullptr; }
    SetIterator(Node* node_) : IterNode(node_) {}
    friend class Set;
    Node* IterNode = nullptr;
    reference operator*() {
      if (!this->IterNode) throw std::invalid_argument("Is NULL");
      return this->IterNode->value_;
    }

    SetIterator operator++(int) {
      SetIterator temp = *this;
      ++(*this);
      return temp;
    }

    SetIterator operator--(int) {
      SetIterator temp = *this;
      --(*this);
      return temp;
    }

    SetIterator& operator++() {
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

    SetIterator& operator--() {
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

    bool operator==(SetIterator other) {
      return this->IterNode == other.IterNode;
    }

    bool operator!=(SetIterator other) {
      return this->IterNode != other.IterNode;
    }
  };

  template <typename key_type, typename value_type>
  class SetConstIterator : public SetIterator<key_type, value_type> {
   public:
    SetConstIterator(const SetIterator<key_type, value_type> other)
        : SetIterator<key_type, value_type>(other) {}
    const Key& operator*() {
      return SetIterator<key_type, value_type>::operator*();
    }
  };

  using iterator = SetIterator<Key, Key>;
  using const_iterator = SetConstIterator<Key, Key>;

  // Set Member functions
  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s);
  ~set();

  set& operator=(set&& s);

  // Set Iterators
  iterator begin();
  iterator end();

  // Set Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Set Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);

  // Set Lookup
  iterator find(const Key& key);
  bool contains(const Key& key);

  // Helper Set
  void rend();
  void takeMin();
  void takeMax();
  void print();
  void delNodes(Node* node);
  Node* serchParentNode(const Key& key);
  Node* getNode(value_type value);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};

}  // namespace s21

#include "s21_set.tpp"

#endif