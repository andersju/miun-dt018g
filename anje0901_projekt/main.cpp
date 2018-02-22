/**
 * @file    main.cpp
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Program för hantering av personregister
 *
 * Provat med GCC/G++ 7.2.0:
 * g++ -Wall -Wextra -Werror -Wpedantic -Wconversion -std=c++11 file.cpp \
 * main.cpp menu.cpp print.cpp search.cpp sort.cpp userhandling.cpp utils.cpp -o program
 * samt med Visual Studio 2017
 */
#include "constants.h"
#include "file.h"
#include "menu.h"
#include "print.h"
#include "search.h"
#include "sort.h"
#include "userhandling.h"
#include "utils.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

int main() {
  std::vector<Person> persons; // Vectorn som alla funktioner kommer att läsa och/eller modifiera
  std::string currentFileName; // Lagrar state för default-filnamn
  int encryptionKey = 0;       // Lagrar state för default-nyckel

  while (true) {
    // Be om input
    int choice = showMenuAndGetInput(MENUITEMS, persons);
    // Rensa skärmen
    clearScreen();

    switch (choice) {
    case 1:
      addPerson(persons);
      break;
    case 2:
      showPersons(persons);
      break;
    case 3:
      performSearch(persons);
      break;
    case 4:
      removePerson(persons);
      break;
    case 5:
      performSort(persons, SORT_BY_NAME);
      break;
    case 6:
      performSort(persons, SORT_BY_SIGNATURE);
      break;
    case 7:
      performSort(persons, SORT_BY_HEIGHT);
      break;
    case 8:
      randomize(persons);
      break;
    case 9:
      saveToFile(persons, currentFileName, encryptionKey);
      break;
    case 10:
      readFromFile(persons, currentFileName, encryptionKey);
      break;
    case 11:
      return 0;
    default:
      break;
    }

    pauseProgram();
    clearScreen();
  }
}
