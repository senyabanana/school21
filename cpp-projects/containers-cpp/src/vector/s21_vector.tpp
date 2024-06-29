using namespace s21;

template <typename T>
vector<T>::vector() : arr_(nullptr), size_(0), capacity_(0) {}

template <typename T>
vector<T>::vector(size_type n)
    : arr_(new value_type[n]), size_(n), capacity_(n) {
  if (!arr_) {
    throw std::bad_alloc();
  }
  for (size_type i = 0; i < n; i++) {
    arr_[i] = T();
  }
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const& items)
    : vector(items.size()) {
  for (size_type i = 0; i < size_; i++) {
    arr_[i] = *(items.begin() + i);
  }
}

template <typename T>
vector<T>::vector(const vector& other) : vector(other.size_) {
  for (size_type i = 0; i < size_; i++) {
    arr_[i] = other.arr_[i];
  }
}

template <typename T>
vector<T>::vector(vector&& other)
    : arr_(other.arr_), size_(other.size_), capacity_(other.capacity_) {
  other.arr_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <typename T>
vector<T>::~vector() {
  delete[] arr_;
  arr_ = nullptr;
}

template <typename T>
vector<T>& vector<T>::operator=(vector<T>&& other) noexcept {
  if (this != &other) {
    delete[] arr_;
    arr_ = other.arr_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.arr_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out range");
  }
  return arr_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return *(arr_ + pos);
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  return arr_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  return arr_[size_ - 1];
}

template <typename T>
typename vector<T>::iterator vector<T>::data() noexcept {
  return arr_;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() noexcept {
  return arr_;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() noexcept {
  return arr_ + size_;
}

template <typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(T) / 2;
}

template <typename T>
void vector<T>::reserve(size_type new_cap) {
  if (new_cap > max_size()) {
    throw std::length_error("Can't allocate memory of this size");
  }
  if (new_cap > capacity_) {
    T* new_array = new T[new_cap];
    for (size_type i = 0; i < size_; i++) {
      new_array[i] = std::move(arr_[i]);
    }
    delete[] arr_;
    arr_ = new_array;
    capacity_ = new_cap;
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    T* new_array = new T[size_];
    std::copy(arr_, arr_ + size_, new_array);
    delete[] arr_;
    arr_ = new_array;
    capacity_ = size_;
  }
}

template <typename T>
void vector<T>::clear() {
  delete[] arr_;
  arr_ = nullptr;
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - begin();
  if (size_ >= capacity_) {
    size_type new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    reallocate(new_capacity);
  }
  pos = begin() + index;
  for (size_type i = size_; i > index; --i) {
    arr_[i] = std::move(arr_[i - 1]);
  }
  arr_[index] = value;
  ++size_;
  return arr_ + index;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  if (pos >= begin() && pos < end()) {
    size_type index = pos - begin();
    for (size_type i = index; i < size_ - 1; ++i) {
      arr_[i] = std::move(arr_[i + 1]);
    }
    --size_;
  }
}

template <typename T>
void vector<T>::push_back(vector::const_reference value) {
  if (size_ == capacity_) {
    size_type new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    reallocate(new_capacity);
  }
  arr_[size_] = value;
  ++size_;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    --size_;
  }
}

template <typename T>
void vector<T>::swap(vector<T>& other) {
  std::swap(arr_, other.arr_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
void vector<T>::reallocate(size_type new_cap) {
  T* new_array = new T[new_cap];
  for (size_type i = 0; i < size_; i++) {
    new_array[i] = std::move(arr_[i]);
  }
  delete[] arr_;
  arr_ = new_array;
  capacity_ = new_cap;
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  s21::vector<value_type> temp{args...};
  iterator position = const_cast<iterator>(pos);
  for (size_t i = 0; i < temp.size(); i++) {
    position = insert(position, temp[i]) + 1;
  }
  return position;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  insert_many(this->end(), args...);
}