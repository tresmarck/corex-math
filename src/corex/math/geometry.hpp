#ifndef COREX_MATH_GEOMETRY_HPP
#define COREX_MATH_GEOMETRY_HPP

#include <corex/math/ds.hpp>
#include <corex/utils.hpp>

namespace cx
{
  float degreesToRadians(float degrees);
  float radiansToDegrees(float radians);
  float distance2D(const Point& start, const Point& end);
  float lineLength(const Line& line);

  float signedDistPointToInfLine(const Point& point, const Line& line);
  Polygon<4> rotateRectangle(float centerX, float centerY, float width,
                             float height, float angle);
  Polygon<4> rotateRectangle(const Rectangle& rect);
  bool areTwoRectsIntersectingInAnAxis(const Rectangle& rect0,
                                       const Rectangle& rect1,
                                       const Vec2& axis);
  bool areTwoRectsIntersecting(const Rectangle& rect0, const Rectangle& rect1);
  ReturnValue<Point> intersectionOfTwoInfLines(const Line& line0,
                                               const Line& line1);
  ReturnValue<Point> intersectionOfLineandInfLine(const Line& line,
                                                  const Line& infLine);
  ReturnValue<Point> intersectionOfLineAndLine(const Line& line0,
                                               const Line& line1);
  bool areTwoLinesIntersecting(const Line& line0, const Line& line1);
  NPolygon clippedPolygonFromTwoRects(const Rectangle& targetRect,
                                      const Rectangle& clippingRect);
  Point getPolygonCentroid(const NPolygon& polygon);
  double getPolygonArea(const NPolygon& polygon);
  bool isPointWithinNPolygon(const Point& point, const NPolygon& polygon);
  bool isRectWithinNPolygon(const Rectangle& rect, const NPolygon& polygon);
  bool isRectIntersectingNPolygon(const Rectangle& rect,
                                  const NPolygon& polygon);
}

#endif
