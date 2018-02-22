/**
 * @file    print.cpp
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Funktioner för utskrift av personer
 */
#include "print.h"
#include "constants.h"
#include "utils.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

/*
 * Visar tabellhuvudet
 */
void printResultsTableHeader(const std::vector<Person>& persons, bool showInfo) {
  if (showInfo) {
    std::cout << "***** NAME LIST *****" << std::endl;
    std::cout << "Number of persons in list: " << persons.size() << "\n" << std::endl;
  }
  std::cout << std::left << std::setw(5) << "Nr";
  std::cout << std::setw(10) << "Sign";
  std::cout << std::setw(28) << "Name";
  std::cout << "Length [m]" << std::endl;
}

/*
 * Skriver ut en person
 *
 * @param person Person att skriva ut
 */
void printPerson(const size_t& i, const Person& person) {
  std::cout << std::left << std::setw(5) << std::to_string(i + 1) + ".";
  std::cout << std::setw(10) << person.getSignature();
  std::cout << std::setw(30) << person.getFirstName() + " " + person.getLastName();
  std::cout << std::right << std::fixed << std::setprecision(2) << std::setw(5)
            << person.getHeight() << std::endl;
}

/*
 * Skriver ut alla personer i vectorn
 *
 * @param persons Vector att skriva ut
 */
void showPersons(const std::vector<Person>& persons) {
  printResultsTableHeader(persons);

  int numberPrinted = 0;
  int page = 0;
  for (size_t i = 0; i < persons.size(); ++i) {

    printPerson(i, persons[i]);
    ++numberPrinted;

    if ((numberPrinted % 20 == 0) && (persons.size() - i) > 0) {
      std::cout << "\nShowing records " << (numberPrinted - i) + page * 20 << "-" << numberPrinted
                << " of " << persons.size() << std::endl;
      std::cout << "\nPress Enter to see more records" << std::endl;
      std::string str;
      std::getline(std::cin, str);
      clearScreen();
      printResultsTableHeader(persons);
      ++page;
    }

    if (i + 1 == persons.size()) {
      std::cout << "\nShowing records " << (numberPrinted - i) + page * 20 << "-" << numberPrinted
                << " of " << persons.size() << std::endl;
    }
  }
}
