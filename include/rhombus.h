#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "figure.h"

class Rhombus : public Figure {
private:
    static const size_t VERTEX_COUNT = 4;
    Point vertices[VERTEX_COUNT];
    bool validState = false;
    void validate() const;

public:
    Rhombus() = default;
    Rhombus(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    Rhombus(const Rhombus& other) = default;
    Rhombus(Rhombus&& other) noexcept = default;
    Point geometricCenter() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    std::shared_ptr<Figure> clone() const override;
    bool equals(const Figure& other) const override;
    size_t vertexCount() const override { return VERTEX_COUNT; }
    Point getVertex(size_t index) const override;
    void setVertex(size_t index, const Point& p) override;
    void clearVertices() override;
    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other) noexcept;
};

#endif