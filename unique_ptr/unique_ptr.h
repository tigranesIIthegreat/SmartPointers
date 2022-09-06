#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

namespace spec {

template <typename T>
class unique_ptr {
public:
  using pointer = T*;
  using element_type = T;

public:
  constexpr unique_ptr() noexcept;
  explicit unique_ptr(pointer) noexcept;
  unique_ptr(unique_ptr<T>&&) noexcept;
  ~unique_ptr();

public:
  unique_ptr& operator=(unique_ptr&&) noexcept;
  pointer release() noexcept;
  void reset(pointer) noexcept;
  void swap(unique_ptr&) noexcept;
  pointer get() const noexcept;
  explicit operator bool() const noexcept;
  element_type& operator*() const;
  pointer operator->() const noexcept;

private:
  pointer _ptr{};
};

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args... args);

} // spec


#endif // UNIQUE_PTR_H