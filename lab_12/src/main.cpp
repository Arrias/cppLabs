#include <vector>
#include <iostream>
#include "matrix.h"
#include <fstream>

const int REG_CNT = 10;

std::size_t get_register_num(std::string arg) {
    return stoi(arg.substr(1, arg.size()));
}

int main() {
    Matrix *registers = new Matrix[REG_CNT];

    std::string command;
    while (std::cin >> command) {
        try {
            if (command == "load") {
                std::string reg, f_name;
                std::cin >> reg >> f_name;
                int num = get_register_num(reg);
                registers[num] = Matrix::load(f_name);

            } else if (command == "print") {
                std::string reg;
                std::cin >> reg;
                int num = get_register_num(reg);
                registers[num].print();

            } else if (command == "add") {
                std::string reg1, reg2;
                std::cin >> reg1 >> reg2;
                int num1 = get_register_num(reg1);
                int num2 = get_register_num(reg2);
                registers[num1] += registers[num2];

            } else if (command == "mul") {
                std::string reg1, reg2;
                std::cin >> reg1 >> reg2;
                int num1 = get_register_num(reg1);
                int num2 = get_register_num(reg2);
                registers[num1] *= registers[num2];

            } else if (command == "elem") {
                std::string reg;
                std::size_t row, col;
                std::cin >> reg >> row >> col;
                int num = get_register_num(reg);
                std::cout << registers[num].get(row, col) << "\n";
            } else {
                break;

            }
        } catch (const MatrixException &e) {
            std::cout << e.what() << "\n";
        } catch (const std::ifstream::failure &e) {
            std::cout << "LOAD: unable to open file.\n";
        } catch (const std::bad_alloc &e) {
            std::cout << "Unable to allocate memory.\n";
        }
    }

    delete[] registers;
    return 0;
}