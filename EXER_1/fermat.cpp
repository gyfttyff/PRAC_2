#include "fermat.h"
#include <iostream>
using namespace std;

// Проверка простоты перебором делителей до sqrt(n)
bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// через теорему Ферма
long long modFermat(long long a, long long x, long long p) {
    cout << "=== Метод 1: Теорема Ферма ===" << endl;
    a = a % p;

    if (isPrime(p) && a != 0) {
        cout << "Модуль p=" << p << " - простое число, a!=0" << endl;
        cout << "Применяем теорему Ферма: a^(p-1) = 1 (mod p)" << endl;
        long long newX = x % (p - 1); // a^x = a^(x mod(p-1)) mod(p)
        cout << "Сокращаем степень: " << x << " mod " << (p - 1)
             << " = " << newX << endl;
        x = newX;
    } else {
        cout << "Теорема Ферма неприменима (модуль не простой или a=0)" << endl;
    }

    // Простое циклическое возведение в степень
    long long result = 1;
    for (long long i = 0; i < x; i++) {
        result = (result * a) % p;
        cout << "Шаг " << i + 1 << ": result = " << result << endl;
    }
    cout << "Итог метода 1: " << result << endl << endl;
    return result;
}

// бинарное возведение в степень
long long modBinary(long long a, long long x, long long p) {
    cout << "=== Метод 2: Бинарный алгоритм ===" << endl;
    a = a % p;
    long long result = 1;

    // Выводим двоичное представление степени
    cout << "Степень " << x << " в двоичном виде: ";
    long long temp = x;
    string bits = "";
    while (temp > 0) {
        bits = (char)('0' + (temp % 2)) + bits;
        temp /= 2;
    }
    cout << bits << endl;

    int step = 1;
    while (x > 0) {
        if (x % 2 == 1) {
            result = (result * a) % p;
            cout << "Шаг " << step << ": бит=1, result = " << result << endl;
        } else {
            cout << "Шаг " << step << ": бит=0, пропуск" << endl;
        }
        a = (a * a) % p; // a^x = a^2^x * a^2^(x-1) * a^2^(x-2) ...
        x = x / 2;
        step++;
    }
    cout << "Итог метода 2: " << result << endl << endl;
    return result;
}