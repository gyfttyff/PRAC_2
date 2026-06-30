#include "euclid.h"
#include <iostream>
#include <vector>
using namespace std;

long long euclidExtended(long long a, long long b) {
    // Векторы для хранения r, u, v, q
    vector<long long> r, u, v, q;

    cout << "Вычисляем НОД(" << a << ", " << b << ")" << endl << endl;

    // Начальные значения
    r.push_back(a);
    r.push_back(b);

    long long q1 = a / b;

    u.push_back(0);   
    v.push_back(1);    
    u.push_back(1);    
    v.push_back(-q1);    
    q.push_back(0);    
    q.push_back(q1);   

    cout << "Начальные значения:" << endl;
    cout << "r: " << r[0] << ", " << r[1] << endl;
    cout << "u: " << u[0] << ", " << u[1] << endl;
    cout << "v: " << v[0] << ", " << v[1] << endl;
    cout << "q: " << q[0] << ", " << q[1] << endl << endl;

    int k = 2;

    // Основной цикл, пока остаток не станет 0
    while (r[k - 1] != 0) {
        long long qk = r[k - 2] / r[k - 1];
        long long rk = r[k - 2] % r[k - 1];
        long long uk = u[k - 2] - u[k - 1] * qk;
        long long vk = v[k - 2] - v[k - 1] * qk;

        q.push_back(qk);
        r.push_back(rk);
        u.push_back(uk);
        v.push_back(vk);

        cout << "Итерация " << k - 1 << ":" << endl;
        cout << "  q" << k << " = " << r[k-2] << " / " << r[k-1] << " = " << qk << endl;
        cout << "  r" << k << " = " << rk << endl;
        cout << "  u" << k << " = " << u[k-2] << " - " << u[k-1] << " * " << qk << " = " << uk << endl;
        cout << "  v" << k << " = " << v[k-2] << " - " << v[k-1] << " * " << qk << " = " << vk << endl;
        cout << "  Проверка: " << a << " * " << uk << " + " << b << " * " << vk
             << " = " << a * uk + b * vk << endl << endl;

        k++;
    }

    // Вывод итоговой таблицы
    cout << "r\tu\tv\tq" << endl;
    for (int i = 0; i < k; i++) {
        cout << r[i] << "\t" << u[i] << "\t" << v[i] << "\t" << q[i] << endl;
    }

    long long d = r[k - 2];
    cout << "\nНОД = " << d << endl;
    cout << "Коэффициенты: u = " << u[k - 2] << ", v = " << v[k - 2] << endl;
    cout << "Проверка: " << a << " * " << u[k-2] << " + " << b << " * " << v[k-2]
         << " = " << a * u[k-2] + b * v[k-2] << endl;

    return d;
}