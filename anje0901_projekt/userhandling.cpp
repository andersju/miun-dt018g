/**
 * @file    userhandling.cpp
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Funktioner för tillägg, borttagning och utskrift av personer
 */
#include "userhandling.h"
#include "constants.h"
#include "search.h"
#include "utils.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

/*
 * Lägger till en person i vectorn
 *
 * @param persons Vector att lägga till i
 */
void addPerson(std::vector<Person>& persons) {
  printFunctionHeader("Add person");

  // Ber om sträng från användaren och rensar bort eventuell förekomst av DELIM
  std::string tmpFirstName = getStringFromInput("Enter first name: ");
  tmpFirstName.erase(std::remove(tmpFirstName.begin(), tmpFirstName.end(), DELIM),
                     tmpFirstName.end());

  std::string tmpLastName = getStringFromInput("Enter last name: ");
  tmpLastName.erase(std::remove(tmpLastName.begin(), tmpLastName.end(), DELIM), tmpLastName.end());

  // Avrundar flyttal till två decimaler
  double tmpHeight = std::floor(getDoubleFromInput("Enter height (e.g. 1.85): ") * 100 + 0.5) / 100;

  // Skapar första delen av signaturen (xxxyyy)
  std::string partialSignature = nameToSignature(tmpFirstName) + nameToSignature(tmpLastName);

  // Kollar om personen är unik
  std::string tmpSignature;
  if (isPersonUnique(persons, tmpFirstName, tmpLastName, tmpHeight)) {
    bool hasUniqueSignature = false;

    // Personen är unik; försöker nu få fram en unik signatur. En viss xxxyyy
    // får förekomma max 100 gånger, så alla från 00 och uppåt testas tills
    // en unik hittats
    for (int i = 0; i < 100; ++i) {
      std::string signatureToCheck =
          partialSignature + std::string(2 - std::to_string(i).length(), '0') + std::to_string(i);

      // Kollar om signaturen är unik
      if (searchSignature(persons, signatureToCheck) == std::end(persons)) {
        tmpSignature = signatureToCheck;
        hasUniqueSignature = true;
        break;
      }
    }

    // Signaturen är unik, så personen läggs till i vectorn
    if (hasUniqueSignature) {
      Person p = {tmpFirstName, tmpLastName, tmpSignature, tmpHeight};
      persons.push_back(p);
      std::cout << "\nAdded person with signature " << tmpSignature << " to list." << std::endl;
    } else {
      std::cout << "\nNo more serial numbers available. Sorry!" << std::endl;
    }
  } else {
    while (true) {
      std::cout
          << "\nThis combination firstname+surname+height already exists.\nTry again? (y/n): ";
      std::string input;
      std::getline(std::cin, input);

      if (input == "y") {
        clearScreen();
        addPerson(persons);
        break;
      } else if (input == "n") {
        break;
      }
    }
  }
}

/*
 * Tar bort person från vector
 *
 * @param persons Vector att ta bort från
 */
void removePerson(std::vector<Person>& persons) {
  printFunctionHeader("Remove person");
  std::cout << "Enter signature to remove: ";
  std::string signatureToRemove;
  std::getline(std::cin, signatureToRemove);

  // Söker efter angiven signatur
  auto result = searchSignature(persons, signatureToRemove);

  // Skriver ut resultatet om sökningen gav en träff
  if (result != std::end(persons)) {
    std::cout << result->getFirstName() + " " + result->getLastName() << " ("
              << result->getSignature() << ") will now be removed." << std::endl;
    persons.erase(result);
  } else {
    std::cout << "Person not found." << std::endl;
  }
}

/*
 * Kollar huruvida angiven kombination förnamn+efternamn+längd är unik
 *
 * @param persons Vector att kolla i
 * @param firstName Förnamn
 * @param lastName Efternamn
 * @param height Längd
 * @return Sant om personen är unik
 */
bool isPersonUnique(const std::vector<Person>& persons, std::string firstName, std::string lastName,
                    double height) {
  // Se till att allt är gement för att kunna jämföra korrekt
  stringToLower(firstName);
  stringToLower(lastName);

  std::string tmpFirstName, tmpLastName;
  // Går igenom varje person i vectorn och jämför förnamn/efternamn/längd
  // med angivet dito
  for (auto& e : persons) {
    tmpFirstName = e.getFirstName();
    tmpLastName = e.getLastName();

    stringToLower(tmpFirstName);
    stringToLower(tmpLastName);

    if (tmpFirstName == firstName && tmpLastName == lastName && e.getHeight() == height) {
      return false;
    }
  }
  return true;
}
