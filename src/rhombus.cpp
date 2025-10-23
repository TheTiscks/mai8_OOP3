#include "rhombus.h"
#include <stdexcept>

void Rhombus::validate() const {
    if (!validState) {
        throw std::runtime_error("Rhombus is in invalid state");
    }

    double side1 = GeometryUtils::distance(vertices[0], vertices[1]);
    double side2 = GeometryUtils::distance(vertices[1], vertices[2]);
    double side3 = GeometryUtils::distance(vertices[2], vertices[3]);
    double side4 = GeometryUtils::distance(vertices[3], vertices[0]);

    if (std::abs(side1 - side2) > GeometryUtils::EPSILON ||
        std::abs(side2 - side3) > GeometryUtils::EPSILON ||
        std::abs(side3 - side4) > GeometryUtils::EPSILON) {
        throw std::runtime_error("Invalid rhombus: all sides must be equal");
    }

    double dx1 = vertices[2].x - vertices[0].x;
    double dy1 = vertices[2].y - vertices[0].y;
    double dx2 = vertices[3].x - vertices[1].x;
    double dy2 = vertices[3].y - vertices[1].y;
    double dotProduct = dx1 * dx2 + dy1 * dy2;

    if (std::abs(dotProduct) > GeometryUtils::EPSILON) {
        throw std::runtime_error("Invalid rhombus: diagonals are not perpendicular");
    }

    for (int i = 0; i < 4; ++i) {
        if (GeometryUtils::areCollinear(vertices[i], vertices[(i + 1) % 4], vertices[(i + 2) % 4])) {
            throw std::runtime_error("Invalid rhombus: three consecutive points are collinear");
        }
    }
}

Rhombus::Rhombus(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    vertices[0] = p1;
    vertices[1] = p2;
    vertices[2] = p3;
    vertices[3] = p4;
    validState = true;
    validate();
}

Point Rhombus::geometricCenter() const {
    validate();
    double sum_x = 0, sum_y = 0;
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        sum_x += vertices[i].x;
        sum_y += vertices[i].y;
    }
    return Point(sum_x / VERTEX_COUNT, sum_y / VERTEX_COUNT);
}

double Rhombus::area() const {
    validate();
    double area = 0;
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        size_t j = (i + 1) % VERTEX_COUNT;
        area += vertices[i].x * vertices[j].y - vertices[j].x * vertices[i].y;
    }
    return std::abs(area) / 2.0;
}

void Rhombus::print(std::ostream& os) const {
    if (!validState) {
        os << "Rhombus (moved-from state)";
        return;
    }
    os << "Rhombus vertices: ";
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        os << "(" << vertices[i].x << ", " << vertices[i].y << ") ";
    }
}

void Rhombus::read(std::istream& is) {
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        double x, y;
        if (!(is >> x >> y)) {
            throw std::runtime_error("Failed to read rhombus vertices");
        }
        vertices[i] = Point(x, y);
    }
    validState = true;
    validate();
}

std::shared_ptr<Figure> Rhombus::clone() const {
    return std::make_shared<Rhombus>(*this);
}

bool Rhombus::equals(const Figure& other) const {
    const Rhombus* rh = dynamic_cast<const Rhombus*>(&other);
    if (!rh) {
        return false;
    }
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        if (!(vertices[i] == rh->vertices[i])) {
            return false;
        }
    }
    return true;
}

Point Rhombus::getVertex(size_t index) const {
    if (index >= VERTEX_COUNT) {
        throw std::out_of_range("Vertex index out of range");
    }
    return vertices[index];
}

void Rhombus::setVertex(size_t index, const Point& p) {
    if (index >= VERTEX_COUNT) {
        throw std::out_of_range("Vertex index out of range");
    }
    vertices[index] = p;
    validState = true;
}

void Rhombus::clearVertices() {
    for (size_t i = 0; i < VERTEX_COUNT; ++i) {
        vertices[i] = Point(0, 0);
    }
    validState = false;
}

Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) {
        for (size_t i = 0; i < VERTEX_COUNT; ++i) {
            vertices[i] = other.vertices[i];
        }
        validState = other.validState;
    }
    return *this;
}

Rhombus& Rhombus::operator=(Rhombus&& other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < VERTEX_COUNT; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
        validState = other.validState;
        other.validState = false;
    }
    return *this;
}