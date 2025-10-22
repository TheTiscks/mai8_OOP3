#include "figure.h"
#include <stdexcept>

bool Point::operator==(const Point& other) const {
    return std::abs(x - other.x) < GeometryUtils::EPSILON &&
           std::abs(y - other.y) < GeometryUtils::EPSILON;
}

namespace GeometryUtils {
    double distance(const Point& a, const Point& b) {
        return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
    double crossProduct(const Point& a, const Point& b, const Point& c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }
    bool areParallel(const Point& a, const Point& b, const Point& c, const Point& d) {
        double dx1 = b.x - a.x; // v1
        double dy1 = b.y - a.y;
        double dx2 = d.x - c.x; // v2
        double dy2 = d.y - c.y;
        if (std::abs(dx1 * dy2 - dy1 * dx2) > EPSILON) {
            return false; // векторы || если их векторное произведение = нулю (-> 0)
        }
        double length1 = std::sqrt(dx1 * dx1 + dy1 * dy1);
        double length2 = std::sqrt(dx2 * dx2 + dy2 * dy2);
        return (length1 > EPSILON && length2 > EPSILON); // векторы не должны быть 0
    }
    bool areCollinear(const Point& a, const Point& b, const Point& c) {
        return std::abs(crossProduct(a, b, c)) < EPSILON;
    }
}

Figure::operator double() const {
    return area();
}

bool Figure::operator==(const Figure& other) const {
    return equals(other);
}

bool Figure::operator!=(const Figure& other) const {
    return !equals(other);
}

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    fig.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.read(is);
    return is;
}