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
#include <set>

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

    bool operator<(const Monom& monom) const
    {
        return Rank < monom.Rank;
    }

	//Операторы сравнения
	bool operator== (const Monom& pol2) {
		return Rank == pol2.Rank;
	}

	bool operator!= (const Monom& pol2) {
		return Rank != pol2.Rank;		
	}
};

// Тип полинома
typedef std::set<Monom> Polinom;
typedef std::set<Monom>* ptrPolinom;

// Заглушка при создании задач
const int noOperator = -1;

#endif HEADER_H