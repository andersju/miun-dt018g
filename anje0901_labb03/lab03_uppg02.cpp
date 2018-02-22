/**
 * @file    lab03_uppg02.cpp
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2017-11-23
 * @version 1.0
 * @brief   Sortera tre namn.
 *
 * Testat med GCC/G++ 7.2.0 och `g++ -Wall -Wextra -Werror -pedantic -std=c++11`
 * samt med Visual Studio 2017
 */
#include <algorithm>
#include <clocale>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::string input, name, name2, name3;
  std::string name_orig, name2_orig, name3_orig;
  std::string firstname_tmp, lastname_tmp, orig_tmp;
  std::istringstream iss;

  std::setlocale(LC_ALL, "swedish");

  // Läs in de tre namnen. Använder en loop för att slippa viss upprepning.
  for (int i = 0; i < 3; i++) {
    std::cout << "Namn " << i + 1 << ": ";
    getline(std::cin, input);
    orig_tmp = input; // Spara originalraden i temporär variabel

    // Gör om input-strängen till små bokstäver för att kunna se till att sorteringen
    // är oberoende gemener/versaler
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    // Läs in strängen till input stream
    iss.str(input);
    // istringstream separerar på mellanslag, så här sparas förnamn och efternamn
    // till separata (temporära) variabler
    iss >> firstname_tmp >> lastname_tmp;
    iss.clear();

    // name{1-3}_orig blir lika med originalsträngen som matades in; detta används för visning.
    // name{1-3} blir lika med "efternamn förnamn" (gement), och används senare för sortering.
    switch (i) {
    case 0:
      name_orig = orig_tmp;
      name = lastname_tmp + " " + firstname_tmp;
      break;
    case 1:
      name2_orig = orig_tmp;
      name2 = lastname_tmp + " " + firstname_tmp;
      break;
    case 2:
      name3_orig = orig_tmp;
      name3 = lastname_tmp + " " + firstname_tmp;
    default:
      break;
    }
  }

  // Sortera namnen och skriv ut
  if (name >= name2 && name2 >= name3)
    std::cout << name3_orig << "\n" << name2_orig << "\n" << name_orig << std::endl;
  else if (name >= name3 && name3 >= name2)
    std::cout << name2_orig << "\n" << name3_orig << "\n" << name_orig << std::endl;
  else if (name2 >= name && name >= name3)
    std::cout << name3_orig << "\n" << name_orig << "\n" << name2_orig << std::endl;
  else if (name2 >= name3 && name3 >= name)
    std::cout << name_orig << "\n" << name3_orig << "\n" << name2_orig << std::endl;
  else if (name3 >= name && name >= name2)
    std::cout << name2_orig << "\n" << name_orig << "\n" << name3_orig << std::endl;
  else
    std::cout << name_orig << "\n" << name2_orig << "\n" << name3_orig << std::endl;

  return 0;
}
