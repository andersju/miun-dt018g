/**
 * @file    lab02_uppg03.cpp
 * @author  Anders Jensen-Urstad <anje0901@student.miun.se>
 * @date    2017-11-23
 * @version 1.0
 * @brief   Skriv ut nummer baklänges och kolla om det är ett palindrom
 *
 * Testat med GCC/G++ 7.2.0 och `g++ -Wall -Wextra -Werror -pedantic -std=c++11`
 * samt med Visual Studio 2017
 */
#include <clocale>
#include <iostream>

// Algoritm för att vända på ett tal baserad på
// https://medium.com/@ManBearPigCode/how-to-reverse-a-number-mathematically-97c556626ec6
int reverse_number(int number) {
  int reversed = 0;

  while (number != 0) {
    reversed = (reversed * 10) + (number % 10);
    number = number / 10;
  }

  return reversed;
}

int main() {
  int original;
  int reversed = 0;
  char try_again = 'j';

  std::setlocale(LC_ALL, "swedish");

  // Loopa så länge användaren inte matat in 'n'
  while (true) {
    std::cout << "Mata in ett femsiffrigt tal: ";
    std::cin >> original;

    // Kolla antal siffror i inmatat tal
    if (original >= 10000 && original <= 99999) {
      reversed = reverse_number(original);

      std::cout << "Baklänges: " << reversed << std::endl;
      // Om originalet och det omvända är lika är det ett palindrom. Här ternära operatorn ? som en
      // mer kompakt if-else.
      std::cout << "Talet är " << (reversed == original ? "ett" : "inte ett") << " palindrom"
                << std::endl;
    } else {
      std::cout << "Talet måste ha exakt fem siffror." << std::endl;
      // I fall användaren matar in något felaktigt (dvs något som inte är heltal)
      // ser nedanstående till att återställa error-flaggor samt ignorera det som matats in
      // (upp till det som kommer först av 1000 tecken eller newline)
      std::cin.clear();
      std::cin.ignore(1000, '\n');
    }

    // Se till att bara j eller n accepteras
    do {
      std::cout << "En gång till (j/n)? ";
      std::cin >> try_again;
    } while (!std::cin.fail() && try_again != 'j' && try_again != 'n');

    if (try_again == 'n') {
      return 0;
    }
  }

  return 0;
}
