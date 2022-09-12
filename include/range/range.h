#ifndef RANGE_H
#define RANGE_H

namespace range {
// todo Let the user specify and open, half-open, or closed range.
// todo Let the user specify the less comparison function.
template <typename T> struct range {
  using value_type = T;
  value_type minimum;
  value_type maximum;
};

template <typename T>
[[nodiscard]] constexpr auto in(const T &value,
                                const range<T> &bounds) noexcept {
  return bounds.minimum <= value && value <= bounds.maximum;
}

template <typename T>
[[nodiscard]] constexpr auto out(const T &value,
                                 const range<T> &bounds) noexcept {
  return !in(value, bounds);
}

template <typename T>
[[nodiscard]] constexpr auto operator<(const T &value,
                                       const range<T> &bounds) noexcept {
  return value < bounds.minimum;
}

template <typename T>
[[nodiscard]] constexpr auto operator>(const T &value,
                                       const range<T> &bounds) noexcept {
  return value > bounds.maximum;
}
} // namespace range
#endif
