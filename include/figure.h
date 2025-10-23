#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    bool operator==(const Point& other) const;
};

namespace GeometryUtils {
    const double EPSILON = 1e-9;
    double distance(const Point& a, const Point& b);
    double crossProduct(const Point& a, const Point& b, const Point& c);
    bool areParallel(const Point& a, const Point& b, const Point& c, const Point& d);
    bool areCollinear(const Point& a, const Point& b, const Point& c);
}

class Figure {
public:
    virtual ~Figure() = default;
    virtual Point geometricCenter() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual std::shared_ptr<Figure> clone() const = 0;
    virtual bool equals(const Figure& other) const = 0;
    virtual size_t vertexCount() const = 0;
    virtual Point getVertex(size_t index) const = 0;
    virtual void setVertex(size_t index, const Point& p) = 0;
    virtual void clearVertices() = 0;
    virtual operator double() const;
    bool operator==(const Figure& other) const;
    bool operator!=(const Figure& other) const;
};

std::ostream& operator<<(std::ostream& os, const Figure& fig);
std::istream& operator>>(std::istream& is, Figure& fig);

#endif