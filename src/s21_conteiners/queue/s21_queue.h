#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "../../s21_containers.h"
namespace s21 {

template <typename T>

class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

 private:
  struct Node {
    T value_;
    Node* next_;
    Node* prev_;
    Node(const T& value) : value_(value), next_(nullptr), prev_(nullptr) {};
  };
  Node* head_;
  Node* tail_;
  size_t size_;

 public:
  queue();
  queue(std::initializer_list<value_type> const& items);
  queue(const queue& q);
  queue(queue&& q);
  ~queue();

  queue& operator=(queue&& q);

  const_reference front();
  const_reference back();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(queue& other);

  // void print();

  template <typename... Args>
  void insert_many_back(Args&&... args);
};

}  // namespace s21

#include "s21_queue.tpp"

#endif