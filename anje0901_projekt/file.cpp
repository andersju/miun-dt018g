/**
 * @file    file.cpp
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Funktioner för filhantering och kryptering
 */
#include "file.h"
#include "constants.h"
#include "utils.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <tuple>

/*
 * Krypterar ett tecken med teckenförskjutning
 *
 * @param character Tecken att kryptera
 * @param rotation Antal steg tecknet ska förskjutas
 * @return Krypterat tecken
 */
char rotEncrypt(char character, const int rotation) {
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

/*
 * Dekrypterar ett tecken med teckenförskjutning
 *
 * @param character Tecken att dekryptera
 * @param rotation Antal steg tecknet ska förskjutas bakåt
 * @return Dekrypterat tecken
 */
char rotDecrypt(char character, const int rotation) {
  int char_value = static_cast<unsigned char>(character);

  // Om char_value minus rotation är lika med eller större än 32 är tecknet printable.
  // Om char_value minus rotation är mindre än 32 är tecknet inte printable, så då hoppar jag
  // över de första 32 och loopar runt till slutet istället.
  if (char_value - rotation >= 32) {
    character = static_cast<char>(char_value - rotation);
  } else {
    character = static_cast<char>(256 - (32 % (char_value - rotation)));
  }

  return character;
}

/*
 * Krypterar eller dekrypterar (roterar) en sträng
 *
 * @param str Sträng att rotera
 * @param crypttype Typ av rotation (framåt eller bakåt)
 * @param key Förskjutningsnyckel
 * @return Roterad sträng
 */
std::string rotateString(std::string str, CryptType crypttype, int key) {
  // Loopa igenom varje tecken i inmatade strängen
  for (std::string::size_type i = 0; i < str.size(); ++i) {
    if (crypttype == ENCRYPT) {
      str[i] = rotEncrypt(str[i], key);
    } else {
      str[i] = rotDecrypt(str[i], key);
    }
  }

  return str;
}

/*
 * Ber användaren om filnamn och krypteringsnyckel (båda optional)
 *
 * @param currentFileName Nuvarande default-filnamn
 * @param currentEncryptionKey Nuvarande default-nyckel
 * @return Filnamn och nyckel att använda
 */
std::tuple<std::string, int> getFileNameAndKeyFromInput(const std::string& currentFileName,
                                                        const int& currentEncryptionKey) {
  // Om ett filnamn angetts tidigare används det som default-filnamn,
  // annars ett hårdkodat default-namn
  std::string defaultFileName = "data.txt";
  if (!currentFileName.empty()) {
    defaultFileName = currentFileName;
  }

  std::cout << "Enter filename [" << defaultFileName << "]: ";
  std::string fileName;
  std::getline(std::cin, fileName);

  // Om inget filnamn angavs används default-filnamnet
  if (fileName.empty()) {
    fileName = defaultFileName;
  }

  int encryptionInput = getIntFromInput("Enter encryption key (0 for no decryption) [" +
                                            std::to_string(currentEncryptionKey) + "]: ",
                                        true);
  // Om nyckel angetts används den (annars default-nyckeln)
  if (encryptionInput == -1) {
    encryptionInput = currentEncryptionKey;
  }

  return std::make_tuple(fileName, encryptionInput);
}

/*
 * Sparar personvectorn till fil
 *
 * @param persons Person-vector att spara
 * @param currentFileName Nuvarande default-filnamn
 * @param encryptionKey Nuvarande default-kryptering
 */
void saveToFile(const std::vector<Person>& persons, std::string& currentFileName,
                int& currentEncryptionKey) {
  printFunctionHeader("Save to file");
  // Sätter fil/nyckel att använda till antingen default-värden eller det som matats in av
  // användaren
  std::tie(currentFileName, currentEncryptionKey) =
      getFileNameAndKeyFromInput(currentFileName, currentEncryptionKey);

  std::ofstream outFile(currentFileName);
  if (outFile.is_open()) {
    // Itererar över alla personer i vectorn
    for (auto& e : persons) {
      std::ostringstream tmpString;
      // Skapar en DELIM-separerad sträng av personobjektet
      tmpString << e.getFirstName() << DELIM << e.getLastName() << DELIM << e.getSignature()
                << DELIM << e.getHeight();

      // Skriver strängen till fil, ev. efter att först ha krypterats om nyckel angetts
      if (currentEncryptionKey > 0) {
        outFile << rotateString(tmpString.str(), ENCRYPT, currentEncryptionKey) << std::endl;
      } else {
        outFile << tmpString.str() << std::endl;
      }
    }
    outFile.close();
    std::cout << persons.size() << " persons written to file." << std::endl;
  } else {
    std::cout << "Could not open " << currentFileName << " for writing." << std::endl;
  }
}

/*
 * Läser in personvectorn från fil
 *
 * @param persons Vector att läsa in till
 * @param currentFileName Nuvarande default-filnamn
 * @param encryptionKey Nuvarande default-kryptering
 */
void readFromFile(std::vector<Person>& persons, std::string& currentFileName,
                  int& currentEncryptionKey) {
  printFunctionHeader("Read from file");
  // Sätter fil/nyckel att använda till antingen default-värden eller det som matats in av
  // användaren
  std::tie(currentFileName, currentEncryptionKey) =
      getFileNameAndKeyFromInput(currentFileName, currentEncryptionKey);

  // Rensar bort eventuell befintlig lista
  if (!persons.empty()) {
    persons.clear();
  }

  std::ifstream inFile(currentFileName);
  if (inFile.is_open()) {
    std::cout << "\nReading from " << currentFileName << std::endl;

    std::string line;
    bool success = false;
    while (std::getline(inFile, line)) {
      // Dekrypterar strängen om nyckel angetts
      if (currentEncryptionKey > 0) {
        line = rotateString(line, DECRYPT, currentEncryptionKey);
      }

      // Kollar huruvida inläst rad tycks vara i korrekt format eller ej genom
      // att räkna antal förekomster av DELIM (detta verifierar även om ev. dekryptering fungerat)
      if (std::count(line.begin(), line.end(), DELIM) != 3) {
        std::cout << "File could not be parsed." << std::endl;
        if (currentEncryptionKey > 0) {
          std::cout << "Wrong encryption key?" << std::endl;
        }
        break;
      } else {
        success = true;
      }

      std::stringstream ss(line);
      std::string tmpFirstName, tmpLastName, tmpSignature, tmpHeight;

      // Läser in alla fält och, om lyckat, skapar personobjekt som sedan adderas till
      // persons-vectorn
      if (std::getline(ss, tmpFirstName, DELIM) && std::getline(ss, tmpLastName, DELIM) &&
          std::getline(ss, tmpSignature, DELIM) && std::getline(ss, tmpHeight)) {
        Person p = {tmpFirstName, tmpLastName, tmpSignature, std::stod(tmpHeight)};
        persons.push_back(p);
      }
    }
    if (success) {
      std::cout << persons.size() << " persons successfully loaded." << std::endl;
    }

    inFile.close();
  } else {
    std::cout << "Could not open " << currentFileName << " for reading." << std::endl;
  }
}
