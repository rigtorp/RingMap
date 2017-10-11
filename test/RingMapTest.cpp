#include <cassert>
#include <rigtorp/RingMap.h>

#define THROWS(expr)                                                           \
  [&] {                                                                        \
    try {                                                                      \
      expr;                                                                    \
    } catch (...) {                                                            \
      return true;                                                             \
    }                                                                          \
    return false;                                                              \
  }()

int main() {
  using namespace rigtorp;

  RingMap<int, int, 16> rm;
  assert(!THROWS(rm.at(0)));
  assert(rm.count(0));
  for (int i = 1; i < 256; ++i) {
    assert(THROWS(rm.at(i)));
    assert(!rm.count(i));
  }
  rm[123].second = 999;
  for (int i = 1; i < 123; ++i) {
    assert(THROWS(rm.at(i)));
    assert(!rm.count(i));
  }
  assert(!THROWS(rm.at(123)));
  assert(rm.count(123));
  assert(rm.at(123).first == 123);
  assert(rm.at(123).second == 999);
  for (int i = 124; i < 1234; ++i) {
    assert(THROWS(rm.at(i)));
    assert(!rm.count(i));
  }
  rm[123 % rm.size() + 20 * rm.size()].second = 9999;
  assert(THROWS(rm.at(123)));
  assert(!rm.count(123));
  assert(!THROWS(rm.at(123 % rm.size() + 20 * rm.size())));
  assert(rm.count(123 % rm.size() + 20 * rm.size()));

  return 0;
}
