using namespace s21;

template <typename K, typename V>
typename tree<K, V>::ConstIterator tree<K, V>::ConstIterator::operator++(int) {
  ConstIterator temp(*this);
  increment();
  return temp;
}

template <typename K, typename V>
typename tree<K, V>::ConstIterator tree<K, V>::ConstIterator::operator--(int) {
  ConstIterator temp(*this);
  decrement();
  return temp;
}

template <typename K, typename V>
typename tree<K, V>::ConstIterator tree<K, V>::ConstIterator::operator++() {
  increment();
  return *this;
}

template <typename K, typename V>
typename tree<K, V>::ConstIterator tree<K, V>::ConstIterator::operator--() {
  decrement();
  return *this;
}

template <typename K, typename V>
typename tree<K, V>::ConstIterator tree<K, V>::ConstIterator::operator+=(
    size_type n) {
  while (n-- > 0) {
    operator++();
  }
  return *this;
}

template <typename K, typename V>
typename tree<K, V>::ConstIterator tree<K, V>::ConstIterator::operator-=(
    size_type n) {
  while (n-- > 0) {
    operator--();
  }
  return *this;
}

template <typename K, typename V>
const typename tree<K, V>::value_type* tree<K, V>::ConstIterator::operator->() {
  return &(tree_->root_->element_);
}

template <typename K, typename V>
bool tree<K, V>::ConstIterator::operator!=(const ConstIterator& other) {
  return this->tree_ != other.tree_;
}

template <typename K, typename V>
bool tree<K, V>::ConstIterator::operator==(const ConstIterator& other) {
  return this->tree_ == other.tree_;
}

template <typename K, typename V>
void tree<K, V>::ConstIterator::increment() {
  if (tree_->right_) {
    tree_ = tree_->findMin(tree_->right_);
  } else if (!tree_->left_ && !tree_->right_) {
    if (tree_->parent_) {
      if (tree_->parent_->left_ == tree_) {
        tree_ = tree_->parent_;
      } else if (tree_->parent_->right_ == tree_) {
        if (tree_->parent_ && tree_->parent_->parent_) {
          tree_ = tree_->parent_->parent_;
        }
      }
    }
  } else if (tree_->parent_) {
    tree_ = tree_->parent_;
  }
}

template <typename K, typename V>
void tree<K, V>::ConstIterator::decrement() {
  if (tree_->left_) {
    tree_ = tree_->findMin(tree_->left_);
  } else if (!tree_->left_ && !tree_->right_) {
    if (tree_->parent_) {
      if (tree_->parent_->right_ == tree_) {
        tree_ = tree_->parent_;
      } else if (tree_->parent_->left_ == tree_) {
        if (tree_->parent_ && tree_->parent_->parent_) {
          tree_ = tree_->parent_->parent_;
        }
      }
    }
  } else if (tree_->parent_) {
    tree_ = tree_->parent_;
  }
}

template <typename K, typename V>
typename tree<K, V>::value_type* tree<K, V>::Iterator::operator->() {
  return &(this->tree_->root_->element_);
}