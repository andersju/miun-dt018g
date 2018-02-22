/**
 * @file    sort.cpp
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Funktioner för sortering av personer
 */
#include "sort.h"
#include "constants.h"
#include "utils.h"

#include <algorithm>
#include <iostream>
#include <random>

/*
 * Utför angiven sortering av vector
 *
 * @param persons Vector att sortera
 * @param sorttype Typ av sortering
 */
void performSort(std::vector<Person>& persons, SortType sorttype) {
  std::string message;

  switch (sorttype) {
  case SORT_BY_NAME:
    message = "Sorting by surname+first name (ascending).";
    std::sort(persons.begin(), persons.end(), [](const Person& a, const Person& b) {
      // Skapar en sträng på formen "<efternamn> <förnamn>", gemen, för att
      // sorteringen ska bli rätt
      std::string a_full = a.getLastName() + " " + a.getFirstName();
      std::string b_full = b.getLastName() + " " + b.getFirstName();
      stringToLower(a_full);
      stringToLower(b_full);
      return a_full < b_full;
    });
    break;
  case SORT_BY_SIGNATURE:
    message = "Sorting by signature (ascending).";
    std::sort(persons.begin(), persons.end(),
              [](const Person& a, const Person& b) { return a.getSignature() < b.getSignature(); });
    break;
  case SORT_BY_HEIGHT:
    message = "Sorting by height (descending).";
    std::sort(persons.begin(), persons.end(),
              [](const Person& a, const Person& b) { return a.getHeight() > b.getHeight(); });
    break;
  default:
    break;
  }

  std::cout << message << std::endl;
}

/*
 * Blandar om vectorn i slumpmässig ordning
 *
 * @param persons Vector att slumpa ordningen för
 */
void randomize(std::vector<Person>& persons) {
  auto rng = std::default_random_engine{};
  std::shuffle(std::begin(persons), std::end(persons), rng);

  std::cout << "Randomizing order in list." << std::endl;
}
