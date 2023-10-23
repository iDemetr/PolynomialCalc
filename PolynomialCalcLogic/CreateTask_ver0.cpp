#pragma once

#include "Header.h"

using namespace std;

string invertPolynom(string);

/// <summary>
/// ��������� ������ � ���������� �� ������������������ ��������.
/// </summary>
/// <param name="sPolinom"></param>
stack <tuple<byte, string, char, string>>* CreateTasks(string sPolinom) {
	//vector<vector<int>*>* polinoms = new vector<vector<int>*>();				// ������ ������ ���������

	stack<int> skob;															// ���� �������� ������
	
	// byte - ����� ���� (�����������), char - ��������, string* - ����� �������, string* - ������ ������
	// ���� ������������������ �������� � ����������
	auto* Task = new stack <tuple<byte, string, char, string>>;

	bool isEndPolinom(0), isOperation(0), isHightPriority(0), isLowPriority(0), isGroup(0);

	char ch;
	string FindPolinom;

	// �������� ��������, ���� �� ������ ������, �� ������ ������ 1 �������
	try {
		for (int i = 0; i < sPolinom.length(); i++) {

			ch = sPolinom[i];

			// ��������� ������ �������� ��� ������ ���������
			if (ch == '(') {
				skob.push(i);

				// ���� ��������� ����������� ��������� - �������� ���������
				//if (skob.size() > 1 && skob.size()%2 == 0) 
				if (skob.size() > 1 && sPolinom[i - 1] == ch)
					isGroup = true;
			}

			// ��������� ��������� ��������
			else if (ch == ')') {
				if (skob.size() != 0) {

					// ������� ���������, ���� ������ ��������� ��� ������
					if (skob.size() == 1 && sPolinom[i - 1] == ch) {
						skob.pop();
						isGroup = false;
						continue;
					}

					FindPolinom = sPolinom.substr(skob.top() + 1, i - 1 - skob.top());			// �������
					skob.pop();
					isEndPolinom = true;

					if (isGroup)
						isHightPriority = isLowPriority = false;

					// ���� �� ����� ���� � ������ ������������/������� ��� �������� ������ 
					if (!isGroup && (isOperation || isHightPriority)) {			// ������������� �������		
						if (get<Operator>(Task->top()) == '-') {
							FindPolinom = invertPolynom(FindPolinom);
							get<Operator>(Task->top()) = '+';							
						}
						get<Pol2>(Task->top()) = FindPolinom;
					}
					
					// ����� ���� - ����� ������
					else {
						Task->push({ skob.size(), FindPolinom, noOperator, "" });
						isGroup = false;
					}
					
					isOperation = false;
				}
				else throw exception("������ � ������ ��������.");
			}

			// ���������� ������ �������� � ���������������� ����������� ��������
			else if (isEndPolinom && (ch == addition || ch == subtraction)) {

				// ���� �� ���� �� ���� ����� ���������� ��������������
				if (!isHightPriority && !isLowPriority) {

					// ���� ������ ������ ������� �� ����
					if (get<Operator>(Task->top()) == noOperator) {		// || ch == subtraction �� ������, ���� � ������ ��� ��� ����, � �� ���������� �� �����
						get<Operator>(Task->top()) = ch;
						isOperation = true;
					}

					// ����� ������, ���� ����� ���� �������� ��� ����������
					else if (get<Layer>(Task->top()) != skob.size()) { //get<Operator>(Task.top()) == subtraction ||
						Task->push({ skob.size(), "",  ch, "" });
						isOperation = true;
					}

					// ���� ���� �����
					else {
						get<Pol2>(Task->top()) = "";
						Task->push({ skob.size(), FindPolinom , ch, "" });
						isOperation = true;
					}
				}

				// ���� ����� ���� ������������/������� - ����� ����� ������
				else {
					Task->push({ skob.size(), "" , ch, "" });
					isOperation = true;
				}

				isHightPriority = isLowPriority = false;
				isEndPolinom = false;
			}

			// ���� �������� ����������� ����������
			else if (isEndPolinom && (ch == multiplication || ch == division)) {

				isEndPolinom = false;
				isLowPriority = !(isHightPriority = ch == multiplication);

				if (get<Operator>(Task->top()) == noOperator) {
					get<Operator>(Task->top()) = ch;
					isOperation = true;
				}
				else if (get<Layer>(Task->top()) == skob.size()) {
					get<Pol2>(Task->top()) = "";
					Task->push({ skob.size(), FindPolinom, ch , "" });
					isOperation = true;
				}
				// ���� ����� ���� ������������/������� - ����� ����� ������
				else {
					Task->push({ skob.size(), "" , ch, "" });
					isOperation = true;
				}
			}
		}
	}
	catch (const std::exception& e) {
		cout << "\n\t Error: " << e.what() << endl;
	}

	return Task;
}

/// <summary>
/// ����������� ����� �������� ��������
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
string invertPolynom(string str) {

	string output = "";
	int i(0);

	try {
		if (str[0] == '-') { i = 1; }
		else { output += "-"; }

		for (; i < str.size(); i++) {
			switch (str[i]) {
			case '+':
				output += "-";
				break;

			case '-':
				output += "+";
				break;

			default:
				output += str[i];
				break;
			}
		}
	}
	catch (const std::exception& e)
	{
		cout << "\t Error: " << e.what() << endl;
	}
	return output;
}
