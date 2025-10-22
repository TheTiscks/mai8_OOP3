#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <typeinfo>
#include <limits>
#include "figure.h"
#include "trapezoid.h"
#include "rhombus.h"
#include "pentagon.h"

class FigureArray {
private:
    std::vector<std::shared_ptr<Figure>> figures;

public:
    void addFigure(std::shared_ptr<Figure> fig) {
        figures.push_back(fig);
    }

    void removeFigure(size_t index) {
        if (index < figures.size()) {
            figures.erase(figures.begin() + index);
        }
    }

    void printAll() const {
        std::cout << "\n= All Figures =" << std::endl;
        for (size_t i = 0; i < figures.size(); ++i) {
            std::cout << "Figure " << i << ": " << *figures[i] << std::endl;
            Point center = figures[i]->geometricCenter();
            double area = figures[i]->area();
            std::cout << "  Centre: (" << std::fixed << std::setprecision(2) << center.x
                      << ", " << center.y << "), Area: " << area << std::endl;
        }
    }

    double totalArea() const {
        double total = 0;
        for (const auto& fig : figures) {
            total += fig->area();
        }
        return total;
    }

    size_t size() const { return figures.size(); }

    void demonstrateOperations() {
        if (figures.size() == 0) {
            std::cout << "No figures available for demonstration!" << std::endl;
            return;
        }
        std::cout << "\n= Demonstration =" << std::endl;
        std::cout << "Available figures:" << std::endl;
        for (size_t i = 0; i < figures.size(); ++i) {
            std::string type = "Unknown";
            if (dynamic_cast<Trapezoid*>(figures[i].get())) {
				type = "Trapezoid";
            } else if (dynamic_cast<Rhombus*>(figures[i].get())) {
				type = "Rhombus";
            } else if (dynamic_cast<Pentagon*>(figures[i].get())) {
				type = "Pentagon";
			}
            std::cout << "[" << i << "] " << type << ": " << *figures[i] << std::endl;
        }
        std::cout << "\n1. COPY:" << std::endl;
        std::cout << "Enter index of figure to copy (0-" << figures.size()-1 << "): ";
        size_t copy_index;
        std::cin >> copy_index;
        if (copy_index >= figures.size()) {
            std::cout << "Invalid index! Using first figure." << std::endl;
            copy_index = 0;
        }
        auto original = figures[copy_index];
        auto copy = original->clone();
        std::cout << "Original: " << *original << std::endl;
        std::cout << "Copy: " << *copy << std::endl;
        std::cout << "Are equal: " << (*original == *copy ? "true" : "false") << std::endl;
        std::cout << "\n2. MOVE:" << std::endl;
        if (figures.size() >= 2) {
            std::cout << "Enter source index (0-" << figures.size()-1 << "): ";
            size_t src_index;
            std::cin >> src_index;
            std::cout << "Enter destination index (0-" << figures.size()-1 << "): ";
            size_t dest_index;
            std::cin >> dest_index;
            if (src_index >= figures.size() || dest_index >= figures.size()) {
                std::cout << "Invalid indexes! Using automatic demonstration." << std::endl;
                Trapezoid temp1(Point(0,0), Point(5,0), Point(4,3), Point(1,3));
                Trapezoid temp2(Point(1,1), Point(6,1), Point(5,4), Point(2,4));
                std::cout << "Temp1 before move: " << temp1 << std::endl;
                std::cout << "Temp2 before move: " << temp2 << std::endl;
                temp2 = std::move(temp1);
                std::cout << "After move:" << std::endl;
                std::cout << "Temp1: " << temp1 << std::endl;
                std::cout << "Temp2: " << temp2 << std::endl;
            } else {
                auto& src_fig = figures[src_index];
                auto& dest_fig = figures[dest_index];
                std::cout << "Before move:" << std::endl;
                std::cout << "Source: " << *src_fig << std::endl;
                std::cout << "Destination: " << *dest_fig << std::endl;
                auto src_backup = src_fig->clone();
                auto dest_backup = dest_fig->clone();
                bool move_performed = false;
                if (auto trapezoid_src = std::dynamic_pointer_cast<Trapezoid>(src_fig)) {
                    if (auto trapezoid_dest = std::dynamic_pointer_cast<Trapezoid>(dest_fig)) {
                        *trapezoid_dest = std::move(*trapezoid_src);
                        move_performed = true;
                    }
                }
                if (!move_performed) {
                    if (auto rhombus_src = std::dynamic_pointer_cast<Rhombus>(src_fig)) {
                        if (auto rhombus_dest = std::dynamic_pointer_cast<Rhombus>(dest_fig)) {
                            *rhombus_dest = std::move(*rhombus_src);
                            move_performed = true;
                        }
                    }
                }
                if (!move_performed) {
                    if (auto pentagon_src = std::dynamic_pointer_cast<Pentagon>(src_fig)) {
                        if (auto pentagon_dest = std::dynamic_pointer_cast<Pentagon>(dest_fig)) {
                            *pentagon_dest = std::move(*pentagon_src);
                            move_performed = true;
                        }
                    }
                }
                if (move_performed) {
                    std::cout << "After move:" << std::endl;
                    std::cout << "Source: " << *src_fig << std::endl;
                    std::cout << "Destination: " << *dest_fig << std::endl;
                    src_fig = src_backup;
                    dest_fig = dest_backup;
                    std::cout << "After restoration:" << std::endl;
                    std::cout << "Source: " << *src_fig << std::endl;
                    std::cout << "Destination: " << *dest_fig << std::endl;
                } else {
                    std::cout << "Cant move different figure types! Using temporary objs" << std::endl;
                    Rhombus temp1(Point(0,0), Point(2,3), Point(4,0), Point(2,-3));
                    Rhombus temp2(Point(1,1), Point(3,4), Point(5,1), Point(3,-2));
                    std::cout << "Temp1 before move: " << temp1 << std::endl;
                    std::cout << "Temp2 before move: " << temp2 << std::endl;
                    temp2 = std::move(temp1);
                    std::cout << "After move:" << std::endl;
                    std::cout << "Temp1: " << temp1 << std::endl;
                    std::cout << "Temp2: " << temp2 << std::endl;
                }
            }
        } else {
            std::cout << "Need at least 2 figures for move operation!" << std::endl;
        }
        std::cout << "\n3. COMPARE:" << std::endl;
        if (figures.size() >= 2) {
            std::cout << "Enter first figure index (0-" << figures.size()-1 << "): ";
            size_t comp_index1;
            std::cin >> comp_index1;
            std::cout << "Enter second figure index (0-" << figures.size()-1 << "): ";
            size_t comp_index2;
            std::cin >> comp_index2;
            if (comp_index1 >= figures.size() || comp_index2 >= figures.size()) {
                std::cout << "Invalid indexes! Using first 2 figs" << std::endl;
                comp_index1 = 0;
                comp_index2 = 1;
            }
            auto fig1 = figures[comp_index1];
            auto fig2 = figures[comp_index2];
            std::string type1 = "Unknown";
            std::string type2 = "Unknown";
            if (dynamic_cast<Trapezoid*>(fig1.get())) {
				type1 = "Trapezoid";
            } else if (dynamic_cast<Rhombus*>(fig1.get())) {
				type1 = "Rhombus";
            } else if (dynamic_cast<Pentagon*>(fig1.get())) {
				type1 = "Pentagon";
			}
            if (dynamic_cast<Trapezoid*>(fig2.get())) {
				type2 = "Trapezoid";
            } else if (dynamic_cast<Rhombus*>(fig2.get())) {
				type2 = "Rhombus";
            } else if (dynamic_cast<Pentagon*>(fig2.get())) {
				type2 = "Pentagon";
			}
            std::cout << "Figure 1 (" << type1 << "): " << *fig1 << std::endl;
            std::cout << "Figure 2 (" << type2 << "): " << *fig2 << std::endl;
            std::cout << "Figure 1 == Figure 2: " << (*fig1 == *fig2 ? "true" : "false") << std::endl;
            std::cout << "Figure 1 != Figure 2: " << (*fig1 != *fig2 ? "true" : "false") << std::endl;
        } else {
            std::cout << "Need at least 2 figures for comparison!" << std::endl;
        }
    }
};

