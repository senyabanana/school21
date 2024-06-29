using namespace s21;

template <typename K, typename V>
map<K, V>::map() : tree<K, V>(){};

template <typename K, typename V>
map<K, V>::map(
    std::initializer_list<typename tree<K, V>::value_type> const &items)
    : tree<K, V>(items) {}

template <typename K, typename V>
map<K, V>::map(const map &other) : tree<K, V>(other) {}

template <typename K, typename V>
map<K, V>::map(map &&other) noexcept : tree<K, V>(std::move(other)) {}

template <typename K, typename V>
map<K, V> &map<K, V>::operator=(map &&other) noexcept {
  tree<K, V>::operator=(std::move(other));
  return *this;
}

template <typename K, typename V>
const V &map<K, V>::at(const K &key) const {
  V &res = (V &)fake_;
  auto temp = this;
  supportAt(key, res, (map<K, V> *)temp);
  return res;
}

template <typename K, typename V>
V &map<K, V>::operator[](const K &key) {
  if (!this->contains(key)) {
    std::pair<K, V> elem{key, V()};
    std::pair<typename tree<K, V>::iterator, bool> res_it = this->insert(elem);
    return res_it.first->second;
  } else {
    auto it = this->begin();
    for (; it != this->end(); ++it) {
      if (it->first == key) {
        return it->second;
      }
    }
    return it->second;
  }
}

template <typename K, typename V>
std::pair<typename tree<K, V>::iterator, bool> map<K, V>::insert(
    const typename tree<K, V>::value_type &value) noexcept {
  return tree<K, V>::insert(value);
}

template <typename K, typename V>
std::pair<typename tree<K, V>::iterator, bool> map<K, V>::insert(const K &key,
                                                                 const V &obj) {
  typename tree<K, V>::iterator it;
  bool is_inserted = false;
  std::pair<K, V> elem{key, obj};
  this->insertElem(elem, it, is_inserted);
  std::pair<typename tree<K, V>::iterator, bool> res = {it, is_inserted};
  return res;
}

template <typename K, typename V>
std::pair<typename tree<K, V>::iterator, bool> map<K, V>::insert_or_assign(
    const K &key, const V &obj) {
  std::pair<typename tree<K, V>::iterator, bool> res_it;
  res_it = insert(key, obj);
  if (!res_it.second) {
    auto it = this->begin();
    while (it->first != key) {
      ++it;
    }
    res_it.first.setTree(it.getTree());
    res_it.first->second = obj;
  }
  return res_it;
}

template <typename K, typename V>
void map<K, V>::supportAt(const K &key, V &res, map<K, V> *tree) const {
  if (!tree->root_ ||
      (!tree->left_ && tree->right_ && tree->root_->element_.first != key)) {
    throw std::out_of_range("Key does not exists");
  }
  if (key < tree->root_->element_.first) {
    map<K, V>::supportAt(key, res, (map<K, V> *)tree->left_);
  } else if (key > tree->root_->element_.first) {
    map<K, V>::supportAt(key, res, (map<K, V> *)tree->right_);
  } else {
    res = tree->root_->element_.second;
  }
}