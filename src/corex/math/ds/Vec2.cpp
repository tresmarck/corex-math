#include <corex/math/utils.hpp>
#include <corex/math/ds/Vec2.hpp>

namespace cx
{
  Vec2::Vec2()
    : x()
    , y() {}

  Vec2::Vec2(float x, float y)
    : x(x)
    , y(y) {}

  Vec2::Vec2(const Vec2& rhs) = default;

  Vec2 operator+(const Vec2& p, const Vec2& q)
  {
    return Vec2{ setDecPlaces(p.x + q.x, 6), setDecPlaces(p.y + q.y, 6) };
  }

  Vec2 operator-(const Vec2& p, const Vec2& q)
  {
    return Vec2{ setDecPlaces(p.x - q.x, 6), setDecPlaces(p.y - q.y, 6) };
  }

  Vec2 operator*(const Vec2& p, const int& a)
  {
    return Vec2{
      setDecPlaces(p.x * static_cast<float>(a), 6),
      setDecPlaces(p.y * static_cast<float>(a), 6)
    };
  }

  Vec2 operator*(const Vec2& p, const float& a)
  {
    return Vec2{ setDecPlaces(p.x * a, 6), setDecPlaces(p.y * a, 6) };
  }

  Vec2 operator*(const int& a, const Vec2& p)
  {
    return Vec2{
      setDecPlaces(static_cast<float>(a) * p.x, 6),
      setDecPlaces(static_cast<float>(a) * p.y, 6)
    };
  }

  Vec2 operator*(const float& a, const Vec2& p)
  {
    return Vec2{
      setDecPlaces(a * p.x, 6),
      setDecPlaces(a * p.y, 6)
    };
  }

  Vec2 operator/(const Vec2& p, const int& a)
  {
    return Vec2{
      setDecPlaces(p.x / static_cast<float>(a), 6),
      setDecPlaces(p.y / static_cast<float>(a), 6)
    };
  }

  Vec2 operator/(const Vec2& p, const float& a)
  {
    return Vec2{ setDecPlaces(p.x / a, 6), setDecPlaces(p.y / a, 6) };
  }
}