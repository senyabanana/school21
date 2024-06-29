using namespace s21;

template <typename Key>
set<Key>::set() : tree<Key, Key>() {}

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const &items) {
  for (value_type i : items) {
    insert(i);
  }
}

template <typename Key>
set<Key>::set(const set &other) : tree<Key, Key>(other) {}

template <typename Key>
set<Key>::set(set &&other) noexcept : tree<Key, Key>(std::move(other)) {}

template <typename Key>
set<Key> &set<Key>::operator=(set &&other) noexcept {
  tree<Key, Key>::operator=(std::move(other));
  return *this;
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() const {
  if (!this->left_ && !this->right_ && !this->root_) {
    throw std::out_of_range("Set does not exist");
  }
  const tree<Key, Key> *temp_this = this;
  tree<Key, Key> *min_tree =
      this->findMin(this->left_ ? this->left_ : temp_this);
  return iterator(min_tree);
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() const {
  if (!this->left_ && !this->right_ && !this->root_) {
    throw std::out_of_range("Set does not exist");
  }
  const tree<Key, Key> *temp_this = this;
  tree<Key, Key> *max_tree =
      this->findMax(this->right_ ? this->right_ : temp_this);
  return iterator(max_tree);
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type &value) {
  std::pair<key_type, value_type> temp_elem{value, value};
  typename tree<Key, Key>::iterator tree_it;
  bool is_inserted = false;
  std::pair<Key, Key> val{value, value};
  this->insertElem(val, tree_it, is_inserted);
  iterator set_it{tree_it};
  std::pair<iterator, bool> res{set_it, is_inserted};
  return res;
}

template <typename Key>
void set<Key>::erase(iterator pos) {
  typename tree<Key, Key>::iterator it;
  it.setTree(pos.getTree());
  tree<Key, Key>::erase(it);
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key &key) const {
  if (!this->contains(key)) {
    throw std::out_of_range("Key does not exist");
  }
  auto it = begin();
  while (*it != key) {
    it++;
  }
  return it;
}