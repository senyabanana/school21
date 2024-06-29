using namespace s21;

template <typename T>
list<T>::list() noexcept : head_(nullptr), tail_(nullptr), size_(0) {
  initFake();
}

template <typename T>
list<T>::list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
  if (n <= 0) {
    throw std::out_of_range("Index out of range");
  }
  initFake();
  while (n-- > 0) {
    push_back(T());
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) noexcept
    : head_(nullptr), tail_(nullptr), size_(0) {
  initFake();
  for (value_type i : items) {
    push_back(i);
  }
}

template <typename T>
list<T>::list(const list& other) noexcept
    : head_(nullptr), tail_(nullptr), size_(0) {
  initFake();
  *this = other;
}

template <typename T>
list<T>::list(list&& other) noexcept {
  if (this != &other) {
    *this = std::move(other);
    other.initFake();
  }
}

template <typename T>
list<T>::~list() {
  clear();
  delete fake_;
}

template <typename T>
list<T>& list<T>::operator=(list<T>&& other) noexcept {
  if (this != &other) {
    list<T> temp_list(std::move(other));
    *this = temp_list;
  }
  return *this;
}

template <typename T>
list<T>& list<T>::operator=(const list<T>& other) noexcept {
  if (this != &other) {
    clear();
    if (fake_ == nullptr) {
      initFake();
    }
    Node_* temp_node = other.head_;
    if (temp_node != nullptr) {
      while (temp_node != other.fake_) {
        push_back(temp_node->data_);
        temp_node = temp_node->next_;
      }
    }
  }
  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::front() const noexcept {
  return head_ ? head_->data_ : fake_->data_;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const noexcept {
  return tail_ ? tail_->data_ : front();
}

template <typename T>
typename list<T>::iterator list<T>::begin() noexcept {
  return list<T>::ListIterator(head_ ? head_ : fake_);
}

template <typename T>
typename list<T>::iterator list<T>::end() noexcept {
  return list<T>::ListIterator(fake_);
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const noexcept {
  return list<T>::ListConstIterator(head_ ? head_ : fake_);
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() const noexcept {
  return list<T>::ListConstIterator(fake_);
}

template <typename T>
bool list<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(Node_) / 2;
}

template <typename T>
void list<T>::clear() noexcept {
  while (size_ != 0) {
    pop_front();
  }
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) noexcept {
  Node_* current_node = getIteratorNode(pos);
  auto* new_node = new Node_(value);
  if (size_ <= 1) {
    if (current_node == fake_) {
      push_back(value);
    } else if (current_node == head_) {
      push_front(value);
    }
    delete new_node;
    new_node = nullptr;
    return iterator(head_);
  } else {
    Node_* prev_node = current_node->prev_;
    new_node->next_ = current_node;
    new_node->prev_ = prev_node;
    current_node->prev_ = new_node;
    prev_node->next_ = new_node;
    if (current_node == fake_) {
      tail_ = new_node;
    } else if (current_node == head_) {
      head_ = new_node;
    }
    ++size_;
  }
  return iterator(new_node);
}

template <typename T>
void list<T>::erase(iterator pos) noexcept {
  Node_* current_ptr = getIteratorNode(pos);
  if (current_ptr == fake_) {
    return;
  }
  if (current_ptr == head_) {
    pop_front();
  } else if (current_ptr == tail_) {
    pop_back();
  } else {
    Node_* next_ptr = current_ptr->next_;
    Node_* prev_ptr = current_ptr->prev_;
    next_ptr->prev_ = prev_ptr;
    prev_ptr->next_ = next_ptr;
    delete current_ptr;
    --size_;
  }
}

template <typename T>
void list<T>::push_back(const_reference value) noexcept {
  auto* new_node = new Node_(value);
  if (head_ == nullptr) {
    head_ = new_node;
    head_->next_ = fake_;
    head_->prev_ = fake_;
    fake_->next_ = head_;
    fake_->prev_ = head_;
  } else if (tail_ == nullptr) {
    tail_ = new_node;
    tail_->next_ = fake_;
    tail_->prev_ = head_;
    head_->next_ = tail_;
    fake_->prev_ = tail_;
  } else {
    new_node->prev_ = tail_;
    tail_->next_ = new_node;
    tail_ = new_node;
    fake_->prev_ = tail_;
    tail_->next_ = fake_;
  }
  ++size_;
  fake_->data_ = size_;
}

template <typename T>
void list<T>::pop_back() noexcept {
  if (tail_ != nullptr) {
    Node_* removed_tail = tail_;
    if (tail_->prev_ != fake_) {
      tail_ = tail_->prev_;
    } else {
      tail_ = nullptr;
    }
    if (removed_tail->prev_ != nullptr) {
      delete removed_tail;
    }
    if (size_ == 2) {
      fake_->next_ = head_;
      fake_->prev_ = head_;
      head_->next_ = fake_;
      head_->prev_ = fake_;
      tail_ = nullptr;
    }
    --size_;
    fake_->data_ = size_;
  }
}

template <typename T>
void list<T>::push_front(const_reference value) noexcept {
  auto* new_node = new Node_(value);
  if (head_ == nullptr) {
    head_ = new_node;
    head_->next_ = fake_;
    head_->prev_ = fake_;
    fake_->next_ = head_;
    fake_->prev_ = head_;
  } else if (tail_ == nullptr) {
    tail_ = head_;
    tail_->next_ = fake_;
    tail_->prev_ = new_node;
    fake_->next_ = new_node;
    fake_->prev_ = tail_;
    head_ = new_node;
  } else {
    new_node->next_ = head_;
    head_ = new_node;
    fake_->next_ = head_;
    head_->prev_ = fake_;
  }
  ++size_;
  fake_->data_ = size_;
}

template <typename T>
void list<T>::pop_front() noexcept {
  if (head_ != nullptr) {
    Node_* removed_head = head_;
    if (head_->next_ != fake_) {
      head_ = head_->next_;
    } else {
      head_ = nullptr;
    }
    if (removed_head->next_ != nullptr) {
      delete removed_head;
    }
    if (size_ == 2) {
      head_ = tail_;
      fake_->next_ = head_;
      fake_->prev_ = head_;
      head_->next_ = fake_;
      head_->prev_ = fake_;
      tail_ = nullptr;
    }
    --size_;
    fake_->data_ = size_;
  }
}

template <typename T>
void list<T>::swap(list& other) noexcept {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(fake_, other.fake_);
  std::swap(size_, other.size_);
}

template <typename T>
void list<T>::merge(list& other) noexcept {
  if (this != &other) {
    iterator it_this = begin();
    iterator it_other = other.begin();
    while (!other.empty()) {
      if (this->empty() || *it_this > *it_other) {
        insert(it_this, *it_other);
        other.erase(it_other);
        ++it_other;
      } else {
        if (it_this == end() || *it_this > *it_other) {
          insert(it_this, *it_other);
          other.erase(it_other);
          ++it_other;
        } else {
          ++it_other;
        }
      }
    }
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) noexcept {
  if (this != &other && !other.empty()) {
    for (auto iter = other.begin(); iter != other.end(); ++iter) {
      insert(pos, *iter);
    }
    other.clear();
  }
}

template <typename T>
void list<T>::reverse() noexcept {
  if (size_ > 1) {
    Node_ head_data = *head_;
    Node_ tail_data = *tail_;
    Node_* head_ptr = head_;
    Node_* tail_ptr = tail_;
    for (size_type i = 0; i < size_ / 2; i++) {
      head_ptr->data_ = tail_data.data_;
      tail_ptr->data_ = head_data.data_;
      head_ptr = head_ptr->next_;
      tail_ptr = tail_ptr->prev_;
      head_data = *head_ptr;
      tail_data = *tail_ptr;
    }
  }
}

template <typename T>
void list<T>::unique() noexcept {
  if (size_ <= 1) {
    return;
  }
  auto it = begin();
  auto it_next = it + 1;
  list<T> temp_list;
  while (it != end()) {
    if (*it == *it_next) {
      ++it;
      ++it_next;
      continue;
    } else {
      temp_list.push_back(*it);
    }
    ++it;
    ++it_next;
  }
  *this = std::move(temp_list);
}

template <typename T>
void list<T>::sort() noexcept {
  if (size_ <= 1) {
    return;
  }
  bool swapped = true;
  while (swapped) {
    swapped = false;
    Node_* current = head_;
    Node_* last = tail_->next_;
    while (current->next_ != last) {
      if (current->data_ > current->next_->data_) {
        std::swap(current->data_, current->next_->data_);
        swapped = true;
      }
      current = current->next_;
    }
    last = current;
  }
}

template <typename T>
void list<T>::initFake() noexcept {
  fake_ = new Node_(T());
  fake_->next_ = nullptr;
  fake_->prev_ = nullptr;
}

template <typename T>
typename list<T>::Node_* list<T>::getIteratorNode(iterator iter) noexcept {
  return iter.getNode();
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  Node_* pos_node = getIteratorNode(pos);
  iterator it(pos_node);
  for (auto elem : {std::forward<Args>(args)...}) {
    insert(it, elem);
  }
  --it;
  return it;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  const_iterator it = end();
  insert_many(it, std::forward<Args>(args)...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  for (auto elem : {std::forward<Args>(args)...}) {
    push_front(elem);
  }
}