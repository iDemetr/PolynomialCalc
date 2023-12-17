#pragma once

#include "pch.h"
#include "Header.h"

using namespace std;

std::ostream& operator<< (std::ostream& stream, const Monom& monom) {

	if (monom.Ratio != 0) {
		if ((monom.Ratio > 1 || monom.Ratio < 0 || monom.Rank == 0) && monom.Rank > -1)
			stream << std::to_string(monom.Ratio);

		if (monom.Rank > 1) {
			stream << monom.variable << "^" << monom.Rank;
		}
		else if (monom.Rank == 1) {
			stream << monom.variable;
		}		
		// Если степень отрицательная - значит моном образовался в результате деления и является остатком.
		else if (monom.Rank < 0) {
			stream << std::to_string(monom.Ratio) << " / (" << monom.variable << ")";
		}
	}

	return stream;
}

std::ostream& operator<< (std::ostream& stream, const Polinom& polinom) {

	if (!polinom.empty()) {
		
		// Вывод первого монома
		auto monom = polinom.begin();

		stream << *monom;

		// Вывод последующих мономов
		while (++monom != polinom.end()) {
			stream << " + " << *monom;
		}
	}

	return stream;
}

void PrintPolinoms(const Polinom& pol, const char operation, const Polinom &pol2) {
	cout << "(" << pol << ") " << operation << " (" << pol2 << ")";
}

string ToString(const Monom& monom) {
	string str = "";
	if (monom.Ratio != 0) {
		if ((monom.Ratio > 1 || monom.Ratio < 0 || monom.Rank == 0) && monom.Rank > -1)
			str = std::to_string(monom.Ratio);

		if (monom.Rank > 1) {
			str += monom.variable + "^" + std::to_string(monom.Rank);
		}
		else if (monom.Rank == 1) {
			str += monom.variable;
		}
		// Если степень отрицательная - значит моном образовался в результате деления и является остатком.
		else if (monom.Rank < 0) {
			str += std::to_string(monom.Ratio) + " / (" + monom.variable + ")";
		}
	}

	return str;
}

string ToString(const Polinom& pol) {
	
	std::string str = "";
	
	if (!pol.empty()) {

		// Вывод первого монома
		auto monom = pol.begin();

		str += ToString (*monom);

		// Вывод последующих мономов
		while (++monom != pol.end()) {
			str += " + "; str += ToString(*monom);
		}
	}
		
	return str;
}


