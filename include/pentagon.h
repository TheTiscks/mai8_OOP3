#ifndef PENTAGON_H
#define PENTAGON_H

#include "figure.h"

class Pentagon : public Figure {
private:
    void validate() const;

public:
    Pentagon() = default;
    Pentagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5);
    Pentagon(const Pentagon& other) = default;
    Pentagon(Pentagon&& other) noexcept = default;
    Point geometricCenter() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    std::shared_ptr<Figure> clone() const override;
    bool equals(const Figure& other) const override;
    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;
};

#endif