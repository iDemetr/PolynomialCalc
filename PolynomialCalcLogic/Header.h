#pragma once

#ifndef HEADER_H
#define HEADER_H

#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>		
#include <windows.h>

#include <vector>
#include <stack>
#include <tuple>


enum command { poww = '^', multiplication = '*', division = '/', addition = '+', subtraction = '-' };

// Интерфейс для доступа к кортежу с задачей, где:
// Layer - номер слоя задачи, чем больше - выше приоритет действий
// Pol1 - левый операнд
// Pol2 - правый операнд
enum ETask { Layer, Pol1, Operator, Pol2 };

// Тип монома
struct Monom {
	// Коэффициент монома
	int Ratio;
	// Степень монома
	int Rank;
	// Аргумент
	std::string variable = "";
};

// Тип полинома
typedef std::vector<Monom> Polinom;
typedef std::vector<Monom>* tprPolinom;

// Заглушка при создании задач
const int noOperator = -1;


#endif HEADER_H