#ifndef CHAIN_DROB_H
#define CHAIN_DROB_H

long long euclidExtended(long long A, long long B, long long& x, long long& y);

// Построение цепной дроби для A/B
void printContinuedFraction(long long A, long long B);

// Решение диофантова уравнения A*x + B*y = C
void solveDiophantine(long long A, long long B, long long C);

#endif