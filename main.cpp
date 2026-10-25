#include "Vector.h"
#include <iostream>
#include <utility>

// пустой вектор
Vector::Vector() : p(nullptr), n(0) {
    // просто зануляем всё, памяти пока нет
}

// создаем просто размера n, заполнится нулями
Vector::Vector(int n) : p(new double[n]()), n(n) {
    // тут new double[n]() со скобками чтобы сразу нулями забилось
}

// создаем из готового массива
Vector::Vector(const double* arr, int n) : p(new double[n]), n(n) {
    for (int i = 0; i < n; ++i) {
        p[i] = arr[i]; // переписываем элементы
    }
}

// копирование (когда пишем Vector v2 = v1)
Vector::Vector(const Vector& other) : p(new double[other.n]), n(other.n) {
    for (int i = 0; i < n; ++i) {
        p[i] = other.p[i]; // выделяем новую память и копируем туда
    }
}

// перемещение (когда объект временный и сейчас умрет)
Vector::Vector(Vector&& other) noexcept : p(other.p), n(other.n) {
    // просто забираем указатель себе, копировать не надо, так быстрее
    other.p = nullptr; // а у старого зануляем чтобы он память не удалил
    other.n = 0;
}

// деструктор
Vector::~Vector() {
    delete[] p; // освобождаем память, иначе утечка
}

// оператор присваивания с копированием (v1 = v2)
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) { // проверка чтоб не присвоить самого себя
        delete[] p; // сначала чистим свою старую память
        n = other.n;
        p = new double[n]; // выделяем новую
        for (int i = 0; i < n; ++i) {
            p[i] = other.p[i]; // и копируем
        }
    }
    return *this; // возвращаем себя чтобы можно было a=b=c
}

// оператор присваивания с перемещением
Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] p; // чистим свое
        p = other.p; // забираем чужое
        n = other.n;
        other.p = nullptr; // у чужого зануляем
        other.n = 0;
    }
    return *this;
}

// обращение по индексу
double& Vector::operator[](int index) {
    return p[index]; // возвращаем ссылку чтобы можно было v[0] = 5 сделать
}

const double& Vector::operator[](int index) const {
    return p[index]; // для константных объектов
}

// вывод в консоль или файл
std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "n=" << v.n << ": ";
    for (int i = 0; i < v.n; ++i) {
        os << v.p[i] << " ";
    }
    return os; // возвращаем поток чтобы можно было cout << a << b
}

// чтение из файла
std::istream& operator>>(std::istream& is, Vector& v) {
    int n;
    is >> n; // читаем сколько чисел
    delete[] v.p; // старую память чистим
    v.n = n;
    v.p = new double[n]; // новую выделяем
    for (int i = 0; i < n; ++i) {
        is >> v.p[i]; // читаем сами числа
    }
    return is;
}

// ВОТ ТУТ МОЯ ОПЕРАЦИЯ (вариант 3)
// первый аргумент это массив, второй вектор, на выходе новый вектор
Vector operator+(const double* arr, const Vector& v) {
    Vector result(v.n); // создаем новый вектор ТАКОГО ЖЕ размера
    for (int i = 0; i < v.n; ++i) {
        result.p[i] = arr[i] + v.p[i]; // складываем элементы с одинаковыми индексами
    }
    return result; // возвращаем (тут перемещение сработает)
}

void Vector::print() const {
    std::cout << *this << "\n";
}
