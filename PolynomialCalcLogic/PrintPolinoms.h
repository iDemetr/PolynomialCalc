#pragma once

#include "Header.h"
using namespace std;

#ifndef PRINT_POLINOMS_H
#define PRINT_POLINOMS_H

/// <summary>
/// Выводит полином в виде строки в консоль.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <param name=""></param>
void PrintPolinoms(const Polinom&, const char, const Polinom&);

/// <summary>
/// Преобразует полином в строку 
/// </summary>
/// <param name=""></param>
/// <returns></returns>
string ToString(const Polinom&);

/// <summary>
/// Преобразует моном в строку 
/// </summary>
/// <param name=""></param>
/// <returns></returns>
string ToString(const Monom&);

/// <summary>
/// Оператор вывода монома
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
std::ostream& operator<< (std::ostream&, const Monom&);
/// <summary>
/// Оператор вывода полинома
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
std::ostream& operator<< (std::ostream&, const Polinom&);

#endif PRINT_POLINOMS_H