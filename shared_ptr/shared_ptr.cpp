#include <iostream>
#include "shared_ptr.h"

namespace spec {

template <typename T>
constexpr shared_ptr<T>::shared_ptr()
noexcept : _ptr{}, _counter{new long{}} {}

template <typename T>
shared_ptr<T>::shared_ptr(typename shared_ptr<T>::pointer ptr)
: _ptr{ptr}, _counter{new long{1}} {}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>& oth)
noexcept : _ptr{oth._ptr}, _counter{oth._counter} {
  ++(*_counter);
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T>&& oth)
noexcept : _ptr{oth._ptr}, _counter{oth._counter} {
  oth._ptr = nullptr;
  oth._counter = nullptr;
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
  if (_ptr == nullptr) {
    return;
  }
  if (*_counter == 1) {
    delete _ptr;
    delete _counter;
  }
  else {
    --(*_counter);
  }
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& rhs) noexcept {
  if (&rhs == this) {
    return *this;
  }
  this->~shared_ptr();
  _ptr = rhs._ptr;
  _counter = rhs._counter;
  ++(*_counter);
  return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& rhs) noexcept {
  this->~shared_ptr();
  _ptr = rhs._ptr;
  _counter = rhs._counter;
  rhs._ptr = nullptr;
  rhs._counter = nullptr;
  return *this;
}

template <typename T>
void shared_ptr<T>::reset() noexcept {
  this->~shared_ptr();
  _ptr = nullptr;
  _counter = nullptr;
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr<T>& oth) noexcept {
  std::swap(_ptr, oth._ptr);
  std::swap(_counter, oth._counter);
}

template <typename T>
typename shared_ptr<T>::pointer shared_ptr<T>::get() const noexcept {
  return _ptr;
}

template <typename T>
typename shared_ptr<T>::element_type& shared_ptr<T>::operator*() const noexcept {
  return *_ptr;
}

template <typename T>
typename shared_ptr<T>::pointer shared_ptr<T>::operator->() const noexcept {
  return _ptr;
}

template <typename T>
long shared_ptr<T>::use_count() const noexcept {
  return *_counter;
}

template <typename T>
bool shared_ptr<T>::unique() const noexcept {
  return (*_counter == 1);
}

template <typename T>
shared_ptr<T>::operator bool() const noexcept {
  return (_ptr != nullptr);
}

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args... args) {
  auto ptr = new T(args...);
  shared_ptr<T> shared(ptr);
  return shared;
}

} // spec
