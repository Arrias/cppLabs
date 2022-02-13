#ifndef LAB11_EMPLOYEES_H_INCLUDED
#define LAB11_EMPLOYEES_H_INCLUDED

#include <cstdint>
#include <string>
#include <vector>

class Employee {
public:
    virtual int salary() const = 0;

    static Employee *get_instance_by_type(int type);

    friend std::ostream &operator<<(std::ostream &out, const Employee &e);

    friend std::istream &operator>>(std::istream &in, Employee &e);

    friend std::ofstream &operator<<(std::ofstream &out, const Employee &e);

    friend std::ifstream &operator>>(std::ifstream &in, Employee &e);

    virtual void print(std::ofstream &out) const;

    virtual void print(std::ostream &out) const;

    virtual void scan(std::istream &in);

    virtual void scan(std::ifstream &in);

    virtual ~Employee();

protected:
    std::string name{""};
    int32_t _base_salary{};
};

class Developer : public Employee {
public:
    int salary() const override;

    void print(std::ostream &out) const override;

    void print(std::ofstream &out) const override;

    void scan(std::istream &in) override;

    void scan(std::ifstream &in) override;

private:
    bool _has_bonus{};
};

class SalesManager : public Employee {
public:
    int salary() const override;

    void print(std::ostream &out) const override;

    void print(std::ofstream &out) const override;

    void scan(std::istream &in) override;

    void scan(std::ifstream &in) override;

private:
    int32_t _sold_nm{}, _price{};
};

class EmployeesArray {
public:
    void add(Employee *e);

    int total_salary() const;

    friend std::ostream &operator<<(std::ostream &out, const EmployeesArray &e_array);

    friend std::ofstream &operator<<(std::ofstream &out, const EmployeesArray &e_array);

    friend std::ifstream &operator>>(std::ifstream &in, EmployeesArray &e_array);

    ~EmployeesArray();

private:
    std::vector<Employee *> _employees;
};

#endif
