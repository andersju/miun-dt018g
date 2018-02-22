/**
 * @file    sort.h
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Funktionsprototyper för sortering
 */
#ifndef PROJEKTUPPGIFT_SORT_H
#define PROJEKTUPPGIFT_SORT_H

#include "constants.h"

#include <vector>

void randomize(std::vector<Person>& persons);
void performSort(std::vector<Person>& persons, SortType sorttype);

#endif
