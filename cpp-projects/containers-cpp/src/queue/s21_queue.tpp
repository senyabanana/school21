using namespace s21;

template <typename T>
queue<T>::queue() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items) noexcept
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (value_type i : items) {
    push(i);
  }
}

template <typename T>
queue<T>::queue(const queue &other) : head_(nullptr), tail_(nullptr), size_(0) {
  *this = other;
}

template <typename T>
queue<T>::queue(queue &&other) noexcept
    : head_(nullptr), tail_(nullptr), size_() {
  *this = std::move(other);
}

template <typename T>
queue<T>::~queue() {
  destroyQueue();
}

template <typename T>
queue<T> &queue<T>::operator=(queue<T> &&other) noexcept {
  if (this != &other) {
    destroyQueue();
    head_ = std::move(other.head_);
    tail_ = std::move(other.tail_);
    size_ = std::move(other.size_);
  }
  return *this;
}

template <typename T>
typename queue<T>::const_reference queue<T>::front() const {
  if (head_ == nullptr) {
    throw std::logic_error("queue is empty");
  }
  return head_->data_;
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() const {
  if (tail_ == nullptr) {
    throw std::logic_error("queue is empty");
  }
  return tail_->data_;
}

template <typename T>
bool queue<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
typename queue<T>::size_type queue<T>::size() const noexcept {
  return size_;
}

template <typename T>
void queue<T>::push(const_reference value) noexcept {
  Node_ *new_node = new Node_(value);
  if (tail_ == nullptr) {
    tail_ = new_node;
    head_ = new_node;
  } else {
    tail_->next_ = new_node;
    tail_ = new_node;
  }
  size_++;
}

template <typename T>
void queue<T>::pop() {
  if (head_ == nullptr) {
    throw std::logic_error("queue is empty");
  }
  Node_ *prev_node = head_->next_;
  delete head_;
  head_ = prev_node;
  size_--;
}

template <typename T>
void queue<T>::swap(queue<T> &other) noexcept {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename T>
void queue<T>::destroyQueue() {
  while (head_ != nullptr) {
    pop();
  }
  tail_ = nullptr;
}

template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args &&...args) {
  for (auto elem : {std::forward<Args>(args)...}) {
    push(elem);
  }
}