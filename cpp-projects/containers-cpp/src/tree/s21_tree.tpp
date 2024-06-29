using namespace s21;

template <typename K, typename V>
tree<K, V>::tree() noexcept
    : root_(nullptr), parent_(nullptr), left_(nullptr), right_(nullptr) {}

template <typename K, typename V>
tree<K, V>::tree(const value_type &elem) noexcept
    : parent_(nullptr), left_(nullptr), right_(nullptr) {
  root_ = new Node_(elem);
}

template <typename K, typename V>
tree<K, V>::tree(const std::initializer_list<value_type> &items)
    : root_(nullptr), parent_(nullptr), left_(nullptr), right_(nullptr) {
  for (value_type i : items) {
    insert(i);
  }
}

template <typename K, typename V>
tree<K, V>::tree(const tree &other) noexcept
    : root_(nullptr), parent_(nullptr), left_(nullptr), right_(nullptr) {
  *this = other;
}

template <typename K, typename V>
tree<K, V>::tree(tree &&other) noexcept {
  *this = std::move(other);
}

template <typename K, typename V>
tree<K, V>::~tree() {
  clear();
}

template <typename K, typename V>
tree<K, V> &tree<K, V>::operator=(const tree &other) noexcept {
  if (this != &other) {
    auto it = other.begin();
    clear();
    root_ = nullptr;
    parent_ = nullptr;
    left_ = nullptr;
    right_ = nullptr;
    std::pair<K, V> elem;
    elem.first = it->first;
    elem.second = it->second;
    insert(elem);
    while (true) {
      if (it == other.end()) {
        break;
      }
      ++it;
      elem.first = it->first;
      elem.second = it->second;
      insert(elem);
    }
  }
  return *this;
}

template <typename K, typename V>
tree<K, V> &tree<K, V>::operator=(tree &&other) noexcept {
  if (this != &other) {
    root_ = other.root_;
    parent_ = other.parent_;
    left_ = other.left_;
    right_ = other.right_;
    other.root_ = nullptr;
    other.parent_ = nullptr;
    other.left_ = nullptr;
    other.right_ = nullptr;
  }
  return *this;
}

template <typename K, typename V>
bool tree<K, V>::empty() const noexcept {
  return !root_;
}

template <typename K, typename V>
typename tree<K, V>::size_type tree<K, V>::size() const noexcept {
  int size = 0;
  getSize(size);
  return size;
}

template <typename K, typename V>
typename tree<K, V>::size_type tree<K, V>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(tree<V, V>) / 2;
}

template <typename K, typename V>
void tree<K, V>::clear() noexcept {
  delete root_;
  delete left_;
  delete right_;
}

template <typename K, typename V>
void tree<K, V>::swap(tree &other) {
  swapTrees(other);
}

template <typename K, typename V>
void tree<K, V>::merge(tree<K, V> &other) noexcept {
  if (!other.root_) {
    return;
  }
  auto iter = other.begin();
  std::pair<K, V> element;
  for (; iter != other.end(); iter++) {
    element.first = iter->first;
    element.second = iter->second;
    insert(element);
  }
  element.first = iter->first;
  element.second = iter->second;
  insert(element);
  other.clear();
  other.root_ = nullptr;
  other.parent_ = nullptr;
  other.left_ = nullptr;
  other.right_ = nullptr;
}

template <typename K, typename V>
bool tree<K, V>::contains(const K &key) const noexcept {
  bool contains = true;
  searchKey(key, contains);
  return contains;
}

template <typename K, typename V>
void tree<K, V>::insertElem(const value_type &elem, Iterator &iter,
                            bool &is_inserted) noexcept {
  if (!root_) {
    root_ = new Node_(elem);
    iter.setTree(this);
    is_inserted = true;
    return;
  }
  if (elem.first < root_->element_.first) {
    if (!left_) {
      left_ = new tree;
      left_->parent_ = this;
    }
    left_->insertElem(elem, iter, is_inserted);
  } else if (elem.first > root_->element_.first) {
    if (!right_) {
      right_ = new tree;
      right_->parent_ = this;
    }
    right_->insertElem(elem, iter, is_inserted);
  }
  balance();
}

template <typename K, typename V>
tree<K, V> *tree<K, V>::findMin(const tree *node) const {
  return (node->left_ && node->left_->root_ ? findMin(node->left_)
                                            : (tree<K, V> *)node);
}

