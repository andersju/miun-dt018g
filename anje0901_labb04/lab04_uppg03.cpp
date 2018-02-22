/**
 * @file    lab04_uppg03.cpp
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2017-12-06
 * @version 1.0
 * @brief   Simulera tärningskast eller räkna ut samtalstaxa
 *
 * Provat med GCC/G++ 7.2.0 och g++ -Wall -Wextra -Werror -Wpedantic -Wconversion -std=c++11
 * samt med Visual Studio 2017
 */
#include <algorithm>
#include <clocale>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <tuple>

/**
 * Konstanter för samtalstaxeprogrammet
 */
const double BASE_MINUTE_PRICE = 4; // Fullpristaxa exkl moms, per minut
const double MOMS = 25;             // Moms i procent
const double OFFPEAK_DISCOUNT = 65; // Rabatt i procent för tider utanför 08:00-18:30
const double LENGTH_DISCOUNT = 15;  // Rabatt i procent för samtal längre än 30 minuter
// Tiderna hade kunnat anges i minuter, men hh:mm är lite användarvänligare.
const std::string ORDINARY_TIME_START = "08:00"; // Början på ordinarie tid (fullpris)
const std::string ORDINARY_TIME_STOP = "18:30";  // Slut på ordinarie tid

/**
 * Funktionsprototyper
 */
void clear_screen();
void pause_program();

void diceSim();
int calc_freq(int total_rolls, int rolls);
int roll_dice(int min, int max);

void teleTaxa();
bool has_only_integers(const std::string& str);
int parse_time(const std::string& input);
std::tuple<bool, int, int> parse_input(const std::string& start_time, const std::string& stop_time);
double get_cost(int start_minutes, int stop_minutes);

int main() {
  int choice = 1;

  std::setlocale(LC_ALL, "swedish");

  while (choice != '3') {
    std::cout << "Programmeny\n" << std::endl;
    std::cout << "1. Kasta tärning" << std::endl;
    std::cout << "2. RingPling" << std::endl;
    std::cout << "3. Avsluta" << std::endl;

    std::cout << "\nVälj alternativ (1-3): ";
    std::cin >> choice;

    switch (choice) {
    case 1:
      diceSim();
      break;
    case 2:
      teleTaxa();
      break;
    case 3:
      return 0;
    default:
      std::cout << "Var god ange giltigt menyalternativ." << std::endl;
      break;
    }

    pause_program();
    clear_screen();
  }

  return 0;
}

/**
 * Pausar programmet
 */
void pause_program() {
  std::cout << "Tryck på enter för att fortsätta." << std::endl;
  // Två cin.ignore() behövs för att inte tidigare input ska tas i beaktande
  // (vilket hade gjort att ovanstående försvunnit direkt)
  std::cin.ignore();
  std::cin.ignore();
}

/**
 * Rensar skärmen
 */
void clear_screen() {
// Det finns inget standardsätt att rensa skärmen, så försök att göra det
// minst dåliga alternativet beroende på plattform.
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
  std::cout << "\033[2J\033[1;1H";
#elif _WIN32
  system("cls");
#else
  std::cout << std::string(100, '\n');
#endif
}

/* Funktioner för tärningsprogrammet */

/**
 * Program för att simulera tärningskast
 */
void diceSim() {
  int roll_count = 0;
  int t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0;

  std::cout << "Ange antal tärningskast att simulera: ";
  std::cin >> roll_count;

  // // Utför tärningskast angivet antal gånger
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
}

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

/* Funktioner för teletaxaprogrammet */

void teleTaxa() {
  std::string start_time, stop_time;
  int start_minutes, stop_minutes;
  double cost, accumulated_cost = 0;
  bool valid;
  char try_again = 'j';

  while (try_again == 'j') {
    std::cout << "Ange starttid: ";
    std::cin >> start_time;

    std::cout << "Ange sluttid: ";
    std::cin >> stop_time;

    std::tie(valid, start_minutes, stop_minutes) = parse_input(start_time, stop_time);

    if (valid) {
      cost = get_cost(start_minutes, stop_minutes);
      std::cout << std::fixed << std::setprecision(2) << "Total kostnad: " << cost << " kr"
                << std::endl;
      accumulated_cost += cost;
    }

    std::cout << "\nVill du göra en till beräkning (j/n)? ";
    std::cin >> try_again;
  }

  std::cout << "\nTotaltaxa för alla inmatade samtal: " << accumulated_cost << " kr " << std::endl;
}

/**
 * Returnerar true om input-strängen består av enbart siffertecken, annars false.
 * Inspirerad av kommentar på https://stackoverflow.com/a/4654718 av kbjorklu
 *
 * @param str Sträng att undersöka
 * @return true om enbart siffror, annars false
 */
