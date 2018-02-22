/**
 * @file    lab03_uppg01.cpp
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2017-11-23
 * @version 1.0
 * @brief   Byt ut ord i sträng
 *
 * Testat med GCC/G++ 7.2.0 och `g++ -Wall -Wextra -Werror -pedantic -std=c++11`
 * samt med Visual Studio 2017
 */
#include <algorithm>
#include <clocale>
#include <iostream>
#include <string>

int main() {
  std::string::size_type period_position = 0;

  const std::string inText1 = "Foten är en kroppsdel som förekommer mycket i våra uttryck.";
  const std::string inText2 = "På stående fot betyder omedelbart, utan förberedelse.";
  const std::string inText3 = "Försätta på fri fot betyder att ge någon friheten.";
  const std::string inText4 = "Sätta foten i munnen betyder att göra bort sig.";
  const std::string inText5 = "Få om bakfoten betyder att missuppfatta något.";
  const std::string inText6 = "Skrapa med foten betyder att visa sig underdånig eller ödmjuk.";
  const std::string inText7 = "Stryka på foten betyder att tvingas ge upp.";
  const std::string inText8 =
      "Leva på stor fot betyder att föra ett dyrbart eller slösaktigt leverne.";
  const std::string inText9 = "Varför fick du foten???";

  std::setlocale(LC_ALL, "swedish");

  // Hade kanske hellre velat görat en strängarray av intexterna, men jag håller mig till
  // uppgiftens kravspecifikation. Så här konkateneras strängarna.
  std::string whole_text = inText1 + "\n" + inText2 + "\n" + inText3 + "\n" + inText4 + "\n" +
                           inText5 + "\n" + inText6 + "\n" + inText7 + "\n" + inText8 + "\n" +
                           inText9;

  // Gör om hela strängen till små bokstäver
  transform(whole_text.begin(), whole_text.end(), whole_text.begin(), ::tolower);

  // Byt ut alla "fot" mot "hand"
  while (whole_text.find("fot") != std::string::npos) {
    whole_text.replace(whole_text.find("fot"), 3, "hand");
  }

  // Se till att första bokstaven i strängen är versal
  whole_text.at(0) = toupper(whole_text.at(0));

  // Hitta positionen för första punkten
  period_position = whole_text.find(".");

  // Loopa så länge sökningen får en träff
  while (period_position != std::string::npos) {
    // Jag vet att första tecknet efter newline-tecken är en ny
    // mening, så jag gör det tecknet versalt. Kollar period_position mot
    // längden på strängen för att se till att jag inte försöker
    // komma åt något utanför listan.
    if (period_position + 2 < whole_text.length()) {
      whole_text.at(period_position + 2) = toupper(whole_text.at(period_position + 2));
    }

    // Söker efter punkt igen, men bara från och med föregående
    // teckenposition plus ett (annars blir det en oändlig loop!)
    period_position = whole_text.find(".", period_position + 1);
  }

  std::cout << whole_text << std::endl;

  return 0;
}
