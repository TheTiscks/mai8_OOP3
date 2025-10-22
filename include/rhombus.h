#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "figure.h"

class Rhombus : public Figure {
private:
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
    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other) noexcept;
};

#endif