/*
Copyright (c) 2017 Erik Rigtorp <erik@rigtorp.se>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#pragma once

#include <array>
#include <type_traits>

namespace rigtorp {

template <class Key, class T, std::size_t N> class RingMap {
  static_assert(std::is_integral<Key>::value, "Key must be integral");
  static_assert(std::is_default_constructible<T>::value,
                "T must be default constructible");

public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<Key, T>;
  using size_type = std::size_t;
  using reference = value_type &;
  using const_reference = const value_type &;

  explicit RingMap() = default;

  void clear() noexcept(std::is_nothrow_assignable<T &, T>::value) {
    data_.fill({});
  }

  reference at(const Key key) {
    auto &slot = data_[key % size()];
    if (slot.first != key) {
      throw std::out_of_range("");
    }
    return slot;
  }

  const_reference at(const Key key) const {
    const auto &slot = data_[key % size()];
    if (slot.first != key) {
      throw std::out_of_range("");
    }
    return slot;
  }

  reference operator[](const Key key) noexcept {
    auto &slot = data_[key % size()];
    slot.first = key;
    return slot;
  }

  size_type count(const Key key) const noexcept {
    const auto &slot = data_[key % size()];
    return slot.first == key;
  }

  constexpr size_type size() const noexcept { return N; }

private:
  std::array<value_type, N> data_ = {};
};
}