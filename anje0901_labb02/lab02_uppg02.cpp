/**
 * @file    lab02_uppg02.cpp
 * @author  Anders Jensen-Urstad <anje0901@student.miun.se>
 * @date    2017-11-23
 * @version 1.0
 * @brief   Skriv ut tabell över ASCII-tecken
 *
 * Testat med GCC/G++ 7.2.0 och `g++ -Wall -Wextra -Werror -pedantic -std=c++11`
 * samt med Visual Studio 2017
 */
#include <iomanip>
#include <iostream>

int main() {
  int teckennr;

  // Två for-loopar för att kunna visa kolumnvis
  for (int i = 32; i < 64; i++) {
    for (int j = 0; j < 7; j++) {
      teckennr = i + 32 * j;
      // På en del plattformar är char signed (-127 eller -128 till 127). unsigned char
      // är garanterat minst 0-255, så jag cast:ar till unsigned char för säkerhets skull.
      std::cout << std::setw(6) << teckennr << " " << static_cast<unsigned char>(teckennr);
    }
    std::cout << std::endl;
  }

  return 0;
}
