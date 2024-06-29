#ifndef MULTISET_HPP
#define MULTISET_HPP

#include "../set/s21_set.hpp"

namespace s21 {
template <typename Key>
class multiset : public set<Key> {
 public:
  using key_type = typename set<Key>::key_type;
  using value_type = typename set<Key>::value_type;

  multiset() : set<Key>() {}
  multiset(std::initializer_list<value_type> const &items) : set<Key>(items) {}
  multiset(const multiset &other) : set<Key>(other) {}
  multiset(multiset &&other) noexcept : set<Key>(std::move(other)) {}

  multiset &operator=(multiset &&other) noexcept {
    set<Key>::operator=(std::move(other));
    return *this;
  }

  std::pair<typename set<Key>::iterator, bool> insert(
      const value_type &value) noexcept {
    std::pair<key_type, value_type> tmp_el{value, value};
    typename tree<Key, Key>::iterator tree_it;
    bool is_inserted = false;
    std::pair<Key, Key> val{value, value};
    this->multiSetInsert(val, tree_it, is_inserted);
    typename set<Key>::iterator set_it(tree_it);
    std::pair<typename set<Key>::iterator, bool> res{set_it, is_inserted};
    return res;
  }
};
}  // namespace s21

#endif