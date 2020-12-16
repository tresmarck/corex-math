#include <cassert>

#include <corex/utils.hpp>
#include <corex/math/algebra.hpp>

namespace cx
{
  int factorial(int n)
  {
    int total = 1;
    for (; n > 1; n--) {
      total *= n;
    }

    return total;
  }

  int pyModInt(int x, int divisor)
  {
    // From: https://stackoverflow.com/a/44197900/1116098
    return (divisor + (x % divisor)) % divisor;
  }

  int pow(int base, int exponent)
  {
    assert(exponent >= 0);

    // Note that std::pow() is slow. So, we're using a custom implementation
    // of a basic pow() for integers.
    if (exponent == 0) {
      return 1;
    } else if (base == 0) {
      return 0;
    } else {
      int result = 1;
      for (int i = 0; i < exponent; i++) {
        result *= base;
      }

      return result;
    }
  }

  float pow(float base, int exponent)
  {
    assert(exponent >= 0);

    // Note that std::pow() is slow. So, we're using a custom implementation
    // of a basic pow() for integers.
    if (exponent == 0) {
      return 1.f;
    } else if (floatEquals(base, 0.f)) {
      return 0.f;
    } else {
      double result = 1; // Let's not lose precision during computation.
      for (int i = 0; i < exponent; i++) {
        result *= static_cast<double>(base);
      }

      return static_cast<float>(result);
    }
  }
}
