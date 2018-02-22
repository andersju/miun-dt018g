/**
 * @file    userhandling.h
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Funktionsprototyper för användarhantering
 */
#ifndef PROJEKTUPPGIFT_USERHANDLING_H
#define PROJEKTUPPGIFT_USERHANDLING_H

#include "constants.h"
#include <vector>

void addPerson(std::vector<Person>& persons);
void removePerson(std::vector<Person>& persons);
bool isPersonUnique(const std::vector<Person>& persons, std::string firstName, std::string lastName,
                    double height);

#endif
