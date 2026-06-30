#include "rsa.h"
#include "math.h"
#include <iostream>
#include <fstream>

using namespace std;

void generateKeys(long long p, long long q, long long &e, long long &d, long long &n) {
    cout << "ГЕНЕРАЦИЯ КЛЮЧЕЙ RSA" << endl;

    if (!isPrime(p) || !isPrime(q)) {
        cout << "ОШИБКА: p и q должны быть простыми!" << endl;
        n = 0; return;
    }

   
    n = p * q;
    cout << "n = p * q = " << n << endl;

    // Вычисление функции Эйлера 
    long long fi = (p - 1) * (q - 1);
    cout << "fi(n) = (p-1)*(q-1) = " << fi << endl;

    // Выбор открытой экспоненты e
    e = 65537; // Стандартное значение
    if (e >= fi) e = 3; // Если fi слишком маленькая
    
    // Ищем e, взаимно простое с fi
    while (gcd(e, fi) != 1) {
        e += 2; 
    }
    cout << "e (открытая экспонента) = " << e << endl;

    // Вычисление закрытой экспоненты d
    // d = e^(-1) mod fi. 
    d = inverseMod(fi, e);
    cout << "d (закрытая экспонента) = " << d << endl;

    cout << "Открытый ключ: (e=" << e << ", n=" << n << ")" << endl;
    cout << "Закрытый ключ: (d=" << d << ", n=" << n << ")\n" << endl;
}

vector<long long> encryptString(const string& text, long long e, long long n) {
    vector<long long> cipher;
    cout << "ШИФРОВАНИЕ СТРОКИ " << endl;
    for (size_t i = 0; i < text.size(); i++) {
        long long m = (unsigned char)text[i]; // ASCII код символа
        long long c = modPow(m, e, n);        // c = m^e mod n
        cipher.push_back(c);
        cout << "Символ '" << text[i] << "' (" << m << ") -> " << c << endl;
    }
    return cipher;
}

string decryptString(const vector<long long>& cipher, long long d, long long n) {
    string text = "";
    cout << "\n=== РАСШИФРОВАНИЕ СТРОКИ ===" << endl;
    for (size_t i = 0; i < cipher.size(); i++) {
        long long m = modPow(cipher[i], d, n); // m = c^d mod n
        text += (char)m;
        cout << "Блок " << cipher[i] << " -> " << m << " ('" << (char)m << "')" << endl;
    }
    return text;
}

bool encryptFile(const string& file, const string& out_file, long long e, long long n) {
    ifstream fin(file, ios::binary);
    if (!fin) { cout << "Файл не найден!" << endl; return false; }
    ofstream fout(out_file, ios::binary);

    // Записываем размер файла в начало, чтобы при расшифровке знать, сколько байт читать
    fin.seekg(0, ios::end);
    long long size = fin.tellg();
    fin.seekg(0, ios::beg);
    fout.write((char*)&size, sizeof(size)); // Записываем размер файла в начало зашифрованного файла.

    cout << "=== ШИФРОВАНИЕ ФАЙЛА ===" << endl;
    int count = 0;
    while (count < size) {
        unsigned char byte;
        fin.read((char*)&byte, 1); // читаем ровно 1 байт из файла в переменную byte
        long long c = modPow(byte, e, n);
        fout.write((char*)&c, sizeof(c)); // Пишем 8 байт вместо 1
        count++;
    }
    cout << "Зашифровано байт: " << count << "\n" << endl;
    return true;
}

bool decryptFile(const string& file, const string& out_file, long long d, long long n) {
    ifstream fin(file, ios::binary);
    if (!fin) { cout << "Файл не найден!" << endl; return false; }
    ofstream fout(out_file, ios::binary);

    long long size;
    fin.read((char*)&size, sizeof(size)); // Читаем первые 8 байт из зашифрованного файла 

    cout << "=== РАСШИФРОВАНИЕ ФАЙЛА ===" << endl;
    int count = 0;
    while (count < size) {
        long long c;
        fin.read((char*)&c, sizeof(c));
        long long m = modPow(c, d, n);
        unsigned char byte = (unsigned char)m; // превращаем в 1 байт
        fout.write((char*)&byte, 1); // Пишем 1 байт
        count++;
    }
    cout << "Расшифровано байт: " << count << "\n" << endl;
    return true;
}