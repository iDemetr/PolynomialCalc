#pragma once

#include "Header.h"
#include "PrintPolinoms.h"

using namespace std;


/// <summary>
/// Парсит полином на список мономов
/// </summary>
/// <param name="sPolinom"></param>
/// <returns></returns>
std::vector<string> ParseMonoms(string sPolinom) {
	std::vector<string> list;
	int pos(0), numPolinom(0);
	string value, lastValue;

	cout << "\n Распознование мономов:  ";

	// Парсинг введенной строки с разбиеним в список по мономам
	do {
		pos = sPolinom.find_first_of(" ");											// Временное ограничение на разделение пробелами мономов и действий
		value = sPolinom.substr(0, pos);											// Получение монома
		sPolinom = sPolinom.substr(pos + 1, sPolinom.length());						// Удаляем из строки распаршенную часть

		if (value != "+") {

			if (lastValue == "-") {													// Фиксация отрицательных значений
				list.push_back("-" + value);
			}
			else if (value != "-") { list.push_back(value); }

			lastValue = value;
		}
	} while (pos != -1);

	auto ptr = list.begin();

	while (ptr != list.end()) {
		cout << *ptr;
		ptr++;
		if (ptr != list.end())
			cout << ", ";
	}
	cout << "\n";

	return list;
}

/// <summary>
/// Преобразует список мономов в матрицу
/// Добавить поддержку многопараметрических полиномов
/// </summary>
/// <param name="LMonoms"></param>
/// <returns></returns>
ptrPolinom CreatePolinom(std::vector<string> LMonoms) {

	string variable = "";
	string  value;
	int rank(0);

	ptrPolinom polinom = new Polinom();

	cout << "\n Сборка полинома: ";

	try {
		for (string var : LMonoms) {
			bool isDegree = false, isVariable = false;
			value = "";

			// Цикл по слову
			for (char ch : var) {
				// Если степень в слове не была встречена
				if (!isDegree && ch != '^') {
					// Если название переменной не было встречено
					if (!isVariable) {
						rank = 0;
						// Если символ число или знак числа
						if (ch >= '0' && ch <= '9' || ch == '-') value += ch;

						// Если встречена буква - значит это переменная полинома
						else if (!isVariable) {
							isVariable = true;
							variable = ch;
							if (value == "" || value == "-" ) value += "1";
							rank = 1;
						}
						else if (variable[0] != ch)
							throw exception("\t Ошибка! Больше одной переменных");
					}
					// Генерация ошибки, если после встречи переменной не встречен символ степени
					else throw exception("\t Ошибка! Неверная запись полинома");
				}

				// Если встречено определение степени
				else {
					// Игнорирование символа степени
					if (isDegree) {
						// Если в степени встречен отличный символ от цифры
						if (ch >= '0' && ch <= '9') {
							rank *= 10;
							rank += ch - '0';
						}
						else throw exception("\t Ошибка! Неверная запись полинома");
					}
					else {
						rank = 0;
						isDegree = true;
					}
				}
			}

			polinom->insert({ stoi(value), rank, variable });

			variable = ""; isVariable = false;
		}
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
		throw;
	}

	cout << *polinom;

	return polinom;
}

