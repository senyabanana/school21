#ifndef MAP_HPP
#define MAP_HPP

#include "../tree/s21_tree.hpp"

namespace s21 {
template <typename K, typename V>
class map : public tree<K, V> {
 public:
  map();
  map(std::initializer_list<typename tree<K, V>::value_type> const &items);
  map(const map &other);
  map(map &&other) noexcept;

  map &operator=(map &&other) noexcept;

  const V &at(const K &key) const;
  V &operator[](const K &key);

  std::pair<typename tree<K, V>::iterator, bool> insert(
      const typename tree<K, V>::value_type &value) noexcept override;
  std::pair<typename tree<K, V>::iterator, bool> insert(const K &key,
                                                        const V &obj);
  std::pair<typename tree<K, V>::iterator, bool> insert_or_assign(const K &key,
                                                                  const V &obj);

 private:
  V fake_ = V();

  void supportAt(const K &key, V &res, map<K, V> *tree) const;
};
}  // namespace s21

#include "s21_map.tpp"

#endif