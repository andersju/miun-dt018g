/**
 * @file    constants.h
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Deklaration av Person-struct, enum för sortering och konstant för avgränsningstecken
 */
#ifndef PROJEKTUPPGIFT_CONSTANTS_H
#define PROJEKTUPPGIFT_CONSTANTS_H

#include <string>

// Lagrar en person, med några getters
struct Person {
private:
  std::string firstName_;
  std::string lastName_;
  std::string signature_;
  double height_;

public:
  Person(std::string& firstName, std::string& lastName, std::string& signature, double height)
      : firstName_(firstName), lastName_(lastName), signature_(signature), height_(height) {}
  const std::string& getFirstName() const { return firstName_; }
  const std::string& getLastName() const { return lastName_; }
  const std::string& getSignature() const { return signature_; }
  const double& getHeight() const { return height_; }
};

enum SortType { SORT_BY_NAME, SORT_BY_SIGNATURE, SORT_BY_HEIGHT };

const char DELIM = '|';

#endif
