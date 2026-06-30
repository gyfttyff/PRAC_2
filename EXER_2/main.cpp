#include <iostream>
#include "euclid.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    long long a, b;

    cout << "РАСШИРЕННЫЙ АЛГОРИТМ ЕВКЛИДА" << endl;
    cout << "Вычисление c*d mod m = 1" << endl;
    cout << "Введите c: "; cin >> a;
    cout << "Введите m: "; cin >> b;
    cout << endl;

    euclidExtended(a, b);
    return 0;
}