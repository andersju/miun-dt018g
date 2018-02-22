/**
 * @file    menu.cpp
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Funktioner för menyvisning och menyinput
 */
#include "menu.h"
#include "constants.h"
#include "utils.h"

#include <iostream>
#include <vector>

/*
 * Visar menyn och tar input
 *
 * @param menuItems Menysträngarna att visa
 * @param persons Vector med personerna
 * @return Valt menyföremål
 */
int showMenuAndGetInput(const std::vector<std::string>& menuItems,
                        const std::vector<Person>& persons) {
  showMenuHeader();

  std::cout << "\nNumber of persons in list: " << persons.size() << "\n" << std::endl;

  for (const auto& e : menuItems) {
    std::cout << e << std::endl;
  }

  return getIntFromInput("\nEnter an option [1-11]: ", false, true, 1, 11);
}

/*
 * Skriver ut välkomnande menyheader
 */
void showMenuHeader() {
  std::cout << R"( ____  _   _ ____  _____ ___   ___   ___   ___)" << std::endl;
  std::cout << R"(|  _ \| | | |  _ \| ____/ _ \ / _ \ / _ \ / _ \)" << std::endl;
  std::cout << R"(| |_) | | | | |_) |  _|| (_) | | | | | | | | | |       Welcome to)" << std::endl;
  std::cout << R"(|  __/| |_| |  _ <| |___\__, | |_| | |_| | |_| | PersonUppgiftsREgister)"
            << std::endl;
  std::cout << R"(|_|    \___/|_| \_\_____| /_/ \___/ \___/ \___/  *********9000*********)"
            << std::endl;
}
