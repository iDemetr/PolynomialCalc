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
		if (monom.Ratio > 1 || monom.Ratio < 0 || monom.Rank == 0)
			stream << monom.Ratio;

		if (monom.Rank > 1) {
			stream << monom.variable << "^" << monom.Rank;
		}
		else if (monom.Rank == 1) {
			stream << monom.variable;
		}
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
		auto monom = polinom.begin();

		cout << *monom;

		//if (monom->Ratio != 1 || monom->Rank == 0)
		//	stream << monom->Ratio;
		//if (monom->Rank > 1) {
		//	stream << monom->variable << "^";
		//}
		//else if (monom->Rank == 1) {
		//	stream << monom->variable;
		//}		

		// ����� ����������� �������
		while (++monom != polinom.end()) {
			stream << " + " << *(monom);
		}
	}

	return stream;
}

/// <summary>
/// ������� ������� � ���� ������.
/// </summary>
/// <param name="pol"></param>
void PrintPolinoms(const Polinom& pol, const char operation, const Polinom &pol2) {
	cout << "(" << pol << ") " << operation << " (" << pol2 << ")";
}


