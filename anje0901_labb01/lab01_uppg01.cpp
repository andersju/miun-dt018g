/**
 * @file    lab01_uppg01.cpp
 * @author  Anders Jensen-Urstad <anje0901@student.miun.se>
 * @date    2017-11-21
 * @version 1.0
 * @brief   Räkna ut bensinförbrukning och kostnad
 *
 * Testat med GCC/G++ 7.2.0 och `g++ -Wall -Wextra -Werror -pedantic -std=c++11`
 */

#include <clocale>
#include <iomanip>
#include <iostream>

// Låt bensinpris vara ett konstant flyttal
const double BENSINPRIS = 12;

int main() {
  // Variablerna får också vara flyttal för att uträkningarna ska bli rätt
  double stallning01, stallning02, tankat, distans, bensinforbrukning;

  // Sätt locale till svenska för att försöka se till att svenska tecken visas rätt
  std::setlocale(LC_ALL, "swedish");

  std::cout << "BENSINFÖRBRUKNING OCH KOSTNAD" << std::endl;
  std::cout << "=============================\n" << std::endl;

  // Låt användaren mata in de tre olika värdena
  std::cout << "Ange mätarställning 1 [km]: ";
  std::cin >> stallning01;
  std::cout << "Ange mätarställning 2 [km]: ";
  std::cin >> stallning02;
  std::cout << "Hur mycket tankade du [l] : ";
  std::cin >> tankat;

  distans = stallning02 - stallning01;
  bensinforbrukning = (tankat / distans) * 10;

  // Se till att bara visa två decimaler
  std::cout << "\n\n" << std::fixed << std::setprecision(2);

  // right och setw för att se till att decimaltecknet hamnar rätt
  std::cout << "Bensinförbrukning [l/mil] : ";
  std::cout << std::right << std::setw(6) << bensinforbrukning << std::endl;

  std::cout << "Milkostnad        [kr/mil]: ";
  std::cout << std::right << std::setw(6) << bensinforbrukning * BENSINPRIS << std::endl;

  return 0;
}
