#ifndef COREX_MATH_DS_VEC2_HPP
#define COREX_MATH_DS_VEC2_HPP

namespace cx
{
  struct Vec2
  {
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);
    Vec2(const Vec2& rhs);
  };

  Vec2 operator+(const Vec2& p, const Vec2& q);
  Vec2 operator-(const Vec2& p, const Vec2& q);
  Vec2 operator*(const Vec2& p, const int& a);
  Vec2 operator*(const Vec2& p, const float& a);
  Vec2 operator*(const int& a, const Vec2& p);
  Vec2 operator*(const float& a, const Vec2& p);
  Vec2 operator/(const Vec2& p, const int& a);
  Vec2 operator/(const Vec2& p, const float& a);
}

#endif