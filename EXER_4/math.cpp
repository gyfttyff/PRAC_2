#include "math.h"
#include <iostream>
#include <vector>
using namespace std;

// Проверка числа на простоту
bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Алгоритм Евклида для НОД
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


// Бинарное возведение в степень по модулю
long long modPow(long long a, long long x, long long p) {
    long long result = 1;
    a = a % p;
    while (x > 0) {
        if (x % 2 == 1) result = (result * a) % p;
        x = x / 2;
        a = (a * a) % p;  // a^x = a^2^x * a^2^(x-1) * a^2^(x-2) ...
    }
    return result;
}

// ищем обратное к b по модулю a
long long inverseMod(long long a, long long b) {
    vector<long long> r, u, v, q;
    cout << "Поиск обратного элемента: НОД(" << a << ", " << b << ")" << endl << endl;
    r.push_back(a);
    r.push_back(b);
    long long q1 = a / b;
    u.push_back(0);
    v.push_back(1);
    u.push_back(1);
    v.push_back(-q1);
    q.push_back(0);
    q.push_back(q1);
    /*cout << "r - остаток; u - коэффициент при " << a 
         << "; v - коэффициент при " << b 
         << "; q - частное" << endl << endl;
    cout << "Начальные значения:" << endl;
    cout << "u: " << u[0] << ", " << u[1] << endl;
    cout << "v: " << v[0] << ", " << v[1] << endl;
    cout << "q: " << q[0] << ", " << q[1] << endl << endl;*/
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
        /*cout << "Итерация " << k - 1 << ":" << endl;
        cout << "  q" << k << " = " << qk << endl;
        cout << "  r" << k << " = " << rk << endl;
        cout << "  u" << k << " = " << uk << endl;
        cout << "  v" << k << " = " << vk << endl;
        cout << a << " * " << vk << " + " << b << " * " << uk 
             << " = " << rk << endl << endl;*/
        k++;
    }
    //cout << "r\tu\tv\tq" << endl;
    for (int i = 0; i < k; i++) {
        //cout << r[i] << "\t" << u[i] << "\t" << v[i] << "\t" << q[i] << endl;
    }
    long long gcd_val = r[k - 2];
    //cout << "\nНОД: " << gcd_val << endl << endl;
    if (gcd_val != 1) {
        cout << "Обратное число не может быть найдено: НОД != 1" << endl;
        return -1;
    }
    long long inverse = u[k - 2];
    //cout << "Обратное число " << endl << b << " ^ -1 mod " << a 
         //<< " = " << inverse << endl;
    long long check = (b * inverse) % a;
    if (check < 0) check += a;
    //cout << "Проверка " << b << " * " << inverse << " mod " << a 
        // << " = " << check << endl;
    if (inverse < 0) {
        inverse = inverse + a;
        //cout << "  приводим к положительному: " << inverse << endl;
    }
    //cout << "Итоговый ответ: " << b << "^(-1) mod " << a 
        // << " = " << inverse << endl;
    return inverse;
}