#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <limits>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  array();
  array(std::initializer_list<value_type> const& items);
  array(const array& other);
  array(array&& other) noexcept;
  ~array();
  array<T, N>& operator=(array<T, N>&& other) noexcept;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void swap(array& other);
  void fill(const_reference value);

 private:
  size_type size_ = N;
  value_type arr_[N];
};
}  // namespace s21

#include "s21_array.tpp"

#endif