template <typename K, typename V>
tree<K, V> *tree<K, V>::findMax(const tree *node) const {
  return (node->right_ && node->right_->root_ ? findMax(node->right_)
                                              : (tree<K, V> *)node);
}

template <typename K, typename V>
void tree<K, V>::multiSetInsert(const value_type &elem, Iterator &iter,
                                bool &is_inserted) noexcept {
  if (!root_) {
    root_ = new Node_(elem);
    iter.setTree(this);
    is_inserted = true;
    return;
  }
  if (elem.first <= root_->element_.first) {
    if (!left_) {
      left_ = new tree;
      left_->parent_ = this;
    }
    left_->multiSetInsert(elem, iter, is_inserted);
  } else if (elem.first >= root_->element_.first) {
    if (!right_) {
      right_ = new tree;
      right_->parent_ = this;
    }
    right_->multiSetInsert(elem, iter, is_inserted);
  }
  balance();
}

template <typename K, typename V>
inline unsigned char tree<K, V>::getHeight(tree *tree) {
  return (tree ? tree->root_ ? tree->root_->height_ : 0 : 0);
}

template <typename K, typename V>
inline int tree<K, V>::getBalance() {
  return (getHeight(right_) - getHeight(left_));
}

template <typename K, typename V>
void tree<K, V>::updateHeight() {
  root_->height_ = (getHeight(left_) > getHeight(right_) ? getHeight(left_)
                                                         : getHeight(right_)) +
                   1;
}

template <typename K, typename V>
void tree<K, V>::changePointers(tree<K, V> *temp, bool is_left) {
  auto *copy_this = new tree<K, V>();
  copy_this->root_ = root_;
  copy_this->parent_ = parent_;
  copy_this->left_ = left_;
  copy_this->right_ = right_;
  if (is_left) {
    temp->left_ = copy_this;
  } else {
    temp->right_ = copy_this;
  }
}

template <typename K, typename V>
void tree<K, V>::leftRotate() {
  tree *temp_right = right_;
  tree *temp_parent = parent_;
  right_ = temp_right->left_;
  changePointers(temp_right, true);
  updateHeight();
  temp_right->updateHeight();
  *this = std::move(*temp_right);
  parent_ = temp_parent;
  left_->parent_ = this;
  if (right_) {
    right_->parent_ = this;
  }
  if (left_) {
    if (left_->right_) {
      if (!left_->right_->parent_->root_) {
        left_->right_->parent_->root_ =
            new Node_(left_->right_->root_->element_);
      }
      left_->right_->parent_ = left_;
    }
    if (left_->left_) {
      if (!left_->left_->parent_->root_) {
        left_->left_->parent_->root_ = new Node_(left_->left_->root_->element_);
      }
      left_->left_->parent_ = left_;
    }
  }
  delete temp_right;
  temp_right = nullptr;
}

template <typename K, typename V>
void tree<K, V>::rightRotate() {
  tree *temp_left = left_;
  tree *temp_parent = parent_;
  left_ = temp_left->right_;
  changePointers(temp_left, false);
  updateHeight();
  temp_left->updateHeight();
  *this = std::move(*temp_left);
  parent_ = temp_parent;
  right_->parent_ = this;
  if (left_) {
    left_->parent_ = this;
  }
  if (right_) {
    if (right_->left_) {
      if (!right_->left_->parent_->root_) {
        right_->left_->parent_->root_ =
            new Node_(right_->left_->root_->element_);
      }
      right_->left_->parent_ = right_;
    }
    if (right_->right_) {
      if (!right_->right_->parent_->root_) {
        right_->right_->parent_->root_ =
            new Node_(right_->right_->root_->element_);
      }
      right_->right_->parent_ = right_;
    }
  }
  delete temp_left;
  temp_left = nullptr;
}

template <typename K, typename V>
void tree<K, V>::balance() {
  updateHeight();
  int balance = getBalance();
  if (balance == 2) {
    if (right_->getBalance() < 0) {
      right_->rightRotate();
    }
    leftRotate();
  } else if (balance == -2) {
    if (left_->getBalance() > 0) {
      left_->leftRotate();
    }
    rightRotate();
  }
}

template <typename K, typename V>
void tree<K, V>::getSize(int &size) const noexcept {
  if (root_ != nullptr) {
    ++size;
  }
  if (left_ != nullptr) {
    left_->getSize(size);
  }
  if (right_ != nullptr) {
    right_->getSize(size);
  }
}

