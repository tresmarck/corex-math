#include <corex/math/ds/Vec2.hpp>

namespace cx
{
  Vec2::Vec2()
    : x()
    , y() {}

  Vec2::Vec2(float x, float y)
    : x(x)
    , y(y) {}

  Vec2::Vec2(const Vec2& rhs)
    : x(rhs.x)
    , y(rhs.y) {}

  Vec2 operator+(const Vec2& p, const Vec2& q)
  {
    return Vec2{ p.x + q.x, p.y + q.y };
  }

  Vec2 operator-(const Vec2& p, const Vec2& q)
  {
    return Vec2{ p.x - q.x, p.y - q.y };
  }

  Vec2 operator*(const Vec2& p, const int& a)
  {
    return Vec2{ p.x * a, p.y * a };
  }

  Vec2 operator*(const Vec2& p, const float& a)
  {
    return Vec2{ p.x * a, p.y * a };
  }

  Vec2 operator*(const int& a, const Vec2& p)
  {
    return Vec2{ a * p.x, a * p.y };
  }

  Vec2 operator*(const float& a, const Vec2& p)
  {
    return Vec2{ a * p.x, a * p.y };
  }

  Vec2 operator/(const Vec2& p, const int& a)
  {
    return Vec2{ p.x / a, p.y / a };
  }

  Vec2 operator/(const Vec2& p, const float& a)
  {
    return Vec2{ p.x / a, p.y / a };
  }
}