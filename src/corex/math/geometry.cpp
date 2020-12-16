#include <cmath>

#include <corex/utils.hpp>
#include <corex/math/algebra.hpp>
#include <corex/math/constants.hpp>
#include <corex/math/ds.hpp>
#include <corex/math/geometry.hpp>
#include <corex/math/linear_algebra.hpp>
#include <corex/math/utils.hpp>

namespace cx
{
  float degreesToRadians(float degrees)
  {
    return static_cast<float>(degrees * (pi / 180.0));
  }

  float radiansToDegrees(float radians)
  {
    return static_cast<float>(radians * (180.0 / pi));
  }

  float distance2D(const Point& start, const Point& end)
  {
    return sqrt(cx::pow(end.x - start.x, 2) + cx::pow(end.y - start.y, 2));
  }

  float lineLength(const Line& line)
  {
    return distance2D(line.start, line.end);
  }

  float signedDistPointToInfLine(const Point& point, const Line& line)
  {
    return setDecPlaces(dotProduct(lineNormalVector(line), (point - line.end)),
                        4);
  }

  Polygon<4> rotateRectangle(float centerX, float centerY, float width,
                             float height, float angle)
  {
    // NOTE: Angle is expected to be in degrees.
    Point topLeftPt = Point{centerX - (width / 2.f), centerY - (height / 2.f)};
    Point topRightPt = Point{topLeftPt.x + width, topLeftPt.y};
    Point bottomLeftPt = Point{topLeftPt.x, topLeftPt.y + height};
    Point bottomRightPt = Point{topLeftPt.x + width, topLeftPt.y + height};

    // Center X and Y are effectively the distance of the rectangle from
    // its center to the origin
    Point transTopLeftPt = translatePoint(topLeftPt, -centerX, -centerY);
    Point transTopRightPt = translatePoint(topRightPt, -centerX, -centerY);
    Point transBottomLeftPt = translatePoint(bottomLeftPt, -centerX, -centerY);
    Point transBottomRightPt = translatePoint(bottomRightPt,
                                              -centerX,
                                              -centerY);

    Point rotatedTopLeftPt = rotatePoint(transTopLeftPt, angle);
    Point rotatedTopRightPt = rotatePoint(transTopRightPt, angle);
    Point rotatedBottomLeftPt = rotatePoint(transBottomLeftPt, angle);
    Point rotatedBottomRightPt = rotatePoint(transBottomRightPt, angle);

    return Polygon<4>{
        {
            // Re-translate point to position the point in the right position.
            translatePoint(rotatedTopLeftPt, centerX, centerY),
            translatePoint(rotatedTopRightPt, centerX, centerY),
            translatePoint(rotatedBottomRightPt, centerX, centerY),
            translatePoint(rotatedBottomLeftPt, centerX, centerY)
        }
    };
  }

  Polygon<4> rotateRectangle(const Rectangle& rect)
  {
    return rotateRectangle(rect.x, rect.y, rect.width, rect.height, rect.angle);
  }

  bool areTwoRectsIntersectingInAnAxis(const Rectangle& rect0,
                                       const Rectangle& rect1,
                                       const Vec2& axis)
  {
    Line projLine0 = projectRectToAnAxis(rect0, axis);
    Line projLine1 = projectRectToAnAxis(rect1, axis);

    // We need to find the line that merges both segments together (whether
    // or not they are intersecting). We could have used a loop here for
    // generalization, but we don't need to do so for now. So, no loops.
    // TODO: Optimize this so that we don't need to create possible lines
    //       and looping through them to find the longest one.
    Line possibleRectLine0 = Line{ projLine0.start, projLine0.end };
    Line possibleRectLine1 = Line{ projLine0.start, projLine1.start };
    Line possibleRectLine2 = Line{ projLine0.start, projLine1.end };
    Line possibleRectLine3 = Line{ projLine0.end, projLine1.start };
    Line possibleRectLine4 = Line{ projLine0.end, projLine1.end };
    Line possibleRectLine5 = Line{ projLine1.start, projLine1.end };

    Line projRectLine = longestLine({
      &possibleRectLine0,
      &possibleRectLine1,
      &possibleRectLine2,
      &possibleRectLine3,
      &possibleRectLine4,
      &possibleRectLine5
    });

    return floatLessEqual(lineLength(projRectLine),
                          lineLength(projLine0) + lineLength(projLine1));
  }

