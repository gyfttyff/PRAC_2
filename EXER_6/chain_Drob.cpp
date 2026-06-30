#include "chain_Drob.h"
#include <iostream>
#include <vector>

using namespace std;


// A*x + B*y = НОД(A,B)

long long euclidExtended(long long A, long long B, long long& x, long long& y) {
    vector<long long> r, u, v, q;
    cout << "найдем НОД(" << A << " , " << B << ")" << endl << endl;
    
    r.push_back(A);
    r.push_back(B);

    long long q1 = A / B;

    u.push_back(0);
    v.push_back(1);
    u.push_back(1);
    v.push_back(-q1);
    q.push_back(0);
    q.push_back(q1);

    cout << "r - остаток от деления; u - коэффициент при " << A 
         << "; v - коэффициент при " << B << "; q - целое частное" << endl << endl;
    cout << "Начальные значения:" << endl;
    cout << "u: " << u[0] << ", " << u[1] << endl;
    cout << "v: " << v[0] << ", " << v[1] << endl;
    cout << "q: " << q[0] << ", " << q[1] << endl << endl;

    int k = 2;

    while (r[k - 1] != 0) {
        long long qk = r[k - 2] / r[k - 1];
        q.push_back(qk);

        long long rk = r[k - 2] % r[k - 1];
        r.push_back(rk);

        long long uk = u[k - 2] - u[k - 1] * qk;
        long long vk = v[k - 2] - v[k - 1] * qk;

        u.push_back(uk);
        v.push_back(vk);

        cout << "Итерация " << k - 1 << ":" << endl;
        cout << "  q" << k << " = " << qk << endl;
        cout << "  r" << k << " = " << rk << endl;
        cout << "  u" << k << " = " << uk << endl;
        cout << "  v" << k << " = " << vk << endl;
        cout << A << " * " << vk << " + " << B << " * " << uk 
             << " = " << rk << endl << endl;

        k++;
    }
    
    cout << "r\tu\tv\tq" << endl;

    for (int i = 0; i < k; i++) {
        if (r[i] == 0) {
            cout << "0\nНОД: " << r[i - 1] << endl;
            break;
        }
        cout << r[i] << "\t" << u[i] << "\t" << v[i] << "\t" << q[i] << endl;
    }

    cout << "\nНОД: " << r[k - 2] << endl << endl;
    x = v[k - 2];
    y = u[k - 2];
    return r[k - 2];
}


// Построение цепной дроби для A/B

void printContinuedFraction(long long A, long long B) {
    cout << "\t Цепная дробь для " << A << "/" << B << endl;
    vector<long long> cf;
    long long a = A, b = B;
    
    // Алгоритм Евклида для получения неполных частных
    while (b != 0) {
        long long part = a / b;
        cf.push_back(part);
        cout << a << " / " << b << " = " << part 
             << " (остаток " << a % b << ")" << endl;
        long long temp = a % b;
        a = b;
        b = temp;
    }
    
    // Вывод цепной дроби в формате [a0; a1, a2, ...]
    cout << "Цепная дробь: [";
    for (size_t i = 0; i < cf.size(); i++) {
        if (i == 0)
            cout << cf[i];
        else
            cout << "; " << cf[i];
    }
    cout << "]" << endl;
}


void solveDiophantine(long long A, long long B, long long C) {
    cout << "Решение уравнения: ";
    cout << A << "x + " << B << "y = " << C << endl;
    printContinuedFraction(A, B);

    long long x0, y0;
    // pₖ*qₖ₋₁ - pₖ₋₁*qₖ = ±1 для подходящих соседних дробей
    long long gcd = euclidExtended(A, B, x0, y0);

    cout << "НОД(" << A << ", " << B << ") = ";
    cout << gcd << endl;

    // Должен делится на остаток иначе не будет решения
    if (C % gcd != 0) {
        cout << "Решений нет!" << endl;
        return;
    }
    //A*(x₀*factor) + B*(y₀*factor) = НОД * (C/НОД) = C
    long long factor = C / gcd;
    x0 *= factor;
    y0 *= factor;

    // Вывод и проверка частного решения 
    cout << "Частное решение:" << endl;
    cout << "x0 = " << x0 << ", y0 = " << y0 << endl;
    cout << "Проверка: ";
    cout << A << "*" << x0 << " + ";
    cout << B << "*" << y0 << " = ";
    cout << (A * x0 + B * y0) << endl;

    // Вычисление шагов для общего решения 
    long long x_step = B / gcd; // x_step = B / НОД — на сколько увеличивается x при t=1
    long long y_step = A / gcd; // y_step = A / НОД — на сколько уменьшается y при t=1


    // Вывод формулы общего решения 
    cout << "Общее решение:" << endl;
    cout << "x = " << x0 << " + ";
    cout << x_step << " * t" << endl;
    cout << "y = " << y0 << " - ";
    cout << y_step << "  *  t" << endl;

    // Демонстрация примеров для t от -2 до 2 потому что t всё равно сокращается 
    cout << "Примеры решений:" << endl;
    for (int t = -2; t <= 2; t++) {
        long long x = x0 + x_step * t;
        long long y = y0 - y_step * t;
        cout << "t = " << t;
        cout << ": x = " << x;
        cout << ", y = " << y;
        cout << " -> ";
        cout << A << "*" << x;
        cout << " + ";
        cout << B << "*" << y;
        cout << " = ";
        cout << (A * x + B * y) << endl;
    }
}