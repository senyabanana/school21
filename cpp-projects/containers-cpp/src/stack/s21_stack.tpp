using namespace s21;

template <typename T>
stack<T>::stack() noexcept : top_(nullptr), size_(0){};

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const &items) noexcept
    : top_(nullptr), size_(0) {
  for (value_type i : items) {
    push(i);
  }
}

template <typename T>
stack<T>::stack(const stack &other) : top_(nullptr), size_(0) {
  *this = other;
}

template <typename T>
stack<T>::stack(stack &&other) noexcept : top_(nullptr), size_(0) {
  *this = std::move(other);
}

template <typename T>
stack<T>::~stack() {
  destroyStack();
}

template <typename T>
stack<T> &stack<T>::operator=(stack<T> &&other) noexcept {
  if (this != &other) {
    destroyStack();
    top_ = std::move(other.top_);
    size_ = std::move(other.size_);
  }
  return *this;
}

template <typename T>
typename stack<T>::const_reference stack<T>::top() const {
  if (top_ == nullptr) {
    throw std::logic_error("stack is empty");
  }
  return top_->data_;
}

template <typename T>
bool stack<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename stack<T>::size_type stack<T>::size() const noexcept {
  return size_;
}

template <typename T>
void stack<T>::push(const_reference value) noexcept {
  Node_ *new_node = new Node_(value);
  if (top_ == nullptr) {
    top_ = new_node;
  } else {
    new_node->next_ = top_;
    top_ = new_node;
  }
  size_++;
}

template <typename T>
void stack<T>::pop() {
  if (top_ == nullptr) {
    throw std::logic_error("stack is empty");
  }
  Node_ *prev_node = top_->next_;
  delete top_;
  top_ = prev_node;
  size_--;
}

template <typename T>
void stack<T>::swap(stack &other) noexcept {
  std::swap(top_, other.top_);
  std::swap(size_, other.size_);
}

template <typename T>
void stack<T>::destroyStack() {
  while (top_ != nullptr) {
    pop();
  }
}

template <typename T>
template <typename... Args>
void stack<T>::insert_many_front(Args &&...args) {
  for (auto elem : {std::forward<Args>(args)...}) {
    push(elem);
  }
}