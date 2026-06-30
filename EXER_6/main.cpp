#include <iostream>
#include "chain_Drob.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    cout << "Вариант 4: 237a + 44b = 1" << endl << endl;
    
    solveDiophantine(237, 44, 1);
    
    return 0;
}