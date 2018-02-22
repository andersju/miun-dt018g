/**
 * @file    search.h
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Funktionsprototyper för sökning
 */
#ifndef PROJEKTUPPGIFT_SEARCH_H
#define PROJEKTUPPGIFT_SEARCH_H

#include "constants.h"

#include <vector>

std::vector<Person>::const_iterator searchSignature(const std::vector<Person>& persons,
                                                    const std::string& signatureToSearch);
void performSearch(const std::vector<Person>& persons);

#endif