template <typename K, typename V>
void tree<K, V>::swapTrees(tree<K, V> &other) {
  std::swap(root_, other.root_);
  std::swap(parent_, other.parent_);
  std::swap(left_, other.left_);
  std::swap(right_, other.right_);
}

template <typename K, typename V>
void tree<K, V>::searchKey(const K &key, bool &contains) const noexcept {
  if (!root_ || (!left_ && !right_ && root_->element_.first != key)) {
    contains = false;
  } else if (key < root_->element_.first) {
    if (left_) {
      left_->searchKey(key, contains);
    } else {
      contains = false;
    }
  } else if (key > root_->element_.first) {
    if (right_) {
      right_->searchKey(key, contains);
    } else {
      contains = false;
    }
  }
}

template <typename K, typename V>
void tree<K, V>::removeThis(tree<K, V> *current) {
  if (current->right_ || current->left_) {
    tree<K, V> *min =
        findMin(current->right_ ? current->right_ : current->left_);
    tree<K, V> *min_parent = min->parent_;
    if (min_parent->left_ == min) {
      min_parent->left_ = nullptr;
    } else {
      min_parent->right_ = nullptr;
    }
    min->parent_ = nullptr;
    if (left_) {
      min->left_ = left_;
      left_ = nullptr;
    }
    if (right_) {
      min->right_ = right_;
      right_ = nullptr;
    }
    swapTrees(*min);
    if (right_) {
      right_->parent_ = this;
    }
    delete min;
  } else {
    delete root_;
    root_ = nullptr;
  }
}

template <typename K, typename V>
void tree<K, V>::removeEdge(tree<K, V> *current, tree<K, V> *parent) {
  if (parent->left_ == current) {
    delete current;
    parent->left_ = nullptr;
  } else if (parent->right_ == current) {
    delete current;
    parent->right_ = nullptr;
  }
}

template <typename K, typename V>
void tree<K, V>::removeNode(tree<K, V> *current, tree<K, V> *parent) {
  tree<K, V> *min = findMin(current->right_ ? current->right_ : current->left_);
  tree<K, V> *min_parent = min->parent_;
  if (min_parent->right_ == min) {
    min_parent->right_ = nullptr;
  } else {
    min_parent->left_ = nullptr;
  }
  if (parent->right_ == current) {
    parent->right_ = min;
  } else {
    parent->left_ = min;
  }
  min->left_ = current->left_;
  min->right_ = current->right_;
  min->parent_ = parent;
  if (min->left_) {
    min->left_->parent_ = min;
  }
  if (min->right_) {
    min->right_->parent_ = min;
  }
  current->parent_ = nullptr;
  current->left_ = nullptr;
  current->right_ = nullptr;
  delete current;
}

template <typename K, typename V>
typename tree<K, V>::iterator tree<K, V>::begin() const {
  if (!left_ && !right_ && !root_) {
    throw std::out_of_range("Tree does not exist");
  }
  const tree<K, V> *temp_this = this;
  tree<K, V> *min_tree = findMin(left_ ? left_ : temp_this);
  return iterator(min_tree);
}

template <typename K, typename V>
typename tree<K, V>::iterator tree<K, V>::end() const {
  if (!left_ && !right_ && !root_) {
    throw std::out_of_range("Tree does not exist");
  }
  const tree<K, V> *temp_this = this;
  tree<K, V> *max_tree = findMin(right_ ? right_ : temp_this);
  return iterator(max_tree);
}

template <typename K, typename V>
std::pair<typename tree<K, V>::iterator, bool> tree<K, V>::insert(
    const tree::value_type &value) noexcept {
  iterator it;
  bool is_inserted = false;
  insertElem(value, it, is_inserted);
  std::pair<iterator, bool> res = {it, is_inserted};
  return res;
}

template <typename K, typename V>
void tree<K, V>::erase(tree<K, V>::iterator pos) {
  tree<K, V> *current = getTreeWithIter(pos);
  if (current == this) {
    removeThis(current);
  } else {
    auto parent = current->parent_;
    if (!current->left_ && !current->right_) {
      removeEdge(current, parent);
    } else {
      removeNode(current, parent);
    }
  }
  if (root_) {
    balance();
  }
}

template <typename K, typename V>
template <typename... Args>
std::vector<std::pair<typename tree<K, V>::iterator, bool>>
tree<K, V>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> res_vec;
  for (auto elem : {std::forward<Args>(args)...}) {
    res_vec.push_back(insert(elem));
  }
  return res_vec;
}