  bool areTwoRectsIntersecting(const Rectangle& rect0, const Rectangle& rect1)
  {
    // Oh, boy. Let's do some SAT (Separating Axis Theorem)!
    Vec2 axisX0 = rotateVec2(Vec2{1.f, 0.f}, rect0.angle);
    Vec2 axisY0 = rotateVec2(Vec2{0.f, 1.f}, rect0.angle);
    Vec2 axisX1 = rotateVec2(Vec2{1.f, 0.f}, rect1.angle);
    Vec2 axisY1 = rotateVec2(Vec2{0.f, 1.f}, rect1.angle);

    return areTwoRectsIntersectingInAnAxis(rect0, rect1, axisX0)
           && areTwoRectsIntersectingInAnAxis(rect0, rect1, axisY0)
           && areTwoRectsIntersectingInAnAxis(rect0, rect1, axisX1)
           && areTwoRectsIntersectingInAnAxis(rect0, rect1, axisY1);
  }

  ReturnValue<Point> intersectionOfTwoInfLines(const Line& line0,
                                               const Line& line1)
  {
    // We're using the vector form of a line equation since it's easier to
    // determine whether two lines are intersecting or not with such a form.
    Vec2 line0DirVec = lineDirectionVector(line0);
    Vec2 line1DirVec = lineDirectionVector(line1);

    if (floatEquals(dotProduct(line0DirVec, vec2Perp(line1DirVec)), 0.f)) {
      // The two lines are parallel, so no point of intersection.
      return ReturnValue<Point>{ Point{}, ReturnState::RETURN_FAIL };
    }

    // Note that the vector form equation of a line is defined as:
    //                   r(λ) = p + λd
    // where:
    //   p - position vector
    //   λ - a scalar value determining the point in a line
    //   d - direction vector
    Vec2 line0PosVec = line0.start; // A Point object is an alias for a Vec2.
    Vec2 line1PosVec = line1.start;

    float lambda = (
        dotProduct(line1PosVec - line0PosVec, vec2Perp(line1DirVec))
        / dotProduct(line0DirVec, vec2Perp(line1DirVec))
    );
    return ReturnValue<Point>{ line0PosVec + (lambda * line0DirVec),
                               ReturnState::RETURN_OK };
  }

  ReturnValue<Point> intersectionOfLineandInfLine(const Line& line,
                                                  const Line& infLine)
  {
    auto intersectionPt = intersectionOfTwoInfLines(line, infLine);
    if (intersectionPt.status == ReturnState::RETURN_FAIL) {
      return intersectionPt;
    }

    Point intersectPt = intersectionPt.value;

    // Previously, we used to check if the intersection point is on the line
    // segment. However, we are sure that the intersection point will lay on the
    // line segment if the segment is a line, because the intersection is where
    // two lines sharer the same point. This renders the check unnecessary. We
    // just need to make sure that the the point will fall on the line segment.
    // So, we removed the check.
    if (isFloatInclusiveBetween(line.start.x, intersectPt.x, line.end.x)
        && isFloatInclusiveBetween(line.start.y, intersectPt.y, line.end.y)) {
      return ReturnValue<Point>{ intersectPt, ReturnState::RETURN_OK };
    }

    return ReturnValue<Point>{ Point{}, ReturnState::RETURN_FAIL };
  }

  ReturnValue<Point> intersectionOfLineAndLine(const Line& line0,
                                               const Line& line1)
  {
    auto intersectionPt = intersectionOfTwoInfLines(line0, line1);
    if (intersectionPt.status == ReturnState::RETURN_FAIL) {
      return intersectionPt;
    }

    Point intersectPt = intersectionPt.value;

    // For an intersection point to exist between two line segments, the point
    // must within the two line segments.
    if (isFloatInclusiveBetween(line0.start.x, intersectPt.x, line0.end.x)
        && isFloatInclusiveBetween(line0.start.y, intersectPt.y, line0.end.y)
        && isFloatInclusiveBetween(line1.start.x, intersectPt.x, line1.end.x)
        && isFloatInclusiveBetween(line1.start.y, intersectPt.y, line1.end.y)) {
      return ReturnValue<Point>{ intersectPt, ReturnState::RETURN_OK };
    }

    return ReturnValue<Point>{ Point{}, ReturnState::RETURN_FAIL };
  }

