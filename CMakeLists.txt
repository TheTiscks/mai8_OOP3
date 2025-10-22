cmake_minimum_required(VERSION 3.10)
project(Figures)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_subdirectory(libs/googletest)

add_library(figures
        src/figure.cpp
        src/trapezoid.cpp
        src/rhombus.cpp
        src/pentagon.cpp
)

add_executable(main_app main.cpp)
target_link_libraries(main_app figures)

add_executable(tests test/test_figures.cpp)
target_link_libraries(tests figures gtest gtest_main)

enable_testing()
add_test(NAME FiguresTests COMMAND tests)