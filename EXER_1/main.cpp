#include <iostream>
#include "fermat.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    long long a, x, p;

    cout << "Введите основание a: ";
    cin >> a;
    cout << "Введите степень x: ";
    cin >> x;
    cout << "Введите модуль p: ";
    cin >> p;

    cout << "\nВычисляем " << a << "^" << x << " mod " << p << "\n\n";

    long long r1 = modFermat(a, x, p);
    long long r2 = modBinary(a, x, p);

    cout << "Сравнение результатов:" << endl;
    cout << "Метод 1 (Ферма): " << r1 << endl;
    cout << "Метод 2 (бинарный): " << r2 << endl;

    if (r1 == r2)
        cout << "Результаты совпадают!" << endl;
    else
        cout << "Результаты НЕ совпадают!" << endl;

    return 0;
}