  bool areTwoLinesIntersecting(const Line& line0, const Line& line1)
  {
    auto intersectionPt = intersectionOfLineAndLine(line0, line1);
    return intersectionPt.status == ReturnState::RETURN_OK;
  }

  NPolygon clippedPolygonFromTwoRects(const Rectangle& targetRect,
                                      const Rectangle& clippingRect)
  {
    // Heck, yeah! Let's do some Sutherland-Hodgman.
    auto targetRectPoly = convertRectangleToPolygon(targetRect);
    auto clippingEdges = convertPolygonToLines(
        convertRectangleToPolygon(clippingRect));

    eastl::vector<Point> clippedPolyVerts;
    for (Point& point : targetRectPoly.vertices) {
      clippedPolyVerts.push_back(point);
    }

    eastl::vector<Point> currTargetPoly;
    for (Line& clipEdge : clippingEdges) {
      currTargetPoly = clippedPolyVerts;
      clippedPolyVerts.clear();

      for (int i = 0; i < currTargetPoly.size(); i++) {
        Line targetLine = Line{
            currTargetPoly[i],
            currTargetPoly[(i + 1) % currTargetPoly.size()]
        };
        auto intersectionPt = intersectionOfLineandInfLine(targetLine,
                                                           clipEdge);
        if (floatLessEqual(signedDistPointToInfLine(targetLine.start, clipEdge),
                           0.f)) {
          // The start of the target line is inside the clip edge.
          clippedPolyVerts.push_back(targetLine.start);

          if (floatGreEqual(signedDistPointToInfLine(targetLine.end, clipEdge),
                            0.f)) {
            // There should be an intersection point here since the start
            // and end points of the target line are in opposite sides of the
            // clipping edge.
            if (intersectionPt.status == ReturnState::RETURN_OK) {
              clippedPolyVerts.push_back(intersectionPt.value);
            }
          }
        } else if (floatLessEqual(
            signedDistPointToInfLine(targetLine.end, clipEdge), 0.f)) {
          // The end of the target line is inside the clip edge.
          // There should be an intersection point here since the start
          // and end points of the target line are in opposite sides of the
          // clipping edge.
          if (intersectionPt.status == ReturnState::RETURN_OK) {
            clippedPolyVerts.push_back(intersectionPt.value);
          }
        }
      }
    }

    return NPolygon{ clippedPolyVerts };
  }

  Point getPolygonCentroid(const NPolygon& polygon)
  {
    // From "Calculating the area and centroid of a polygon" by Paul Bourke.
    // URL: http://paulbourke.net/geometry/polygonmesh/
    double polygonArea = getPolygonArea(polygon);
    auto& vertices = polygon.vertices;
    double centroidX = 0.0;
    double centroidY = 0.0;

    float determinant = corex::core::det3x3(vertices[0],
                                            vertices[1],
                                            vertices[2]);

    for (int i = 0; i < vertices.size(); i++) {
      // If the polygon is oriented counterclockwise when the origin is in the
      // center, then it is oriented clockwise when the origin is in the
      // top-left. We must iterate through the vertices from left to right.
      //
      // If the polygon is oriented clockwise when the origin is in the center,
      // then it is oriented counterclockwise when the origin is in the
      // top-left. We must iterate through the vertices from right to left.
      int currVertIndex = 0;
      int nextVertIndex = 0;
      if (corex::core::floatGreEqual(determinant, 0.f)) {
        // Polygon is oriented counterclockwise when the origin is in the
        // center.
        currVertIndex = i;
        nextVertIndex = pyModInt(currVertIndex + 1, vertices.size());
      } else {
        // Polygon is oriented clockwise when the origin is in the
        // center.
        currVertIndex = vertices.size() - (i + 1);
        nextVertIndex = pyModInt(currVertIndex - 1, vertices.size());
      }

      centroidX += (vertices[currVertIndex].x + vertices[nextVertIndex].x)
                   * ((vertices[currVertIndex].x * vertices[nextVertIndex].y)
                      - (vertices[nextVertIndex].x * vertices[currVertIndex].y));
      centroidY += (vertices[currVertIndex].y + vertices[nextVertIndex].y)
                   * ((vertices[currVertIndex].x * vertices[nextVertIndex].y)
                      - (vertices[nextVertIndex].x * vertices[currVertIndex].y));
    }

    double areaConstant = 1.0 / (6.0 * polygonArea);
    centroidX *= areaConstant;
    centroidY *= areaConstant;

    return Point{
        static_cast<float>(centroidX),
        static_cast<float>(centroidY)
    };
  }

