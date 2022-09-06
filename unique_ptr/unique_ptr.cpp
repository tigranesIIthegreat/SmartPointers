#include "unique_ptr.h"
#include <iostream>

namespace spec {

template <typename T>
constexpr unique_ptr<T>::unique_ptr() noexcept : _ptr{} {}

template <typename T>
unique_ptr<T>::unique_ptr(typename unique_ptr<T>:: pointer ptr) noexcept : _ptr{ptr} {}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr<T>&& oth) noexcept {
  _ptr = oth._ptr;
  oth._ptr = nullptr;
}

template <typename T>
unique_ptr<T>::~unique_ptr() {
  if (_ptr) {
    delete _ptr;
  }
  _ptr = nullptr;
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& oth) noexcept {
  if (_ptr) {
    delete _ptr;
  }
  _ptr = oth._ptr;
  oth._ptr = nullptr;
  return *this;
}

template <typename T>
typename unique_ptr<T>::pointer unique_ptr<T>::release() noexcept {
  auto result = _ptr;
  _ptr = nullptr;
  return result;
}

template <typename T>
void unique_ptr<T>::reset(typename unique_ptr<T>::pointer ptr) noexcept {
  if (_ptr) {
    delete _ptr;
  }
  _ptr = ptr;
}

template <typename T>
void unique_ptr<T>::swap(unique_ptr<T>& oth) noexcept {
  std::swap(_ptr, oth._ptr);
}

template <typename T>
typename unique_ptr<T>::pointer unique_ptr<T>::get() const noexcept {
  return _ptr;
}

template <typename T>
unique_ptr<T>::operator bool() const noexcept {
  return _ptr != nullptr;
}

template <typename T>
typename unique_ptr<T>::element_type& unique_ptr<T>::operator*() const {
  return *_ptr;
}

template <typename T>
typename unique_ptr<T>::pointer unique_ptr<T>::operator->() const noexcept {
  return _ptr;
}

template <typename T, typename... Args> 
unique_ptr<T> make_unique(Args... args) {
  auto ptr = new T(args...);
  unique_ptr<T> unique(ptr);
  return unique;
}

} // spec
