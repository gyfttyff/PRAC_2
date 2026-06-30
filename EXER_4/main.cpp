#include <iostream>
#include <string>
#include "rsa.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    
    cout << "КРИПТОСИСТЕМА RSA" << endl;
    cout << "==============================" << endl << endl;
    
    // Вводим простые числа
    long long p, q;
    cout << "Введите простое число p (например, 61): "; cin >> p;
    cout << "Введите простое число q (например, 53): "; cin >> q;
    
    long long e, d, n;
    
    generateKeys(p, q, e, d, n);
    

    if (n == 0) {
        cout << "Ошибка генерации ключей!" << endl;
        return 1;
    }
    
    // ТЕПЕРЬ В ПЕРЕМЕННЫХ e, d, n ЛЕЖАТ КЛЮЧИ!
    
    
    int choice;
    cout << "\nВыберите режим:" << endl;
    cout << "1 - Шифрование строки" << endl;
    cout << "2 - Шифрование файла" << endl;
    cout << "Ваш выбор: "; cin >> choice;
    
    if (choice == 1) {
        // Режим шифрования строки
        cin.ignore();
        string text;
        cout << "\nВведите строку: "; getline(cin, text);
        
        // Шифруем строку — передаём e и n (открытый ключ)
        vector<long long> cipher = encryptString(text, e, n);
        
        // Расшифровываем — передаём d и n (закрытый ключ)
        string recovered = decryptString(cipher, d, n);
        
        cout << "\nИтог: " << recovered << endl;
        cout << "Совпадает с исходным: " 
             << (recovered == text ? "ДА" : "НЕТ") << endl;
    } 
    else if (choice == 2) {
        // Режим шифрования файла
        string inName;
        cout << "\nВходной файл: "; cin >> inName;
        
        // Формируем имена выходных файлов
        string encName = "enc_" + inName;
        string decName = "dec_" + inName;
        
        // Шифруем файл — передаём e и n (открытый ключ)
        if (encryptFile(inName, encName, e, n)) {
            // Расшифровываем файл — передаём d и n (закрытый ключ)
            decryptFile(encName, decName, d, n);
            
            cout << "Зашифрованный файл: " << encName << endl;
            cout << "Расшифрованный файл: " << decName << endl;
        }
    }
    
    return 0;
}