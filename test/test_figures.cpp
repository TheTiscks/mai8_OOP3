#include <gtest/gtest.h>
#include <sstream>
#include "trapezoid.h"
#include "rhombus.h"
#include "pentagon.h"

TEST(FigureTest, ValidTrapezoid) {
    EXPECT_NO_THROW({
        Trapezoid tr(Point(0,0), Point(4,0), Point(3,2), Point(1,2));
    });
}

TEST(FigureTest, InvalidTrapezoid_NoParallelSides) {
    EXPECT_THROW({ // нет паралл
        Trapezoid tr(Point(0,0), Point(1,3), Point(3,2), Point(2,1));
    }, std::runtime_error);
}

TEST(FigureTest, InvalidTrapezoid_TwoParallelSides) {
    EXPECT_THROW({
        // хотя определение параллелограмма как частного случая трапеции имеет место, наиболее принята точка зрения
        // о том, что параллелограм трапецией не является => в рамках данной задачи, удовлетворять проверку не должен
        // см.: https://old.bigenc.ru/mathematics/text/4200431 (БРЭ)
        // см.: с. 126 Математика. Геометрия: 7-9-е классы Л. С. Атанасян, В. Ф. Бутузов ISBN 978-5-09-102538-5
        Trapezoid tr(Point(0,0), Point(2,0), Point(2,2), Point(0,2));
    }, std::runtime_error);
}

TEST(FigureTest, CollinearTrapezoid) {
    EXPECT_THROW({ // 3 т на одной прямой
        Trapezoid tr(Point(0,0), Point(2,0), Point(3,0), Point(1,2));
    }, std::runtime_error);
}

TEST(FigureTest, ValidRhombus) {
    EXPECT_NO_THROW({
        Rhombus rh(Point(0,2), Point(2,0), Point(0,-2), Point(-2,0));
    });
}

TEST(FigureTest, InvalidRhombus) {
    EXPECT_THROW({ // стороны разные - не ромб
        Rhombus rh(Point(0,0), Point(3,0), Point(3,2), Point(0,2));
    }, std::runtime_error);
}

TEST(FigureTest, ValidPentagon) {
    EXPECT_NO_THROW({
        Pentagon pent(Point(0,2), Point(2,1), Point(1,-1), Point(-1,-1), Point(-2,1));
    });
}

TEST(FigureTest, InvalidPentagon) {
    EXPECT_THROW({ // не выпуклый
        Pentagon pent(Point(0,0), Point(3,0), Point(3,3), Point(1,1), Point(0,3));
    }, std::runtime_error);
}

TEST(FigureTest, CollinearPentagon) {
    EXPECT_THROW({ // коллин. точки
        Pentagon pent(Point(0,0), Point(1,0), Point(2,0), Point(2,1), Point(0,1));
    }, std::runtime_error);
}

TEST(FigureTest, StreamOperatorsWithValidation_Valid) {
    Trapezoid tr;
    std::stringstream ss1("0 0 4 0 3 2 1 2");
    EXPECT_NO_THROW(ss1 >> tr);
}

TEST(FigureTest, StreamOperatorsWithValidation_Invalid) {
    Trapezoid tr2; // нет параллельных
    std::stringstream ss2("0 0 1 3 3 2 2 1");
    EXPECT_THROW(ss2 >> tr2, std::runtime_error);
}

TEST(FigureTest, RhombusStreamValidation) {
    Rhombus rh1;
    std::stringstream ss1("0 2 2 0 0 -2 -2 0");
    EXPECT_NO_THROW(ss1 >> rh1);

    Rhombus rh2;
    std::stringstream ss2("0 0 3 0 3 2 0 2"); // не ромб
    EXPECT_THROW(ss2 >> rh2, std::runtime_error);
}

TEST(FigureTest, PentagonStreamValidation) {
    Pentagon pent1;
    std::stringstream ss1("0 2 2 1 1 -1 -1 -1 -2 1");
    EXPECT_NO_THROW(ss1 >> pent1);

    Pentagon pent2;
    std::stringstream ss2("0 0 3 0 3 3 1 1 0 3"); // невыпуклый
    EXPECT_THROW(ss2 >> pent2, std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}