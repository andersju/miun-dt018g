/**
 * @file    lab02_uppg01.cpp
 * @author  Anders Jensen-Urstad <anje0901@student.miun.se>
 * @date    2017-11-22
 * @version 1.0
 * @brief   Räkna ut pytagoreiska trianglar
 *
 * Testat med GCC/G++ 7.2.0 och `g++ -Wall -Wextra -Werror -pedantic -std=c++11`
 * samt med Visual Studio 2017
 */

#include <clocale>
#include <iostream>
#include <string>

std::string format_triangle(int a, int b, int c) {
  return "[a=" + std::to_string(a) + ",\t b=" + std::to_string(b) + ",\t c=" + std::to_string(c) +
         "]\n";
}

int main() {
  const int MAX = 500;                // Maxvärde på hypotenusan
  int a, b, c, no_of_pytriangles = 0; // Temporära variabler + lagring av totalt antal
  std::string triangles[5]; // För lagring av trianglar med hypotenusa 100/200/300/400/500

  std::setlocale(LC_ALL, "swedish");

  // Brute force-metod. Kollar helt enkelt alla varianter upp till 500.
  // Vi vet att första är [3,4,5] så vi börjar där.
  for (a = 3; a <= MAX; a++) {
    // Viktigt att sätta b till a (eller lika gärna a+1 eftersom b alltid är större),
    // för att undvika dubbletter.
    for (b = a + 1; b <= MAX; b++) {
      // Hypotenusan är alltid större än b.
      for (c = b + 1; c <= MAX; c++) {
        // Om a^2 + b^2 = c^2 har vi en pytagoreisk triangel.
        if ((a * a + b * b) == (c * c)) {
          no_of_pytriangles++;

          // Jag vill ha just 100, 200, 300, 400, 500. Eftersom de alla är jämnt
          // delbara med 100 (och inget annat jag kollar är det) kan jag använda %
          // istället för t.ex. c == 100 || c == 200 || c == 300 osv.
          if (c % 100 == 0) {
            // Eftersom de är jämnt delbara kan jag också göra det lätt för mig och dela
            // med 100 och subtrahera ett för att få rätt index i triangles-arrayen.
            // Strängformateringen kan lika gärna göras här men jag flyttade ut den för att
            // få det att se lite mindre rörigt ut.
            triangles[c / 100 - 1].append(format_triangle(a, b, c));
          }
        }
      }
    }
  }

  std::cout << "Antal pytagoreiska trianglar med ingen sida större än 500: ";
  std::cout << no_of_pytriangles << std::endl;

  std::cout << "Trianglar med hypotenusor (c) 100, 200, 300, 400 och 500:\n" << std::endl;
  // Loop på C++11-vis, istället för att gå igenom rangen sizeof(triangles)/sizeof(triangles[0])...
  // `auto triangle_str` hade fungerat, men skapat en kopia. `const &` ser till att ingen kopia
  // skapas, och att jag heller inte kan råka modifiera originalet.
  for (auto const& triangle_str : triangles) {
    std::cout << triangle_str << std::endl;
  }

  return 0;
}
