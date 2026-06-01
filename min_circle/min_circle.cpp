#include "min_circle.h"
#include <iostream>
#include <vector>

bool Point2D::operator==(const Point2D& other) const
{
    if (x == other.x && y == other.y)
    {
	    return true;
    }
    return false;
}

bool Point2D::operator!=(const Point2D& other) const 
{
    return !(*this == other);
}

bool Circle::isValid() const
{
    if (radius >= 0)
    {
	    return true;
    }
    return false;
}

bool Circle::contains(const Point2D& point) const
{
    if ((distance(center, point) <= radius) && isValid())
    {
	return true;
    }    
    return false;
}

bool Circle::contains(const LineSegment& segment) const
{
    if (isValid() && distance(center, segment.start) <= radius && distance(center, segment.end) <= radius)
    {
	return true;
    }
    return false;
}

bool Circle::containsEntireSegment(const LineSegment& segment) const
{
    if (isValid() && distance(center, findMidPoint(segment)) <= radius && distance(center, segment.start) <= radius && distance(center, segment.end) <= radius)
    {
        return true;
    }
    return false;

}

Circle MinimumEnclosingCircleForSegments(const std::vector<LineSegment>& segments)
{
    std::vector<Point2D> vec = extractPointsFromSegments(segments);
	return minCircle(vec);
}

double distanceSquared(const Point2D& p1, const Point2D& p2)
{
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

double distance(const Point2D& p1, const Point2D& p2)
{
    return std::sqrt(distanceSquared(p1, p2));
}

Circle circleFromDiameter(const Point2D& p1, const Point2D& p2)
{
    Circle c;
    c.center.x = (p1.x + p2.x) / 2.0;
    c.center.y = (p1.y + p2.y) / 2.0;
    c.radius = distance(p1, p2) / 2.0;
    return c;
}

Circle circleFrom3Points(const Point2D& p1, const Point2D& p2, const Point2D& p3)
{
    double d = 2.0 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
    double cx = ((p1.x * p1.x + p1.y * p1.y) * (p2.y - p3.y) + (p2.x * p2.x + p2.y * p2.y) * (p3.y - p1.y) + (p3.x * p3.x + p3.y * p3.y) * (p1.y - p2.y)) / d;
    double cy = ((p1.x * p1.x + p1.y * p1.y) * (p3.x - p2.x) + (p2.x * p2.x + p2.y * p2.y) * (p1.x - p3.x) + (p3.x * p3.x + p3.y * p3.y) * (p2.x - p1.x)) / d;
    Circle c;
    c.center.x = cx;
    c.center.y = cy;
    c.radius = distance(c.center, p1);
    return c;    
}

Circle minCircleHelper(std::vector<Point2D>& points, std::vector<Point2D> boundary, size_t n)
{
    if (n == 0 || boundary.size() == 3)
    {
        if (boundary.empty())
        {
            return {{0,0}, -1.0};
        }
        else if (boundary.size() == 1)
        {
            return {boundary[0], 0.0};
        }
        else if (boundary.size() == 2)
        {
            return circleFromDiameter(boundary[0], boundary[1]);
        }
        else
        {
            return circleFrom3Points(boundary[0], boundary[1], boundary[2]);
        }
    }

    size_t idx = rand() % n;
    Point2D p = points[idx];

    std::swap(points[idx], points[n - 1]);

    Circle cir = minCircleHelper(points, boundary, n - 1);

    if (cir.isValid() && cir.contains(p))
    {
        return cir;
    }
    boundary.push_back(p);
    return minCircleHelper(points, boundary, n - 1);

}

Circle minCircle(std::vector<Point2D> points)
{
    return minCircleHelper(points, {}, points.size());
}

std::vector<Point2D> extractPointsFromSegments(const std::vector<LineSegment>& segments)
{
    std::vector<Point2D> circle;
    circle.reserve(segments.size() * 3);

	for (int i = 0; i < segments.size(); i++) {
		circle.push_back(segments[i].start);
		circle.push_back(findMidPoint(segments[i]));	
		circle.push_back(segments[i].end);
	}
	return circle;
}

Point2D findMidPoint(const LineSegment& segment)
{
    Point2D mid;
    mid.x = (segment.start.x + segment.end.x) / 2;
    mid.y = (segment.start.y + segment.end.y) / 2;
    return mid;
}

