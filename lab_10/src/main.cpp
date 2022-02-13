#include "employees.h"
#include <iostream>
#include <fstream>

int main() {
    EmployeesArray array;
    std::string cm;

    while (std::cin >> cm) {
        if (cm == "exit") {
            return 0;
        } else if (cm == "load") {
            std::string filename;
            std::cin >> filename;
            std::ifstream in(filename);
            in >> array;
        } else if (cm == "save") {
            std::string filename;
            std::cin >> filename;
            std::ofstream out(filename);
            out << array;
        } else if (cm == "add") {
            int type;
            std::cin >> type;
            auto new_employee = Employee::get_instance_by_type(type);
            std::cin >> *new_employee;
            array.add(new_employee);
        } else if (cm == "list") {
            std::cout << array;
        }
    }

    return 0;
}