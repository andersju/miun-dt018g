/**
 * @file    search.cpp
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Funktioner för sökning av personer
 */
#include "search.h"
#include "constants.h"
#include "menu.h"
#include "print.h"
#include "userhandling.h"
#include "utils.h"

#include <algorithm>
#include <iostream>
#include <string>

/*
 * Söker i vector efter angiven signatur
 *
 * @param persons Vector att söka i
 * @param signatureToSearch Signatur att söka efter
 * @return Iterator till elementet om det hittades, annars till last
 */
std::vector<Person>::const_iterator searchSignature(const std::vector<Person>& persons,
                                                    const std::string& signatureToSearch) {
  return std::find_if(std::begin(persons), std::end(persons),
                      [signatureToSearch](const Person& person) {
                        return person.getSignature() == signatureToSearch;
                      });
}

/*
 * Visar dialog för sökning efter signatur och utför sökningen
 *
 * @param persons Vector att söka i
 */
void performSearch(const std::vector<Person>& persons) {
  printFunctionHeader("Search signature");

  std::cout << "Enter signature to search for: ";
  std::string signatureToSearch;
  std::getline(std::cin, signatureToSearch);

  auto result = searchSignature(persons, signatureToSearch);

  if (result != std::end(persons)) {
    std::cout << "\nSignature found:\n" << std::endl;
    printResultsTableHeader(persons, false);
    printPerson(1, *result);
  } else {
    std::cout << "Signature " << signatureToSearch << " not found." << std::endl;
  }
}
