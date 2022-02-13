#include "employees.h"
#include <iostream>
#include <fstream>
#include <cassert>

const int MAX_NAME_LENGTH = 102;

int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) {
        salary += 1000;
    }
    return salary;
}

void Developer::print(std::ostream &out) const {
    out << "Developer\n";
    Employee::print(out);
    out << "Has bonus: " << (_has_bonus ? "+" : "-") << "\n";
}

void Developer::scan(std::istream &in) {
    Employee::scan(in);
    in >> _has_bonus;
}

void Developer::print(std::ofstream &out) const {
    int32_t type = 1;
    out.write((char *) &type, sizeof(int32_t));
    Employee::print(out);
    out.write((char *) (&_has_bonus), sizeof(char));
}

void Developer::scan(std::ifstream &in) {
    Employee::scan(in);
    in.read((char *) &_has_bonus, sizeof(char));
}

int SalesManager::salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
}

void SalesManager::print(std::ostream &out) const {
    out << "Sales Manager\n";
    Employee::print(out);
    out << "Sold items: " << _sold_nm << "\n";
    out << "Item price: " << _price << "\n";
}

void SalesManager::scan(std::istream &in) {
    Employee::scan(in);
    in >> _sold_nm >> _price;
}

void SalesManager::print(std::ofstream &out) const {
    int32_t type = 2;
    out.write((char *) &type, sizeof(int32_t));
    Employee::print(out);
    out.write((char *) (&_sold_nm), sizeof(int32_t));
    out.write((char *) (&_price), sizeof(int32_t));
}

void SalesManager::scan(std::ifstream &in) {
    Employee::scan(in);
    in.read((char *) &_sold_nm, sizeof(int32_t));
    in.read((char *) &_price, sizeof(int32_t));
}

void EmployeesArray::add(Employee *e) {
    _employees.push_back(e);
}

int EmployeesArray::total_salary() const {
    int result = 0;
    for (Employee *i : _employees) {
        result += i->salary();
    }
    return result;
}

std::ostream &operator<<(std::ostream &out, const EmployeesArray &e_array) {
    for (size_t i = 0; i < e_array._employees.size(); ++i) {
        out << i + 1 << ". " << *e_array._employees[i];
    }

    out << "== Total salary: " << e_array.total_salary() << "\n";
    out << "\n";
    return out;
}

std::ofstream &operator<<(std::ofstream &out, const EmployeesArray &e_array) {
    int32_t sz = e_array._employees.size();
    out.write((char *) (&sz), sizeof(int32_t));
    for (Employee *e : e_array._employees) {
        out << *e;
    }
    return out;
}

std::ifstream &operator>>(std::ifstream &in, EmployeesArray &e_array) {
    int32_t sz;
    in.read((char *) &sz, sizeof(int32_t));
    for (int i = 0; i < sz; ++i) {
        int32_t type;
        in.read((char *) &type, sizeof(int32_t));
        Employee *new_employee = Employee::get_instance_by_type(type);
        in >> *new_employee;
        e_array.add(new_employee);
    }
    return in;
}

EmployeesArray::~EmployeesArray() {
    for (Employee *e : _employees) {
        delete e;
    }
}

std::ostream &operator<<(std::ostream &out, const Employee &e) {
    e.print(out);
    return out;
}

void Employee::print(std::ostream &out) const {
    out << "Name: " << name << "\n";
    out << "Base Salary: " << _base_salary << "\n";
}

std::istream &operator>>(std::istream &in, Employee &e) {
    e.scan(in);
    return in;
}

void Employee::scan(std::istream &in) {
    in >> name >> _base_salary;
}

std::ofstream &operator<<(std::ofstream &out, const Employee &e) {
    e.print(out);
    return out;
}

void Employee::print(std::ofstream &out) const {
    out.write(name.c_str(), sizeof(char) * (name.length() + 1));
    out.write((char *) &_base_salary, sizeof(int32_t));
}

std::ifstream &operator>>(std::ifstream &in, Employee &e) {
    e.scan(in);
    return in;
}

void Employee::scan(std::ifstream &in) {
    char buf[MAX_NAME_LENGTH]{};
    in.getline(buf, sizeof(buf), '\0');
    name = std::string(buf);
    in.read((char *) &_base_salary, sizeof(int32_t));
}

Employee *Employee::get_instance_by_type(int type) {
    if (type == 1) {
        return new Developer();
    } else if (type == 2) {
        return new SalesManager();
    }
    assert(false && "Incorrect type");
}

Employee::~Employee() {}

