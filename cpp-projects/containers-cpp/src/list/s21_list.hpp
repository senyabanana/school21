#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  typedef struct Node_ {
    value_type data_;
    Node_ *next_;
    Node_ *prev_;
    explicit Node_(value_type data) noexcept
        : data_(data), next_(nullptr), prev_(nullptr) {}
  } Node_;

  Node_ *head_;
  Node_ *tail_;
  Node_ *fake_;
  size_type size_;

 public:
  class ListIterator {
    friend class list<T>;

   public:
    ListIterator() noexcept : ptr_(nullptr){};
    ListIterator(typename list<T>::Node_ *node) noexcept : ptr_(node){};

    reference operator*() noexcept;
    ListIterator operator++(int) noexcept;
    ListIterator operator--(int) noexcept;
    ListIterator &operator++() noexcept;
    ListIterator &operator--() noexcept;
    ListIterator operator+(size_type value) noexcept;
    ListIterator operator-(size_type value) noexcept;
    bool operator==(ListIterator other) noexcept;
    bool operator!=(ListIterator other) noexcept;
    typename list<T>::Node_ *getNode() noexcept { return ptr_; }

   private:
    typename list<T>::Node_ *ptr_;
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator() noexcept : ListIterator() {}
    ListConstIterator(ListIterator &other) noexcept : ListIterator(other) {}
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  list() noexcept;
  list(size_type n);
  list(std::initializer_list<value_type> const &items) noexcept;
  list(const list &other) noexcept;
  list(list &&other) noexcept;
  ~list();
  list &operator=(list &&other) noexcept;
  list &operator=(const list<T> &other) noexcept;

  const_reference front() const noexcept;
  const_reference back() const noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value) noexcept;
  void erase(iterator pos) noexcept;
  void push_back(const_reference value) noexcept;
  void pop_back() noexcept;
  void push_front(const_reference value) noexcept;
  void pop_front() noexcept;
  void swap(list &other) noexcept;
  void merge(list &other) noexcept;
  void splice(const_iterator pos, list &other) noexcept;
  void reverse() noexcept;
  void unique() noexcept;
  void sort() noexcept;
  void initFake() noexcept;
  Node_ *getIteratorNode(iterator iter) noexcept;

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);
};
}  // namespace s21

#include "s21_list.tpp"
#include "s21_list_iterators.tpp"

#endif