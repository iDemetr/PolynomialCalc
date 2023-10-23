#pragma once

#include "Header.h"
using namespace std;

#ifndef PRINT_POLINOMS_H
#define PRINT_POLINOMS_H

void PrintPolinom(ptrPolinom);

std::ostream& operator<< (std::ostream&, const Monom&);
std::ostream& operator<< (std::ostream&, const Polinom&);

#endif PRINT_POLINOMS_H