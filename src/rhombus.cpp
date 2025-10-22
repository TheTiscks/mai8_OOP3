#include "rhombus.h"
#include <stdexcept>

void Rhombus::validate() const {
    if (vertices.size() != 4) {
        throw std::runtime_error("Rhombus must have exactly 4 vertices");
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
    double dx1 = vertices[2].x - vertices[0].x; // диагонали перпендикулярны?
    double dy1 = vertices[2].y - vertices[0].y;
    double dx2 = vertices[3].x - vertices[1].x;
    double dy2 = vertices[3].y - vertices[1].y;
    double dotProduct = dx1 * dx2 + dy1 * dy2;
    if (std::abs(dotProduct) > GeometryUtils::EPSILON) {
        throw std::runtime_error("Invalid rhombus: diagonals are not perpendicular");
    }
    for (int i = 0; i < 4; ++i) { // точки не коллинеарны?
        if (GeometryUtils::areCollinear(vertices[i], vertices[(i + 1) % 4], vertices[(i + 2) % 4])) {
            throw std::runtime_error("Invalid rhombus: three consecutive points are collinear");
        }
    }
}

Rhombus::Rhombus(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    vertices = {p1, p2, p3, p4};
    validate();
}

Point Rhombus::geometricCenter() const {
    if (vertices.size() != 4) {
		throw std::runtime_error("Invalid rhombus");
	}
    double sum_x = 0, sum_y = 0;
    for (const auto& v : vertices) {
        sum_x += v.x;
        sum_y += v.y;
    }
    return Point(sum_x / 4, sum_y / 4);
}

double Rhombus::area() const {
    if (vertices.size() != 4) {
		throw std::runtime_error("Invalid rhombus");
	}
    double area = 0;
    for (size_t i = 0; i < 4; ++i) {
        size_t j = (i + 1) % 4;
        area += vertices[i].x * vertices[j].y - vertices[j].x * vertices[i].y;
    }
    return std::abs(area) / 2.0;
}

void Rhombus::print(std::ostream& os) const {
    if (vertices.empty()) {
        os << "Rhombus (moved-from state)";
        return;
    }
    os << "Rhombus vertices: ";
    for (const auto& v : vertices) {
        os << "(" << v.x << ", " << v.y << ") ";
    }
}

void Rhombus::read(std::istream& is) {
    vertices.clear();
    for (int i = 0; i < 4; ++i) {
        double x, y;
        if (!(is >> x >> y)) {
            throw std::runtime_error("Failed to read rhombus vertices");
        }
        vertices.emplace_back(x, y);
    }
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
    if (vertices.size() != rh->vertices.size()) {
		return false;
	}
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (!(vertices[i] == rh->vertices[i])) {
			return false;
    	}
	}
    return true;
}

Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

Rhombus& Rhombus::operator=(Rhombus&& other) noexcept {
    if (this != &other) {
        vertices = std::move(other.vertices);
    }
    return *this;
}