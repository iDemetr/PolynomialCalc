#pragma once

#ifndef HEADER_H
#define HEADER_H

enum command { poww = '^', multiplication = '*', division = '/', addition = '+', subtraction = '-' };

// Интерфейс для доступа к кортежу с задачей, где:
// Layer - номер слоя задачи, чем больше - выше приоритет действий
// Pol1 - левый операнд
// Pol2 - правый операнд
enum ETask { Layer, Pol1, Operator, Pol2 };

/// <summary>
/// Кортеж задачи
/// </summary>
#define Task std::tuple<BYTE, string, char, string>

/// <summary>
/// Стек задач
/// </summary>
#define Tasks std::stack <Task>

/// <summary>
/// Тип монома
/// </summary>
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

/// <summary>
/// Тип полинома
/// </summary>
typedef std::set<Monom> Polinom;
typedef std::set<Monom>* ptrPolinom;

/// <summary>
/// 
/// </summary>
struct nodeBuffer{
	/// <summary>
	/// Номер слоя.
	/// </summary>
	int layer;

	/// <summary>
	/// Какая операция должна была быть выполнена
	/// </summary>
	char operation;

	/// <summary>
	/// Ссылка на крайний результат на этом слое.
	/// </summary>
	ptrPolinom polinom;
};

/// <summary>
/// Буфер расчётов
/// </summary>
typedef std::stack<nodeBuffer> Buffer;

// Заглушка при создании задач
const int noOperator = -1;

#endif HEADER_H