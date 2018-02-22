/**
 * @file    utils.h
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Funktionsprototyper för hjälpfunktioner
 */
#ifndef PROJEKTUPPGIFT_UTILS_H
#define PROJEKTUPPGIFT_UTILS_H

#include <string>

std::string getStringFromInput(const std::string& messageString, bool acceptEmpty = false);
int getIntFromInput(const std::string& messageString, bool acceptEmpty = false,
                    bool checkRange = false, int validFrom = 0, int validTo = 0);
double getDoubleFromInput(const std::string& messageString);
void stringToLower(std::string& string);
std::string nameToSignature(std::string name);
void pauseProgram();
void clearScreen();
void printFunctionHeader(const std::string& title);

#endif
