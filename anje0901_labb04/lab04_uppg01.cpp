/**
 * @file    lab04_uppg01.cpp
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2017-11-23
 * @version 1.0
 * @brief   Simulera tärningskast och ge statistik.
 *
 * Provat med GCC/G++ 7.2.0 och g++ -Wall -Wextra -Werror -Wpedantic -Wconversion -std=c++11
 * samt med Visual Studio 2017
 */
#include <clocale>
#include <cmath>
#include <iostream>
#include <random>

/**
 * Returnerar relativ tärningskastfrekvens, uttryckt i procent.
 *
 * @param total_rolls Totalt antal kast
 * @param rolls Antal kast för en viss tärningssida
 * @return Frekvens för en tärningssida, i procent, avrundat till heltal
 */
int calc_freq(int total_rolls, int rolls) {
  // Ser till att göra kasten till flyttal för korrekt division, som sedan
  // avrundas och returneras som heltal
  return (int)std::round(((double)total_rolls / (double)rolls) * 100);
}

/**
 * Returnerar slumpmässigt heltal mellan angivet minimum och maximum.
 *
 * @param min Minsta möjliga tal
 * @param rolls Högsta möjliga tal
 * @return Slumpmässigt heltal mellan min och max
 */
int roll_dice(int min, int max) {
  // Rekommenderad modern metod enligt https://stackoverflow.com/a/19728404
  // Behöver bara initialisera random_device och rng:n (random number generator)
  // en gång per programkörning, därför använder jag static. Annars hade det gått
  // väldigt mycket långsammare.
  static std::random_device rd;
  static std::mt19937 rng(rd());
  std::uniform_int_distribution<int> distribution(min, max);

  return distribution(rng);
}

int main() {
  int roll_count = 0;
  int t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0;

  std::setlocale(LC_ALL, "swedish");

  std::cout << "Ange antal tärningskast att simulera: ";
  std::cin >> roll_count;

  // Utför tärningskast angivet antal gånger
  for (int i = 0; i < roll_count; ++i) {
    int val = roll_dice(1, 6);

    if (val == 1)
      ++t1;
    else if (val == 2)
      ++t2;
    else if (val == 3)
      ++t3;
    else if (val == 4)
      ++t4;
    else if (val == 5)
      ++t5;
    else if (val == 6)
      ++t6;
  }

  std::cout << "Antal ettor : " << t1 << " (" << calc_freq(t1, roll_count) << "%)" << std::endl
            << "Antal tvåor : " << t2 << " (" << calc_freq(t2, roll_count) << "%)" << std::endl
            << "Antal treor : " << t3 << " (" << calc_freq(t3, roll_count) << "%)" << std::endl
            << "Antal fyror : " << t4 << " (" << calc_freq(t4, roll_count) << "%)" << std::endl
            << "Antal femmor: " << t5 << " (" << calc_freq(t5, roll_count) << "%)" << std::endl
            << "Antal sexor : " << t6 << " (" << calc_freq(t6, roll_count) << "%)" << std::endl;

  return 0;
}
