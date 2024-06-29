using namespace s21;

template <typename T>
typename list<T>::reference list<T>::ListIterator::operator*() noexcept {
  return ptr_->data_;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator++(int) noexcept {
  ListIterator it = *this;
  ptr_ = ptr_->next_;
  return it;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator--(int) noexcept {
  ListIterator it = *this;
  ptr_ = ptr_->prev_;
  return it;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator++() noexcept {
  ptr_ = ptr_->next_;
  return *this;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator--() noexcept {
  ptr_ = ptr_->prev_;
  return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator+(
    size_type value) noexcept {
  Node_* temp = ptr_;
  for (size_type i = 0; i < value; i++) {
    temp = temp->next_;
  }
  ListIterator res(temp);
  return res;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator-(
    size_type value) noexcept {
  Node_* temp = ptr_;
  for (size_type i = 0; i < value; i++) {
    temp = temp->prev_;
  }
  ListIterator res(temp);
  return res;
}

template <typename T>
bool list<T>::ListIterator::operator==(ListIterator other) noexcept {
  return this->ptr_ == other.ptr_;
}

template <typename T>
bool list<T>::ListIterator::operator!=(ListIterator other) noexcept {
  return this->ptr_ != other.ptr_;
}
