#include "Vector.h"
#include <fstream>
#include <iostream>
#include <utility>

int main() {
    // подрубаем русский язык чтобы не было кракозябр
    setlocale(LC_ALL, "Russian");

    // открываем файлы
    std::ifstream fin("C:\\Users\\forti\\OneDrive\\Desktop\\input.txt");
    std::ofstream fout("output.txt");

    if (!fin.is_open()) {
        std::cerr << "Не открылся input.txt\n";
        return 1;
    }

    // создаем пустой вектор и читаем в него данные из файла
    Vector v1;
    fin >> v1;
    std::cout << "v1 = " << v1 << "\n";

    // читаем массив такой же длины как вектор
    double* arr = new double[v1.size()];
    for (int i = 0; i < v1.size(); ++i) {
        fin >> arr[i];
    }

    std::cout << "arr = ";
    for (int i = 0; i < v1.size(); ++i) std::cout << arr[i] << " ";
    std::cout << "\n";

    // ВОТ ТУТ ПРОВЕРЯЕМ МОЮ ОПЕРАЦИЮ
    // складываем массив и вектор
    Vector v2 = arr + v1;
    std::cout << "Результат arr + v1 = " << v2 << "\n";
    fout << "Результат: " << v2 << "\n"; // и в файл пишем

    // проверяем квадратные скобки
    std::cout << "v2[0] = " << v2[0] << "\n";

    //  разницу копирования и перемещения
    std::cout << "\n--- Тесты копирования и перемещения ---\n";

    Vector v3 = v1; // тут сработает конструктор копирования
    std::cout << "v3 (копия v1) = " << v3 << "\n";

    Vector v4 = std::move(v3); // тут сработает конструктор перемещения
    std::cout << "v4 (забрал у v3) = " << v4 << "\n";

    Vector v5; // пустой
    v5 = v1; // сработает присваивание с копированием

    Vector v6;
    v6 = std::move(v5); // присваивание с перемещением

    // проверка что v5 реально опустел после того как у него забрали данные
    std::cout << "v5 после move: n=" << v5.size() << "\n";
    std::cout << "v6 = " << v6 << "\n";

    delete[] arr; // не забываем почистить обычный массив
    std::cout << "\nВсё готово, результат в output.txt\n";
    return 0;
}
