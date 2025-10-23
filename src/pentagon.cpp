#include "pentagon.h"
#include <stdexcept>

void Pentagon::validate() const {
    if (!validState) {
        throw std::runtime_error("Pentagon is in invalid state");
    }
    int sign = 0;
    for (int i = 0; i < 5; ++i) {
        const Point& a = vertices[i];
        const Point& b = vertices[(i + 1) % 5];
        const Point& c = vertices[(i + 2) % 5];
        double cross = GeometryUtils::crossProduct(a, b, c);
        if (std::abs(cross) < GeometryUtils::EPSILON) {
            throw std::runtime_error("Invalid pentagon: three consecutive points are collinear");
        }
        if (sign == 0) {
            sign = (cross > 0) ? 1 : -1;
        } else if ((cross > 0 && sign < 0) || (cross < 0 && sign > 0)) {
            throw std::runtime_error("Invalid pentagon: polygon is not convex");
        }
    }
    for (int i = 0; i < 5; ++i) {
        double side = GeometryUtils::distance(vertices[i], vertices[(i + 1) % 5]);
        if (side < GeometryUtils::EPSILON) {
            throw std::runtime_error("Invalid pentagon: side length is too small");
        }
    }
}

Pentagon::Pentagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5) {
    vertices[0] = p1;
    vertices[1] = p2;
    vertices[2] = p3;
    vertices[3] = p4;
    vertices[4] = p5;
    validState = true;
    validate();
}

Point Pentagon::geometricCenter() const {
    validate();
    double sum_x = 0, sum_y = 0;
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        sum_x += vertices[i].x;
        sum_y += vertices[i].y;
    }
    return Point(sum_x / VERTEX_COUNT, sum_y / VERTEX_COUNT);
}

double Pentagon::area() const {
    validate();
    double area = 0;
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        size_t j = (i + 1) % VERTEX_COUNT;
        area += vertices[i].x * vertices[j].y - vertices[j].x * vertices[i].y;
    }
    return std::abs(area) / 2.0;
}

void Pentagon::print(std::ostream& os) const {
    if (!validState) {
        os << "Pentagon (moved-from state)";
        return;
    }
    os << "Pentagon vertices: ";
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        os << "(" << vertices[i].x << ", " << vertices[i].y << ") ";
    }
}

void Pentagon::read(std::istream& is) {
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        double x, y;
        if (!(is >> x >> y)) {
            throw std::runtime_error("Failed to read pentagon vertices");
        }
        vertices[i] = Point(x, y);
    }
    validState = true;
    validate();
}

std::shared_ptr<Figure> Pentagon::clone() const {
    return std::make_shared<Pentagon>(*this);
}

bool Pentagon::equals(const Figure& other) const {
    const Pentagon* p = dynamic_cast<const Pentagon*>(&other);
    if (!p) {
        return false;
    }
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        if (!(vertices[i] == p->vertices[i])) {
            return false;
        }
    }
    return true;
}

Point Pentagon::getVertex(size_t index) const {
    if (index >= VERTEX_COUNT) {
        throw std::out_of_range("Vertex index out of range");
    }
    return vertices[index];
}

void Pentagon::setVertex(size_t index, const Point& p) {
    if (index >= VERTEX_COUNT) {
        throw std::out_of_range("Vertex index out of range");
    }
    vertices[index] = p;
    validState = true;
}

void Pentagon::clearVertices() {
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        vertices[i] = Point(0, 0);
    }
    validState = false;
}

Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this != &other) {
        for (size_t i = 0; i < VERTEX_COUNT; ++i) {
            vertices[i] = other.vertices[i];
        }
        validState = other.validState;
    }
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < VERTEX_COUNT; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
        validState = other.validState;
        other.validState = false;
    }
    return *this;
}