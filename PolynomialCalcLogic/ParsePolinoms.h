#pragma once

#include "Header.h"
using namespace std;

#ifndef PARSE_POLINOMS_H
#define PARSE_POLINOMS_H

/// <summary>
/// Преобразует список мономов в матрицу
/// Добавить поддержку многопараметрических полиномов
/// </summary>
/// <param name="LMonoms"></param>
/// <returns></returns>
ptrPolinom CreatePolinom(vector<string>);

/// <summary>
/// Парсит полином на список мономов
/// </summary>
/// <param name="sPolinom"></param>
/// <returns></returns>
vector<string> ParseMonoms(string);

#endif PARSE_POLINOMS_H