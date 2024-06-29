#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack() noexcept;
  stack(std::initializer_list<value_type> const &items) noexcept;
  stack(const stack &other);
  stack(stack &&other) noexcept;
  ~stack();
  stack<T> &operator=(stack &&other) noexcept;

  const_reference top() const;

  bool empty() const;
  size_type size() const noexcept;

  void push(const_reference value) noexcept;
  void pop();
  void swap(stack &other) noexcept;

  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  typedef struct Node_ {
    value_type data_;
    Node_ *next_;
    Node_(value_type data) noexcept : data_(data), next_(nullptr) {}
  } Node_;

  Node_ *top_;
  size_type size_;
  void destroyStack();
};
}  // namespace s21

#include "s21_stack.tpp"

#endif