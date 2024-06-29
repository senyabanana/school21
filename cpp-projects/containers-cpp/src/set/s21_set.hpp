#ifndef SET_HPP
#define SET_HPP

#include "../tree/s21_tree.hpp"

namespace s21 {
template <typename Key>
class set : public tree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = Key &;
  using const_reference = const Key &;
  using size_type = size_t;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &other);
  set(set &&other) noexcept;

  set &operator=(set &&other) noexcept;

 protected:
  class ConstSetIterator : public tree<Key, Key>::ConstIterator {
   public:
    ConstSetIterator() noexcept : tree<Key, Key>::ConstIterator() {}
    ConstSetIterator(const ConstSetIterator &other)
        : tree<Key, Key>::ConstIterator(other) {}
    explicit ConstSetIterator(tree<Key, Key> *tr) noexcept
        : tree<Key, Key>::ConstIterator(tr) {}
    explicit ConstSetIterator(typename tree<Key, Key>::ConstIterator &other) {
      tree<Key, Key> *tree = other.getTree();
      this->tree_ = tree;
    }

    ConstSetIterator &operator=(const ConstSetIterator &other) {
      ConstSetIterator temp(other);
      this->tree_ = temp.getTree();
      return *this;
    }
    const_reference operator*() {
      typename tree<Key, Key>::Node_ *rt = this->getNode();
      return rt->element_.first;
    }
  };

  class SetIterator : public ConstSetIterator {
   public:
    SetIterator() noexcept : ConstSetIterator() {}
    SetIterator(const SetIterator &other) : ConstSetIterator(other) {}
    explicit SetIterator(tree<Key, Key> *tree) noexcept
        : ConstSetIterator(tree) {}
    explicit SetIterator(typename tree<Key, Key>::Iterator &other) {
      tree<Key, Key> *tree = other.getTree();
      this->tree_ = tree;
    }

    SetIterator &operator=(const SetIterator &other) {
      ConstSetIterator::operator=(other);
      return *this;
    }
  };

 public:
  using const_iterator = ConstSetIterator;
  using iterator = SetIterator;
  using tree<Key, Key>::insert;

  iterator begin() const;
  iterator end() const;

  virtual std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);

  iterator find(const Key &key) const;
};
}  // namespace s21

#include "s21_set.tpp"

#endif