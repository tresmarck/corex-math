#include <cmath>

#include <corex/utils.hpp>
#include <corex/math/ds.hpp>
#include <corex/math/geometry.hpp>
#include <corex/math/linear_algebra.hpp>
#include <corex/math/utils.hpp>

namespace cx
{
  float det3x3(const Vec2& v0, const Vec2& v1, const Vec2& v2)
  {
    return ((v1.x * v2.y) + (v0.x * v1.y) + (v0.y * v2.x))
           - ((v0.y * v1.x) + (v1.y * v2.x) + (v0.x * v2.y));
  }

  float vec2Magnitude(const Vec2& p)
  {
    return distance2D(Vec2{0.f, 0.f}, p);
  }

  float vec2Angle(const Vec2& p)
  {
    // Based on: https://stackoverflow.com/a/48227232/1116098
    // Returns the angle in degrees. Note also that we are using the
    // standard Cartesian coordinate plane, not the window space Cartesian
    // coordinate plane where the origin is on the top-left.
    // Let's tackle the special cases first.
    if (floatEquals(p.x, 0.f)) {
      return floatGreEqual(p.y, 0.f) ? 90.f
                                     : floatEquals(p.y, 0.f) ? 0.f
                                                             : 270.f;
    } else if (floatEquals(p.y, 0.f)) {
      return floatGreEqual(p.x, 0.f) ? 0
                                     : 180.f;
    }

    float rotDelta = radiansToDegrees(
        std::atanf(static_cast<float>(p.y / p.x)));
    if (floatLessThan(p.x, 0.f) && floatGreater(p.y, 0.f)) {
      // Quadrant II
      return 90 + rotDelta;
    } else if (floatLessThan(p.x, 0.f) && floatLessThan(p.y, 0.f)) {
      // Quadrant III
      return 180 + rotDelta;
    } else if (floatGreater(p.x, 0.f) && floatLessThan(p.y, 0.f)) {
      return 270 + rotDelta;
    } else {
      // Quadrant I
      return rotDelta;
    }
  }

  float dotProduct(const Vec2& p, const Vec2& q)
  {
    return (p.x * q.x) + (p.y * q.y);
  }

  float crossProduct(const Vec2& p, const Vec2& q)
  {
    return (p.x * p.y) - (p.y * q.x);
  }

  Vec2 rotateVec2(const Vec2& p, float angle)
  {
    // The angle parameter is expected to be in degrees. And we subtract the
    // angle by 360 so that we can rotate the point counterclockwise, which is
    // the rotation direction we usually expect,
    float angleRadians = degreesToRadians(angle);
    return Vec2{
        setDecPlaces(
            (p.x * std::cos(angleRadians)) - (p.y * std::sin(angleRadians)),
            6),
        setDecPlaces(
            (p.x * std::sin(angleRadians)) + (p.y * std::cos(angleRadians)),
            6)
    };
  }

  Vec2 projectVec2(const Vec2& p, const Vec2& q)
  {
    return static_cast<float>(dotProduct(p, q) / pow(vec2Magnitude(q), 2)) * q;
  }

  Vec2 vec2Perp(const Vec2& p)
  {
    // Vectors are arranged in a clockwise direction. This means that their
    // perpendiculars must be rotated counterclockwise. However, since the
    // origin is at the top left corner, rather than the bottom left, positive
    // angles will be rotated clockwise. As such, we have to use negative angles
    // to rotate the vectors counterclockwise to get their correct perpendicular
    // vectors.
    // TODO: Change this so that the origin is at the bottom left corner, since
    //       that's the most intuitive way. The math library must not worry
    //       about the coordinate system being used by top-level systems like
    //       the windowing system.
    return rotateVec2(p, -90.f);
  }

  Vec2 translateVec2(const Vec2& vec, float deltaX, float deltaY)
  {
    return Vec2{vec.x + deltaX, vec.y + deltaY};
  }

  Vec2 minVec2Magnitude(const eastl::vector<Vec2*> vectors)
  {
    // We don't want copies and references can't hold null objects.
    Vec2* minVec = nullptr;
    bool isFirstElement = true;
    for (Vec2* vec : vectors) {
      if (isFirstElement
          || floatLessThan(vec2Magnitude(*vec), vec2Magnitude(*minVec))) {
        // Let's utilize boolean short-circuit.
        isFirstElement = false;
        minVec = vec;
      }
    }

    return *minVec;
  }

  Vec2 maxVec2Magnitude(const eastl::vector<Vec2*> vectors)
  {
    // We don't want copies and references can't hold null objects.
    Vec2* maxVec = nullptr;
    bool isFirstElement = true;
    for (Vec2* vec : vectors) {
      if (isFirstElement
          || floatGreater(vec2Magnitude(*vec), vec2Magnitude(*maxVec))) {
        // Let's utilize boolean short-circuit.
        isFirstElement = false;
        maxVec = vec;
      }
    }

    return *maxVec;
  }

  Vec2 unitVector(const Vec2& vec)
  {
    return vec / vec2Magnitude(vec);
  }

  Vec2 lineToVec(const Line& line)
  {
    return Vec2{ line.end.x - line.start.x, line.end.y - line.start.y };
  }

  Vec2 lineDirectionVector(const Line& line)
  {
    return unitVector(lineToVec(line));
  }

  Vec2 lineNormalVector(const Line& line)
  {
    // The vertices of lines and polygons are arranged in a clockwise direction.
    // This means that the unit vectors representing the direction of lines must
    // be rotated counterclockwise. However, since the origin is at the top left
    // corner, rather than the bottom left, positive angles will be rotated
    // clockwise. As such, we have to use negative angles to rotate the unit
    // vectors counterclockwise to get the proper normal vectors of lines.
    return rotateVec2(lineDirectionVector(line), -90.f);
  }

  Line projectRectToAnAxis(const Rectangle& rect, const Vec2& axis)
  {
    auto rotatedRect = rotateRectangle(rect);
    Point topLeftPt = rotatedRect.vertices[0];
    Point topRightPt = rotatedRect.vertices[1];
    Point bottomLeftPt = rotatedRect.vertices[3];
    Point bottomRightPt = rotatedRect.vertices[2];
    Point projectedTopLeftPt = projectVec2(topLeftPt, axis);
    Point projectedTopRightPt = projectVec2(topRightPt, axis);
    Point projectedBottomLeftPt = projectVec2(bottomLeftPt, axis);
    Point projectedBottomRightPt = projectVec2(bottomRightPt, axis);

    Line possibleRectLine0{ projectedTopLeftPt, projectedTopRightPt };
    Line possibleRectLine1{ projectedTopLeftPt, projectedBottomLeftPt };
    Line possibleRectLine2{ projectedTopLeftPt, projectedBottomRightPt };
    Line possibleRectLine3{ projectedTopRightPt, projectedBottomLeftPt };
    Line possibleRectLine4{ projectedTopRightPt, projectedBottomRightPt };
    Line possibleRectLine5{ projectedBottomLeftPt, projectedBottomRightPt };

    return longestLine({
      &possibleRectLine0,
      &possibleRectLine1,
      &possibleRectLine2,
      &possibleRectLine3,
      &possibleRectLine4,
      &possibleRectLine5
    });
  }
}
