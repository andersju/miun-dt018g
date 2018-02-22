/**
 * @file    utils.cpp
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Diverse små hjälpfunktioner
 */
#include "utils.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
#include <sstream>
#include <string>

/*
 * Ber om och hämtar sträng från användaren
 *
 * @param messageString Dialogtext att visa före input
 * @param acceptEmpty Huruvida tom sträng ska accepteras som input
 * @return Inmatad sträng
 */
std::string getStringFromInput(const std::string& messageString, bool acceptEmpty) {
  while (true) {
    std::string inputString;
    std::cout << messageString;
    std::getline(std::cin, inputString);

    if (!inputString.empty() || acceptEmpty) {
      return inputString;
    }
  }
}

/*
 * Ber om och hämtar heltal från användaren
 *
 * @param messageString Dialogtext att visa före input
 * @param acceptEmpty Acceptera tomt input (returnerar då 0)
 * @param checkRange Huruvida input måste vara inom ett visst intervall
 * @param validFrom Minsta accepterat värde (om checkRange är sant)
 * @param validTo Högsta accepterat värde (om checkRange är sant)
 * @return Inmatat heltal
 */
int getIntFromInput(const std::string& messageString, bool acceptEmpty, bool checkRange,
                    int validFrom, int validTo) {
  int result = 0;

  while (true) {
    std::string inputStr;
    std::cout << messageString;
    std::getline(std::cin, inputStr);

    if (!inputStr.empty()) {
      std::istringstream iss(inputStr);
      if (iss >> result) {
        if (!checkRange || (result >= validFrom && result <= validTo)) {
          return result;
        }
      }
    } else if (acceptEmpty) {
      return -1;
    }
  }
}

/*
 * Ber om och hämtar flyttal från användaren
 *
 * @param messageString Dialogtext att visa före input
 * @return Inmatat decimaltal
 */
double getDoubleFromInput(const std::string& messageString) {
  double result = 0;

  while (true) {
    std::string inputStr;
    std::cout << messageString;
    std::getline(std::cin, inputStr);

    if (!inputStr.empty()) {
      std::istringstream iss(inputStr);
      if (iss >> std::fixed >> std::setprecision(1) >> result) {
        return result;
      }
    }
  }
}

/*
 * Gör sträng gemen
 *
 * @param string Sträng att göra gemen
 */
void stringToLower(std::string& string) {
  std::transform(string.begin(), string.end(), string.begin(), ::tolower);
}

/*
 * Konstruerar partiell signatur (utan löpnummer) utifrån förnamn och efternamn
 *
 * @param name Namn att göra signatur av
 * @return Partiell signatur
 */
std::string nameToSignature(std::string name) {
  // Ser till att namnet strippas från mellanslag samt görs gement
  name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
  stringToLower(name);

  if (name.length() >= 3) {
    return name.substr(0, 3);
  } else {
    // Fyller ut med lämpligt antal x om namnet är kortare än tre tecken
    return name.append(3 - name.length(), 'x');
  }
}

/*
 * Pausar programmet
 */
void pauseProgram() {
  std::cout << "\nPress Enter to continue.";
  std::string str;
  std::getline(std::cin, str);
}

/*
 * Rensar skärmen
 */
void clearScreen() {
// Det finns inget standardsätt att rensa skärmen, så försök att göra det
// minst dåliga alternativet beroende på plattform.
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
  std::cout << "\033[2J\033[1;1H" << std::endl;
#elif _WIN32
  system("cls");
#else
  std::cout << std::string(100, '\n') << std::endl;
#endif
}

/*
 * Skriver ut funktionsrubrik
 *
 * @param title Titel att skriva ut
 */
void printFunctionHeader(const std::string& title) {
  std::string titleString = "# " + title + " #";
  std::string border = std::string(titleString.length(), '#');
  std::cout << border << "\n" << titleString << "\n" << border << "\n" << std::endl;
}
