/**
 * @file    lab03_uppg03.cpp
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2017-11-23
 * @version 1.0
 * @brief   Kryptera/dekryptera sträng med rot13+rot7
 *
 * Testat med GCC/G++ 7.2.0 och `g++ -Wall -Wextra -Werror -pedantic -std=c++11`
 * samt med Visual Studio 2017
 */
#include <iostream>
#include <string>

enum CryptType { ENCRYPT, DECRYPT };

// Funktion för att kryptera ett tecken.
char rot_encrypt(char character, const int rotation) {
  // char är signed (-128-255) eller unsigned (0-255) beroende på plattform,
  // så se till att få fram osignade versionens värde för att kunna jämföra sen.
  int char_value = static_cast<unsigned char>(character);

  // Är roterade tecknet inom godkänt intervall? Om ja, använd det tecknet.
  // Om inte, använd modulo för att ta det som skvimper över och lägg till
  // det till början av det tillåtna intervallet.
  if (char_value + rotation <= 255) {
    character = static_cast<char>(char_value + rotation);
  } else if (char_value <= 255) {
    character = static_cast<char>(((char_value + rotation) % 255) + 31);
  }

  return character;
}

// Funktion för att dekryptera ett tecken.
// Precis som rot_encrypt, fast åt andra hållet.
char rot_decrypt(char character, const int rotation) {
  int char_value = static_cast<unsigned char>(character);

  // Om char_value minus rotation är lika med eller större än 32 är tecknet printable.
  // Om char_value minus rotation är mindre än 32 är tecknet inte printable, så då hoppar jag
  // över de första 32 och loopar runt till slutet istället.
  if (char_value - rotation >= 32) {
    character = static_cast<char>(char_value - rotation);
  } else if (char_value - rotation < 32) {
    character = static_cast<char>(256 - (32 % (char_value - rotation)));
  }

  return character;
}

// Funktion för att rotera en sträng åt endera hållet
std::string rotate_string(std::string str, CryptType crypttype) {
  // Initial nyckel
  int key = 13;

  // Loopa igenom varje tecken i inmatade strängen
  for (std::string::size_type i = 0; i < str.size(); ++i) {
    if (i != 0 && (i % 5 == 0)) { // Ändra key var 5:e tecken
      key = (key == 13 ? 7 : 13); // Toggla mellan 13 och 7
    }

    if (crypttype == ENCRYPT) {
      str[i] = rot_encrypt(str[i], key);
    } else {
      str[i] = rot_decrypt(str[i], key);
    }
  }

  return str;
}

int main() {
  std::string original, encrypted, decrypted;

  // Läs in sträng att kryptera
  std::cout << "Ange text att kryptera: ";
  std::getline(std::cin, original);

  // Utför kryptering av input-sträng
  encrypted = rotate_string(original, ENCRYPT);
  // Utför dekryptering av krpyterade strängen
  decrypted = rotate_string(encrypted, DECRYPT);

  // Skriv ut krypterade och dekrypterade strängarna
  std::cout << "Krypterad: " << encrypted << std::endl;
  std::cout << "Dekrypterad: " << decrypted << std::endl;

  return 0;
}
