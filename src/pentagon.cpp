#include "pentagon.h"
#include <stdexcept>

void Pentagon::validate() const {
    if (vertices.size() != 5) {
        throw std::runtime_error("Pentagon must have exactly 5 vertices");
    }
    int sign = 0; // у выпуклого 5-угольника все векторные произв имеют один знак
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
    for (int i = 0; i < 5; ++i) { // стороны > 0
        double side = GeometryUtils::distance(vertices[i], vertices[(i + 1) % 5]);
        if (side < GeometryUtils::EPSILON) {
            throw std::runtime_error("Invalid pentagon: side length is too small");
        }
    }
}

Pentagon::Pentagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5) {
    vertices = {p1, p2, p3, p4, p5};
    validate();
}

Point Pentagon::geometricCenter() const {
    if (vertices.size() != 5) {
		throw std::runtime_error("Invalid pentagon");
    }
	double sum_x = 0, sum_y = 0;
    for (const auto& v : vertices) {
        sum_x += v.x;
        sum_y += v.y;
    }
    return Point(sum_x / 5, sum_y / 5);
}

double Pentagon::area() const {
    if (vertices.size() != 5) {
		throw std::runtime_error("Invalid pentagon");
    }
	double area = 0;
    for (size_t i = 0; i < 5; ++i) {
        size_t j = (i + 1) % 5;
        area += vertices[i].x * vertices[j].y - vertices[j].x * vertices[i].y;
    }
    return std::abs(area) / 2.0;
}

void Pentagon::print(std::ostream& os) const {
    if (vertices.empty()) {
        os << "Pentagon (moved-from state)";
        return;
    }
    os << "Pentagon vertices: ";
    for (const auto& v : vertices) {
        os << "(" << v.x << ", " << v.y << ") ";
    }
}

void Pentagon::read(std::istream& is) {
    vertices.clear();
    for (int i = 0; i < 5; ++i) {
        double x, y;
        if (!(is >> x >> y)) {
            throw std::runtime_error("Failed to read pentagon vertices");
        }
        vertices.emplace_back(x, y);
    }
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
    if (vertices.size() != p->vertices.size()) {
		return false;
	}
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (!(vertices[i] == p->vertices[i])) {
			return false;
    	}
	}
    return true;
}

Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}