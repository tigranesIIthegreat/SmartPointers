#ifndef SHARED_PTR_H
#define SHARED_PTR_H

namespace spec {

template <typename T>
class shared_ptr {
public:
  using element_type = T;
  using pointer = T*;

public:
  constexpr shared_ptr() noexcept;
  explicit shared_ptr(pointer);
  shared_ptr(const shared_ptr&) noexcept;
  shared_ptr(shared_ptr&&) noexcept;
  ~shared_ptr();

public:
  shared_ptr& operator=(const shared_ptr&) noexcept;
  shared_ptr& operator=(shared_ptr&&) noexcept;
  void reset() noexcept;
  void swap(shared_ptr&) noexcept;
  pointer get() const noexcept;
  element_type& operator*() const noexcept;
  pointer operator->() const noexcept;
  long use_count() const noexcept;
  bool unique() const noexcept;
  explicit operator bool() const noexcept;

private:
  pointer _ptr{};
  long* _counter{};
};

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args... atgs);

} // spec

#endif // SHARED_PTR_H