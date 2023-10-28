#pragma once

#include "Header.h"
#include "PrintPolinoms.h"

using namespace std;


/// <summary>
/// ������ ������� �� ������ �������
/// </summary>
/// <param name="sPolinom"></param>
/// <returns></returns>
std::vector<string> ParseMonoms(string sPolinom) {
	std::vector<string> list;
	int pos(0), numPolinom(0);
	string value, lastValue;

	cout << "\n ������������� �������:  ";

	// ������� ��������� ������ � ��������� � ������ �� �������
	do {
		pos = sPolinom.find_first_of(" ");											// ��������� ����������� �� ���������� ��������� ������� � ��������
		value = sPolinom.substr(0, pos);											// ��������� ������
		sPolinom = sPolinom.substr(pos + 1, sPolinom.length());						// ������� �� ������ ������������ �����

		if (value != "+") {

			if (lastValue == "-") {													// �������� ������������� ��������
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
/// ����������� ������ ������� � �������
/// �������� ��������� �������������������� ���������
/// </summary>
/// <param name="LMonoms"></param>
/// <returns></returns>
ptrPolinom CreatePolinom(std::vector<string> LMonoms) {

	string variable = "";
	string  value;
	int rank(0);

	ptrPolinom polinom = new Polinom();

	cout << "\n ������ ��������: ";

	try {
		for (string var : LMonoms) {
			bool isDegree = false, isVariable = false;
			value = "";

			// ���� �� �����
			for (char ch : var) {
				// ���� ������� � ����� �� ���� ���������
				if (!isDegree && ch != '^') {
					// ���� �������� ���������� �� ���� ���������
					if (!isVariable) {
						rank = 0;
						// ���� ������ ����� ��� ���� �����
						if (ch >= '0' && ch <= '9' || ch == '-') value += ch;

						// ���� ��������� ����� - ������ ��� ���������� ��������
						else if (!isVariable) {
							isVariable = true;
							variable = ch;
							if (value == "" || value == "-" ) value += "1";
							rank = 1;
						}
						else if (variable[0] != ch)
							throw exception("\t ������! ������ ����� ����������");
					}
					// ��������� ������, ���� ����� ������� ���������� �� �������� ������ �������
					else throw exception("\t ������! �������� ������ ��������");
				}

				// ���� ��������� ����������� �������
				else {
					// ������������� ������� �������
					if (isDegree) {
						// ���� � ������� �������� �������� ������ �� �����
						if (ch >= '0' && ch <= '9') {
							rank *= 10;
							rank += ch - '0';
						}
						else throw exception("\t ������! �������� ������ ��������");
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

