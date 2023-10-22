#pragma once

#include "Header.h"

using namespace std;

//vector<vector<string>>
void CreateTasks(string sPolinom) {
	stack<int> skob;															// ���� �������� ������
	vector<vector<int>*>* polinoms = new vector<vector<int>*>();				// ������ ������ ���������

	// byte - ����� ���� (�����������), char - ��������, string* - ����� �������, string* - ������ �������
	stack <tuple<byte, string, char, string>> Task;								// ���� ������������������ �������� � ����������
	enum ETask { Layer, Pol1, Operator, Pol2 };

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
						get<Pol2>(Task.top()) = FindPolinom;
					}
					else {
						Task.push({ skob.size(), FindPolinom, noOperator, "" });
						isGroup = false;
					}
					isOperation = false;
				}
				else throw exception("������ � ������ ��������.");
			}

			// ���������� ������ �������� � ���������������� ����������� ��������
			else if (isEndPolinom && (ch == addition || ch == subtraction)) {
				isEndPolinom = false;

				// ���� �� ���� �� ���� ����� ���������� ��������������
				if (!isHightPriority && !isLowPriority) {

					// ���� ������ ������ ������� �� ����
					if (get<Operator>(Task.top()) == noOperator) {		// || ch == subtraction �� ������, ���� � ������ ��� ��� ����, � �� ���������� �� �����
						get<Operator>(Task.top()) = ch;
						isOperation = true;
					}
					else {

						// ����� ������, ���� ����� ���� �������� ��� ����������
						if (get<Operator>(Task.top()) == subtraction || get<Layer>(Task.top()) != skob.size()) {
							Task.push({ skob.size(), "",  ch, "" });
							isOperation = true;
						}

						// ���� ���� �����
						else {
							if (get<Pol1>(Task.top()) == "")
								Task.pop();
							else
								get<Pol2>(Task.top()) = "";


							Task.push({ skob.size(), FindPolinom , ch, "" });
							isOperation = true;
						}
					}
				}

				// ���� ����� ���� ������������/������� - ����� ����� ������
				else {
					Task.push({ skob.size(), "" , ch, "" });
					isOperation = true;
				}

				isHightPriority = isLowPriority = false;
			}
			
			// ���� �������� ����������� ����������
			else if (isEndPolinom && (ch == multiplication || ch == division)) {

				isEndPolinom = false;
				isLowPriority = !(isHightPriority = ch == multiplication);

				if (get<Operator>(Task.top()) == noOperator) {
					get<Operator>(Task.top()) = ch;
					isOperation = true;
				}
				else if (get<Layer>(Task.top()) == skob.size()) {
					get<Pol2>(Task.top()) = "";
					Task.push({ skob.size(), FindPolinom, ch , "" });
					isOperation = true;
				}
			}
		}
	}
	catch (const std::exception& e) {
		cout << "\n\t Error: " << e.what() << endl;
	}
	delete polinoms;
}

