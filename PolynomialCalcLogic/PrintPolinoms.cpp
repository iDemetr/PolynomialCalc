#pragma once

#include "Header.h"

using namespace std;


/// <summary>
/// �������� ������
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
/// �������� ������
/// </summary>
/// <param name="stream"></param>
/// <param name="cells"></param>
/// <returns></returns>
std::ostream& operator<< (std::ostream& stream, const Polinom& polinom) {

	if (!polinom.empty()) {
		
		// ����� ������� ������
		Monom monom = *polinom.begin();
		if (monom.Ratio < 0)
			stream << "-";
		if (monom.Rank > 0) {
			stream << monom.variable << "^" << monom.Rank;
		}

		// ����� ����������� �������
		for (Monom monom : polinom) {
			stream << monom;
		}
	}

	return stream;
}

/// <summary>
/// ������� ������� � ���� ������.
/// </summary>
/// <param name="pol"></param>
void PrintPolinoms(const Polinom& pol, const char operation, const Polinom &pol2) {
	cout << "(" << pol << ") " << operation << " (" << pol << ")";
}


