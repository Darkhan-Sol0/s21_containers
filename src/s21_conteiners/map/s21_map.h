#ifndef S21_MAP_H
#define S21_MAP_H

#include "../../s21_containers.h"

namespace s21 {
template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

 private:
  struct Node {
    Key key_;
    T value_;
    Node* left_;   // less
    Node* right_;  // granded
    Node* owner_;
    Node(const Key& key, const T& value)
        : key_(key),
          value_(value),
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
  template <typename key_type, typename mapped_type>
  class MapIterator {
   public:
    MapIterator() { IterNode = nullptr; }
    MapIterator(Node* node_) : IterNode(node_) {}
    friend class Map;
    Node* IterNode = nullptr;
    value_type operator*() {
      if (!this->IterNode) throw std::invalid_argument("Is NULL");
      return {this->IterNode->key_, this->IterNode->value_};
    }

    MapIterator operator++(int) {
      MapIterator temp = *this;
      ++(*this);
      return temp;
    }

    MapIterator operator--(int) {
      MapIterator temp = *this;
      --(*this);
      return temp;
    }

    MapIterator& operator++() {
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

    MapIterator& operator--() {
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
      return {this->IterNode->key_, this->IterNode->value_};
    }

    bool operator==(MapIterator other) {
      return this->IterNode == other.IterNode;
    }

    bool operator!=(MapIterator other) {
      return this->IterNode != other.IterNode;
    }
  };

  template <typename key_type, typename mapped_type>
  class MapConstIterator : public MapIterator<key_type, mapped_type> {
   public:
    MapConstIterator(MapIterator<key_type, mapped_type> other)
        : MapIterator<key_type, mapped_type>(other) {}
    const T& operator*() {
      return MapIterator<key_type, mapped_type>::operator*();
    }
  };

  using iterator = MapIterator<Key, T>;
  using const_iterator = MapConstIterator<Key, T>;

  // Map Member functions
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m);
  ~map();

  map& operator=(map&& m);

  // Map Element access
  T& at(const Key& key);
  T& operator[](const Key& key);

  // Map Iterators
  iterator begin();
  iterator end();

  // Map Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Map Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);

  // Map Lookup
  bool contains(const Key& key);

  // Helper Map
  // void print();
  void rend();
  void takeMin();
  void takeMax();
  Node* getNode(const Key& key);
  Node* serchParentNode(const Key& key);
  void delNodes(Node* node);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};

}  // namespace s21

#include "s21_map.tpp"

#endif