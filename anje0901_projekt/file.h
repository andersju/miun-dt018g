/**
 * @file    file.h
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Funktionsprototyper för filhantering och kryptering
 */
#ifndef PROJEKTUPPGIFT_FILE_H
#define PROJEKTUPPGIFT_FILE_H

#include "constants.h"

#include <vector>

enum CryptType { ENCRYPT, DECRYPT };

char rotEncrypt(char character, const int rotation);
char rotDecrypt(char character, const int rotation);
std::string rotateString(std::string str, CryptType crypttype, int key);
void saveToFile(const std::vector<Person>& persons, std::string& currentFileName,
                int& encryptionKey);
void readFromFile(std::vector<Person>& persons, std::string& currentFileName, int& encryptionKey);
std::tuple<std::string, int> getFileNameAndKeyFromInput(const std::string& currentFileName,
                                                        const int& currentEncryptionKey);

#endif
