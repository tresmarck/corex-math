#ifndef COREX_MATH_LINEAR_ALGEBRA_HPP
#define COREX_MATH_LINEAR_ALGEBRA_HPP

namespace cx
{
  float det3x3(const Vec2& v0, const Vec2& v1, const Vec2& v2);
  float vec2Magnitude(const Vec2& p);
  float vec2Angle(const Vec2& p);
  float dotProduct(const Vec2& p, const Vec2& q);
  float crossProduct(const Vec2& p, const Vec2& q);
  Vec2 rotateVec2(const Vec2& p, float angle);
  Vec2 projectVec2(const Vec2& p, const Vec2& q);
  Vec2 vec2Perp(const Vec2& p);
  Vec2 translateVec2(const Vec2& vec, float deltaX, float deltaY);
  Vec2 minVec2Magnitude(const eastl::vector<Vec2*> vectors);
  Vec2 maxVec2Magnitude(const eastl::vector<Vec2*> vectors);
  Vec2 unitVector(const Vec2& vec);
  Vec2 lineToVec(const Line& line);
  Vec2 lineDirectionVector(const Line& line);
  Vec2 lineNormalVector(const Line& line);
  Line projectRectToAnAxis(const Rectangle& rect, const Vec2& axis);

  template <typename... Args>
  inline constexpr auto rotatePoint(Args&&... args)
  -> decltype(rotateVec2(eastl::forward<Args>(args)...))
  {
    return rotateVec2(eastl::forward<Args>(args)...);
  }

  template <typename... Args>
  inline constexpr auto projectPoint(Args&&... args)
  -> decltype(projectVec2(eastl::forward<Args>(args)...))
  {
    return projectVec2(eastl::forward<Args>(args)...);
  }

  template <typename... Args>
  inline constexpr auto translatePoint(Args&&... args)
  -> decltype(translateVec2(eastl::forward<Args>(args)...))
  {
    return translateVec2(eastl::forward<Args>(args)...);
  }
}

#endif