bool has_only_integers(const std::string& str) {
  // Om strängen är tom har den inga siffror, så returnera false
  if (str.empty()) {
    return false;
  }

  // Nedanstående returnerar true om strängen har enbart siffror i sig
  return str.find_first_not_of("0123456789") == std::string::npos;
}

/**
 * Parse:ar en tidssträng och kollar huruvida den är korrekt formaterad; och,
 * om så är fallet, konverterar från h:mm eller hh:mm till enbart minuter
 *
 * @param input Tidssträng att undersöka
 * @return Tidsangivelse i minuter
 */
int parse_time(const std::string& input) {
  std::istringstream iss;
  std::string hours_str, minutes_str;
  int hours, minutes;

  // Returnera fel om input inte har kolon
  if (input.find(':') == std::string::npos) {
    std::cout << "BOOOO! Felaktigt format" << std::endl;
    return -1;
  }

  // Returnera fel om input inte har rätt längd
  if (input.length() != 4 && input.length() != 5) {
    std::cout << "Felaktigt längd!" << std::endl;
    return -1;
  }

  // Vid det här laget har input både kolon och rätt längd. Läs av två värden:
  iss.str(input);
  std::getline(iss, hours_str, ':');
  std::getline(iss, minutes_str, ':');

  // Returnera fel om något av de två värdena innehåller annat tecken än siffra
  if (!has_only_integers(hours_str) || !has_only_integers(minutes_str)) {
    std::cout << "Aja baja! Bara siffror plz!" << std::endl;
    return -1;
  }

  // Vid det här laget innehåller hours_str respektive minutes_str garanterat inget annat än
  // siffertecken, så jag kan konvertera dem utan att behöva hantera exceptions.
  hours = std::stoi(hours_str);
  minutes = std::stoi(minutes_str);

  if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
    std::cout << "Felaktig tidsangivelse. Giltiga intervall är 0-23 timmar och 0-59 minuter."
              << std::endl;
    return -1;
  }

  return hours * 60 + minutes;
}

/**
 * Parse:ar input-strängarna och försöker omvandla till tidsangivelser i minuter
 *
 * @param start_time Starttid som textsträng (t.ex. 07:45 eller 7:45)
 * @param stop_time Sluttid som textsträng (t.ex. 08:30 eller 8:30)
 * @return Huruvida tiden parse:ades korrekt, samt starttid och sluttid specificerat som
 *         minuter efter midnatt
 */
std::tuple<bool, int, int> parse_input(const std::string& start_time,
                                       const std::string& stop_time) {
  int start_minutes = parse_time(start_time);
  int stop_minutes = parse_time(stop_time);

  if (start_minutes < 0 || stop_minutes < 0) {
    return std::make_tuple(false, 0, 0);
  }

  if (start_minutes > stop_minutes) {
    std::cout << "Sluttiden är större än starttiden." << std::endl;
    return std::make_tuple(false, 0, 0);
  }

  // Om start- och stopptid är samma ser vi till att stopptid blir starttid+1,
  // för att beräkningen ska bli rätt; det antas att taxan gäller per *påbörjad*
  // minut.
  if (start_minutes == stop_minutes) {
    stop_minutes = start_minutes + 1;
  }

  return std::make_tuple(true, start_minutes, stop_minutes);
}

/**
 * Räknar ut samtalskostnad för specificerad tid
 *
 * @param start_minutes Starttid, angivet som antal minuter efter midnatt
 * @param stop_minutes Sluttid, angivet som antal minuter efter midnatt
 * @return Samtalkostnad (inkl. moms; rabatter inräknade)
 */
double get_cost(int start_minutes, int stop_minutes) {
  int total_time = 0;
  int ordinary_time = 0;
  int discounted_time = 0;
  double cost = 0;

  // Räknar ut hur mycket av tiden som ligger inom perioden
  // för fullpristaxa
  auto Min = std::max(start_minutes, parse_time(ORDINARY_TIME_START));
  auto Max = std::min(stop_minutes, parse_time(ORDINARY_TIME_STOP));
  if (Min < Max) {
    ordinary_time = Max - Min;
  }

  total_time = stop_minutes - start_minutes;
  discounted_time = total_time - ordinary_time;

  cost = ordinary_time * BASE_MINUTE_PRICE;
  cost += (discounted_time * BASE_MINUTE_PRICE) * ((100 - OFFPEAK_DISCOUNT) / 100);

  if (total_time > 30)
    cost = cost * ((100 - LENGTH_DISCOUNT) / 100);

  return cost * ((MOMS / 100) + 1);
}
