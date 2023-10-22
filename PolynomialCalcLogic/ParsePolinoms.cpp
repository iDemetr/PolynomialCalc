#pragma once

#include "Header.h"

using namespace std;


/// <summary>
/// Парсит полином на список мономов
/// </summary>
/// <param name="sPolinom"></param>
/// <returns></returns>
vector<string> ParseMonoms(string sPolinom) {
	vector<string> list;
	int pos(0), numPolinom(0);
	string value, lastValue;

	cout << "Формирование списка монопов..." << endl;

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

	cout << "Сформированный список мономов:" << endl;
	for (string var : list) {
		cout << var << ", ";
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
vector<int>* CreatePolinom(vector<string> LMonoms) {

	char variable = ' ';
	string  value;
	int rank(0);

	vector<int>* polinom = new vector<int>();

	cout << "Формирование матрицы...\n";

	for (int i = 0; i < 10; i++) {
		polinom->push_back(0);
	}

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
						rank = 1;
						// Если символ число или знак числа
						if (ch >= '0' && ch <= '9' || ch == '-') value += ch;

						// Если встречена буква - значит это переменная полинома
						else if (!isVariable) {
							isVariable = true;
							variable = ch;
							if (value == "") value += "1";
							rank = 2;
						}
						else if (variable != ch)
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
			(*polinom)[rank - 1] = stoi(value);
		}
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}

	return polinom;
}

