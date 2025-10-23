#include "trapezoid.h"
#include <stdexcept>

void Trapezoid::validate() const {
    if (!validState) {
        throw std::runtime_error("Trapezoid is in invalid state");
    }

    for (int i = 0; i < 4; ++i) {
        if (GeometryUtils::areCollinear(vertices[i], vertices[(i + 1) % 4], vertices[(i + 2) % 4])) {
            throw std::runtime_error("Invalid trapezoid: three consecutive points are collinear");
        }
    }
    int sign = 0;
    for (int i = 0; i < 4; ++i) {
        const Point& a = vertices[i];
        const Point& b = vertices[(i + 1) % 4];
        const Point& c = vertices[(i + 2) % 4];
        double cross = GeometryUtils::crossProduct(a, b, c);
        if (sign == 0) {
            sign = (cross > 0) ? 1 : -1;
        } else if ((cross > 0 && sign < 0) || (cross < 0 && sign > 0)) {
            throw std::runtime_error("Invalid trapezoid: polygon is not convex");
        }
    }
    int parallelCount = 0;
    if (GeometryUtils::areParallel(vertices[0], vertices[1], vertices[2], vertices[3])) {
        parallelCount++;
    }
    if (GeometryUtils::areParallel(vertices[1], vertices[2], vertices[3], vertices[0])) {
        parallelCount++;
    }
    if (parallelCount != 1) {
        throw std::runtime_error("Invalid trapezoid: must have exactly one pair of parallel sides");
    }
}

Trapezoid::Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    vertices[0] = p1;
    vertices[1] = p2;
    vertices[2] = p3;
    vertices[3] = p4;
    validState = true;
    validate();
}

Point Trapezoid::geometricCenter() const {
    validate();

    double sum_x = 0, sum_y = 0;
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        sum_x += vertices[i].x;
        sum_y += vertices[i].y;
    }
    return Point(sum_x / VERTEX_COUNT, sum_y / VERTEX_COUNT);
}

double Trapezoid::area() const {
    validate();
    double area = 0;
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        size_t j = (i + 1) % VERTEX_COUNT;
        area += vertices[i].x * vertices[j].y - vertices[j].x * vertices[i].y;
    }
    return std::abs(area) / 2.0;
}

void Trapezoid::print(std::ostream& os) const {
    if (!validState) {
        os << "Trapezoid (moved-from state)";
        return;
    }

    os << "Trapezoid vertices: ";
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        os << "(" << vertices[i].x << ", " << vertices[i].y << ") ";
    }
}

void Trapezoid::read(std::istream& is) {
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        double x, y;
        if (!(is >> x >> y)) {
            throw std::runtime_error("Failed to read trapezoid vertices");
        }
        vertices[i] = Point(x, y);
    }
    validState = true;
    validate();
}

std::shared_ptr<Figure> Trapezoid::clone() const {
    return std::make_shared<Trapezoid>(*this);
}

bool Trapezoid::equals(const Figure& other) const {
    const Trapezoid* tr = dynamic_cast<const Trapezoid*>(&other);
    if (!tr) {
        return false;
    }
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        if (!(vertices[i] == tr->vertices[i])) {
            return false;
        }
    }
    return true;
}

Point Trapezoid::getVertex(size_t index) const {
    if (index >= VERTEX_COUNT) {
        throw std::out_of_range("Vertex index out of range");
    }
    return vertices[index];
}

void Trapezoid::setVertex(size_t index, const Point& p) {
    if (index >= VERTEX_COUNT) {
        throw std::out_of_range("Vertex index out of range");
    }
    vertices[index] = p;
    validState = true;
}

void Trapezoid::clearVertices() {
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        vertices[i] = Point(0, 0);
    }
    validState = false;
}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) {
        for (size_t i = 0; i < VERTEX_COUNT; ++i) {
            vertices[i] = other.vertices[i];
        }
        validState = other.validState;
    }
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < VERTEX_COUNT; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
        validState = other.validState;
        other.validState = false;
    }
    return *this;
}