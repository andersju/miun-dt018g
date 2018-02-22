/**
 * @file    menu.h
 * @author  Anders Jensen-Urstad (anje0901) <anders@unix.se>
 * @date    2018-01-09
 * @version 1.0
 * @brief   Funktionsprototyper för menyhanteirng
 */
#ifndef PROJEKTUPPGIFT_MENU_H
#define PROJEKTUPPGIFT_MENU_H

#include "constants.h"

#include <string>
#include <vector>

const std::vector<std::string> MENUITEMS = {"1.  Add person",
                                            "2.  Print list of persons",
                                            "3.  Search person",
                                            "4.  Remove person",
                                            "5.  Sort by name",
                                            "6.  Sort by signature",
                                            "7.  Sort by height",
                                            "8.  Randomize order",
                                            "9.  Save to file",
                                            "10. Read from file",
                                            "11. Exit"};

int showMenuAndGetInput(const std::vector<std::string>& menuItems,
                        const std::vector<Person>& persons);
void showMenuHeader();

#endif
