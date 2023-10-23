#pragma once

#include "Header.h"

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

	cout << "������������ ������ �������..." << endl;

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

	cout << "�������������� ������ �������:" << endl;
	for (string var : list) {
		cout << var << ", ";
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
tprPolinom CreatePolinom(std::vector<string> LMonoms) {

	string variable = "";
	string  value;
	int rank(0);

	tprPolinom polinom = new Polinom();

	cout << "������������ �������...\n";

	//for (int i = 0; i < 10; i++) {
	//	polinom->push_back(0);
	//}

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

			polinom->push_back({ stoi(value), rank, variable });

			variable = ""; isVariable = false;
		}
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
		throw;
	}

	return polinom;
}

