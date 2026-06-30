#include <iostream>
#include "inverse.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    long long c, m;

    cout << "НАХОЖДЕНИЕ ОБРАТНОГО ЭЛЕМЕНТА" << endl;
    cout << "Введите c: "; cin >> c;
    cout << "Введите m: "; cin >> m;
    cout << endl;

    inverseMod(c, m);
    return 0;
}