void printMenu() {
    //std::cout << "\n" << std::endl;
    std::cout << "1. Add Trapezoid" << std::endl;
    std::cout << "2. Add Rhombus" << std::endl;
    std::cout << "3. Add Pentagon" << std::endl;
    std::cout << "4. Remove figure by index" << std::endl;
    std::cout << "5. Print all figures (with centres and areas)" << std::endl;
    std::cout << "6. Show total area" << std::endl;
    std::cout << "7. Demonstrate operations (copy, move, compare)" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Choice: ";
}

int main() {
    FigureArray array;
    int choice;
    std::cout << "= Manage figures =" << std::endl;
    do {
        printMenu();
        std::cin >> choice;
        try {
            switch (choice) {
                case 1: {
                    std::cout << "Enter 4 vertices for trapezoid (8 numbers): ";
                    auto tr = std::make_shared<Trapezoid>();
                    std::cin >> *tr;
                    array.addFigure(tr);
                    std::cout << "Trapezoid added successfully!" << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "Enter 4 vertices for rhombus (8 numbers): ";
                    auto rh = std::make_shared<Rhombus>();
                    std::cin >> *rh;
                    array.addFigure(rh);
                    std::cout << "Rhombus added successfully!" << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "Enter 5 vertices for pentagon (10 numbers): ";
                    auto pent = std::make_shared<Pentagon>();
                    std::cin >> *pent;
                    array.addFigure(pent);
                    std::cout << "Pentagon added successfully!" << std::endl;
                    break;
                }
                case 4: {
                    if (array.size() == 0) {
                        std::cout << "No figure to remove" << std::endl;
                        break;
                    }
                    std::cout << "Enter index to remove (0-" << array.size()-1 << "): ";
                    size_t index;
                    std::cin >> index;
                    if (index < array.size()) {
                        array.removeFigure(index);
                        std::cout << "Figure removed!" << std::endl;
                    } else {
                        std::cout << "Invalid index!" << std::endl;
                    }
                    break;
                }
                case 5: {
                    if (array.size() == 0) {
                        std::cout << "No figures to display!" << std::endl;
                        break;
                    }
                    array.printAll();
                    break;
                }
                case 6: {
                    if (array.size() == 0) {
                        std::cout << "No figures - total area is 0" << std::endl;
                        break;
                    }
                    std::cout << "Total area of all figures: " << array.totalArea() << std::endl;
                    break;
                }
                case 7: {
                    array.demonstrateOperations();
                    break;
                }
                case 0:
                    std::cout << "Goodbye!" << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice!" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 0);
    return 0;
}