  double getPolygonArea(const NPolygon& polygon)
  {
    // Let's use the Shoelace algorithm.
    double area = 0.f;
    auto& vertices = polygon.vertices;
    for (int i = 0; i < polygon.vertices.size(); i++) {
      // Our polygon vertices, whose container list is accessed from left to
      // right, are arranged in a clockwise manner in a coordinate system where
      // the origin is on the top left corner, like what we are using. However
      // when using an origin that is situated on the bottom left corner, the
      // polygon will be arranged in a counterclockwise manner. The Shoelace
      // Algorithm assumes that the origin is anchored on the bottom right
      // corner. As such, we can simply iterate through the list of vertices
      // from left to right.
      int nextIndex = (i + 1) % polygon.vertices.size();
      area +=
          (static_cast<double>(vertices[i].x)
           * static_cast<double>(vertices[nextIndex].y))
          - (static_cast<double>(vertices[nextIndex].x)
             * static_cast<double>(vertices[i].y));
    }

    return fabs(area) / 2.0;
  }

  bool isPointWithinNPolygon(const Point& point, const NPolygon& polygon)
  {
    // Code based from:
    //     https://wrf.ecse.rpi.edu/Research/Short_Notes/pnpoly.html
    // NOTE: I think the algorithm expects that the origin is situated in the
    //       bottom-left corner of the space. Since our vertices are stored with
    //       the assumption that the origin is situated in the top-left corner.
    //       from the perspective of the algorithm, the vertices are flipped
    //       vertically.
    bool isPointInside = false;
    for (int i = 0, j = polygon.vertices.size() - 1;
         i < polygon.vertices.size();
         j = i++) {
      Line polyLine = Line{ polygon.vertices[i], polygon.vertices[j] };
      if (((polyLine.start.y > point.y) != (polyLine.end.y > point.y))
          && (point.x < ((polyLine.end.x - polyLine.start.x)
                         * (point.y - polyLine.start.y)
                         / (polyLine.end.y - polyLine.start.y)
                         + polyLine.start.x))) {
        isPointInside = !isPointInside;
      }
    }

    return isPointInside;
  }

  bool isRectWithinNPolygon(const Rectangle& rect, const NPolygon& polygon)
  {
    auto rectPoly = convertRectangleToPolygon(rect);

    for (int i = 0; i < polygon.vertices.size(); i++) {
      Line boundaryLine = Line{
          polygon.vertices[i],
          polygon.vertices[(i + 1) % polygon.vertices.size()]
      };

      for (int j = 0; j < rectPoly.vertices.size(); j++) {
        Line rectLine = Line{
            rectPoly.vertices[j],
            rectPoly.vertices[(j + 1) % rectPoly.vertices.size()]
        };

        if (areTwoLinesIntersecting(boundaryLine, rectLine)
            && (floatGreater(signedDistPointToInfLine(rectLine.start,
                                                      boundaryLine),
                             0.f)
                || floatGreater(signedDistPointToInfLine(rectLine.end,
                                                         boundaryLine),
                                0.f))) {
          return false;
        }
      }
    }

    return isPointWithinNPolygon(rectPoly.vertices[0], polygon);
  }

  bool isRectIntersectingNPolygon(const Rectangle& rect,
                                  const NPolygon& polygon)
  {
    // NOTE: "A subset of a set is equal to its intersections."
    // Source: https://www.quora.com
    //                /Set-Theory-Is-a-subset-a-type-of-intersection
    //                /answer/Vinay-Madhusudanan
    auto rectPoly = convertRectangleToPolygon(rect);

    for (int i = 0; i < polygon.vertices.size(); i++) {
      Line boundaryLine = Line{
          polygon.vertices[i],
          polygon.vertices[(i + 1) % polygon.vertices.size()]
      };

      for (int j = 0; j < rectPoly.vertices.size(); j++) {
        Line rectLine = Line{
            rectPoly.vertices[j],
            rectPoly.vertices[(j + 1) % rectPoly.vertices.size()]
        };

        if (areTwoLinesIntersecting(boundaryLine, rectLine)) {
          return true;
        }
      }
    }

    return isPointWithinNPolygon(rectPoly.vertices[0], polygon);
  }
}
