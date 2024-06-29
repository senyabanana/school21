#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue() noexcept;
  queue(std::initializer_list<value_type> const &items) noexcept;
  queue(const queue &other);
  queue(queue &&other) noexcept;
  ~queue();
  queue &operator=(queue &&other) noexcept;

  const_reference front() const;
  const_reference back() const;

  bool empty() const noexcept;
  size_type size() const noexcept;

  void push(const_reference value) noexcept;
  void pop();
  void swap(queue &other) noexcept;

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  typedef struct Node_ {
    value_type data_;
    Node_ *next_;
    explicit Node_(value_type data) noexcept : data_(data), next_(nullptr) {}
  } Node_;

  Node_ *head_;
  Node_ *tail_;
  size_type size_;
  void destroyQueue();
};
}  // namespace s21

#include "s21_queue.tpp"

#endif