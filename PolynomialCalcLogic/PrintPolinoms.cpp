#pragma once

#include "Header.h"

using namespace std;


/// <summary>
/// Оператор вывода
/// </summary>
/// <param name="stream"></param>
/// <param name="cells"></param>
/// <returns></returns>
std::ostream& operator<< (std::ostream& stream, const Monom& monom) {

	if (monom.Ratio != 0) {
		if (monom.Ratio < 0)
			stream << "- ";
		else
			stream << "+ ";

		if (monom.Ratio > 0)
			stream << monom.Ratio;

		if (monom.Rank > 0) {
			stream << monom.variable << "^" << monom.Rank;
		}
		else stream << " ";
	}

	return stream;
}

/// <summary>
/// Оператор вывода
/// </summary>
/// <param name="stream"></param>
/// <param name="cells"></param>
/// <returns></returns>
std::ostream& operator<< (std::ostream& stream, const Polinom& polinom) {

	for (Monom monom : polinom) {
		cout << monom;
	}

	return stream;
}

/// <summary>
/// Выводит полином в виде строки.
/// </summary>
/// <param name="pol"></param>
void PrintPolinom(ptrPolinom pol) {
	cout << "\t";
	for (Monom monom : *pol) {
		cout << monom;
	}
	cout << "\n";
}


