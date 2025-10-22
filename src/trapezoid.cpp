#include "trapezoid.h"
#include <stdexcept>

void Trapezoid::validate() const {
    if (vertices.size() != 4) {
        throw std::runtime_error("Trapezoid must have exactly 4 vertices");
    }
    for (int i = 0; i < 4; ++i) { // коллинеарность
        if (GeometryUtils::areCollinear(vertices[i], vertices[(i + 1) % 4], vertices[(i + 2) % 4])) {
            throw std::runtime_error("Invalid trapezoid: three consecutive points are collinear");
        }
    }
    int sign = 0; // выпуклая?
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
    // трапеция должна иметь 1 пару паралл сторон (подробнее - в комментариях тестов)
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
    vertices = {p1, p2, p3, p4};
    validate();
}

Point Trapezoid::geometricCenter() const {
    if (vertices.size() != 4) {
        throw std::runtime_error("Invalid trapezoid");
    }
    double sum_x = 0, sum_y = 0;
    for (const auto& v : vertices) {
        sum_x += v.x;
        sum_y += v.y;
    }
    return Point(sum_x / 4, sum_y / 4);
}

double Trapezoid::area() const {
    if (vertices.size() != 4) {
		throw std::runtime_error("Invalid trapezoid");
    }
	double area = 0;
    for (size_t i = 0; i < 4; ++i) {
        size_t j = (i + 1) % 4;
        area += vertices[i].x * vertices[j].y - vertices[j].x * vertices[i].y;
    }
    return std::abs(area) / 2.0;
}

void Trapezoid::print(std::ostream& os) const {
    if (vertices.empty()) {
        os << "Trapezoid (moved-from state)";
        return;
    }
    os << "Trapezoid vertices: ";
    for (const auto& v : vertices) {
        os << "(" << v.x << ", " << v.y << ") ";
    }
}

void Trapezoid::read(std::istream& is) {
    vertices.clear();
    for (int i = 0; i < 4; ++i) {
        double x, y;
        if (!(is >> x >> y)) {
            throw std::runtime_error("Failed to read trapezoid vertices");
        }
        vertices.emplace_back(x, y);
    }
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
    if (vertices.size() != tr->vertices.size()) {
        return false;
    }
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (!(vertices[i] == tr->vertices[i])) {
            return false;
        }
    }
    return true;
}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}