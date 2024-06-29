using namespace s21;

template <typename T, std::size_t N>
array<T, N>::array() : size_(N) {}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const& items) : array() {
  for (size_type i = 0; i < items.size(); ++i) {
    arr_[i] = *(items.begin() + i);
  }
}

template <typename T, std::size_t N>
array<T, N>::array(const array& other) {
  for (size_type i = 0; i < size_; ++i) {
    arr_[i] = other.arr_[i];
  }
}

template <typename T, std::size_t N>
array<T, N>::array(array&& other) noexcept : array(other) {}

template <typename T, std::size_t N>
array<T, N>::~array() {}

template <typename T, std::size_t N>
array<T, N>& array<T, N>::operator=(array<T, N>&& other) noexcept {
  if (this != &other) {
    for (size_type i = 0; i < size_; ++i) {
      arr_[i] = other.arr_[i];
    }
  }
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= size_ || size_ == 0) {
    throw std::out_of_range("Index out range");
  }
  return arr_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return *(arr_ + pos);
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  return arr_[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() {
  return arr_[size_ - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return arr_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return arr_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return arr_ + size_;
}

template <typename T, std::size_t N>
bool array<T, N>::empty() {
  return size_ == 0;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return size_;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return size();
}

template <typename T, std::size_t N>
void array<T, N>::swap(array& other) {
  std::swap(arr_, other.arr_);
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < size_; i++) {
    arr_[i] = value;
  }
}