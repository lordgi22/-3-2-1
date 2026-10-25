#pragma once // чтоб этот файл не подключался дважды
#include <iostream>

class Vector {
private:
    double* p; // тут будет лежать наш массив с числами
    int n;     // а тут сколько этих чисел (размер)

public:
    // конструкторы
    Vector(); // пустой
    Vector(int n); // задаем только размер
    Vector(const double* arr, int n); // создаем из обычного массива
    Vector(const Vector& other); // копируем другой вектор
    Vector(Vector&& other) noexcept; // перемещаем (забираем данные)

    ~Vector(); // деструктор (чистит память)

    // перегрузка присваивания
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    // чтобы можно было писать v[0]
    double& operator[](int index);
    const double& operator[](int index) const;

    // перегрузка ввода вывода в файл/консоль (friend потому что cout это не наш класс)
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
    friend std::istream& operator>>(std::istream& is, Vector& v);

    // ВОТ ОНА МОЯ ОПЕРАЦИЯ ПО ВАРИАНТУ 3: массив + вектор
    // обязательно friend так как слева не объект класса а просто массив
    friend Vector operator+(const double* arr, const Vector& v);

    int size() const { return n; } // узнать размер
    void print() const;
};
