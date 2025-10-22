#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "figure.h"

class Trapezoid : public Figure {
private:
    void validate() const;

public:
    Trapezoid() = default;
    Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    Trapezoid(const Trapezoid& other) = default;
    Trapezoid(Trapezoid&& other) noexcept = default;
    Point geometricCenter() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    std::shared_ptr<Figure> clone() const override;
    bool equals(const Figure& other) const override;
    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;
};

#endif