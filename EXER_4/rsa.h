#ifndef RSA_H
#define RSA_H

#include <string>
#include <vector>


void generateKeys(long long p, long long q, 
                  long long &e, long long &d, long long &n);


std::vector<long long> encryptString(const std::string& text, 
                                      long long e, long long n);


std::string decryptString(const std::vector<long long>& cipher, 
                           long long d, long long n);


bool encryptFile(const std::string& file, const std::string& out_file, 
                  long long e, long long n);

bool decryptFile(const std::string& file, const std::string& out_file, 
                  long long d, long long n);

#endif