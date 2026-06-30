#include "inverse.h"
#include <iostream>
#include <vector>
using namespace std;

long long inverseMod(long long c, long long m) {
    vector<long long> r, u, v, q;

    cout << "Ищем обратное к " << c << " по модулю " << m << endl;
    cout << "Вычисляем НОД(" << m << ", " << c << ")" << endl << endl;

    r.push_back(m);
    r.push_back(c);
    long long q1 = m / c;

    u.push_back(0); v.push_back(1);
    u.push_back(1); v.push_back(-q1);
    q.push_back(0); q.push_back(q1);

    int k = 2;
    while (r[k - 1] != 0) {
        long long qk = r[k - 2] / r[k - 1];
        long long rk = r[k - 2] % r[k - 1];
        long long uk = u[k - 2] - u[k - 1] * qk;
        long long vk = v[k - 2] - v[k - 1] * qk;

        q.push_back(qk);
        r.push_back(rk);
        u.push_back(uk);
        v.push_back(vk);

        cout << "Итерация " << k - 1 << ": q=" << qk
             << ", r=" << rk << ", u=" << uk << ", v=" << vk << endl;
        k++;
    }

    cout << "\nИтоговая таблица:" << endl;
    cout << "r\tu\tv\tq" << endl;
    for (int i = 0; i < k; i++) {
        cout << r[i] << "\t" << u[i] << "\t" << v[i] << "\t" << q[i] << endl;
    }

    long long gcd = r[k - 2];
    cout << "\nНОД = " << gcd << endl;

    if (gcd != 1) {
        cout << "Обратного элемента НЕ СУЩЕСТВУЕТ (НОД != 1)" << endl;
        return -1;
    }

    // Коэффициент при c - это v[k-2]
    long long d = v[k - 2];
    cout << "Коэффициент при c: v = " << d << endl;

    if (d < 0) {
        d = d + m;
        cout << "Приводим к положительному: " << d << " + " << m << " = " << d << endl;
    }

    cout << "\nОтвет: " << c << "^(-1) mod " << m << " = " << d << endl;
    cout << "Проверка: " << c << " * " << d << " mod " << m
         << " = " << (c * d) % m << endl;

    return d;
}