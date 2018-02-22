/**
 * @file    print.h
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Funktionsprototyper för utskrifter
 */
#ifndef PROJEKTUPPGIFT_PRINT_H
#define PROJEKTUPPGIFT_PRINT_H

#include "constants.h"

#include <vector>

void showPersons(const std::vector<Person>& persons);
void printPerson(const size_t& i, const Person& person);
void printResultsTableHeader(const std::vector<Person>& persons, bool showInfo = true);

#endif
