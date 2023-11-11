#pragma once

#include "pch.h"
#include "Header.h"

using namespace std;

void readPow(int&, string, Tasks*);
string invertPolynom(string);

/// <summary>
/// ��������� ������ � ���������� �� ������������������ ��������.
/// </summary>
/// <param name="sPolinom"></param>
Tasks* CreateTasks(string sPolinom) {
	//vector<vector<int>*>* polinoms = new vector<vector<int>*>();				// ������ ������ ���������

	stack<int> skob;															// ���� �������� ������

	// ���� ������������������ �������� � ����������
	auto* task = new Tasks;

	bool isEndPolinom(0), isOperation(0), isHightPriority(0), isLowPriority(0), isGroup(0);

	char ch;
	string FindPolinom;

	cout << "\n ������������ ������������������ ��������...";

	// �������� ��������, ���� �� ������ ������, �� ������ ������ 1 �������
	try {
		for (int i = 0; i < sPolinom.length(); i++) {

			ch = sPolinom[i];

			switch (ch) 
			{
				// �������� ������ ������ ������
			case '[': {
				skob.push(i);
				isGroup = true;
				break;
			}

					// �������� ������ ��������� ������
			case ']': {
				isGroup = false;
				skob.pop();
				break;
			}

					// ��������� ������ �������� ��� ������ ���������
			case '(': {
				skob.push(i);

				// ���� ��������� ����������� ��������� - �������� ���������
				if (skob.size() > 1 && sPolinom[i - 1] == ch)
					isGroup = true;
				else
					isGroup = false;
				break;
			}

					// ��������� ��������� ��������
			case ')': {
				if (skob.size() != 0) {

					// ������� ���������, ���� ������ ��������� ��� ������
					if ((skob.size() > 1 || task->size() > 1) && !isOperation) {
 						skob.pop();
						isGroup = true;			// ��������� ����� �� ��������� ������ ��� ������ �������
						//isEndPolinom = false;
						continue;
					}

					FindPolinom = sPolinom.substr(skob.top() + 1, i - 1 - skob.top());			// �������
					skob.pop();
					isEndPolinom = true;

					if (isGroup)
						isHightPriority = isLowPriority = false;

					// ���� �� ����� ���� � ���� �������� ������������/������� ��� �� �������� ������ 
					if (!isGroup && (isOperation || isHightPriority)) {			// ������������� �������		
						if (get<Operator>(task->top()) == '-') {
							FindPolinom = invertPolynom(FindPolinom);
							get<Operator>(task->top()) = '+';
						}
						get<Pol2>(task->top()) = FindPolinom;
					}

					// ����� ���� ��� ��������� ���������� - ����� ������
					else {
						task->push({ skob.size(), FindPolinom, noOperator, "" });
						isGroup = false;
					}

					isOperation = false;
				}
				else throw exception("������ � ������ ��������.");
				break;
			}
			
			default:
				// ���� ��� �������� ����� �������� ��� ����
				if (isEndPolinom) {
					// ���������� ������ �������� � ���������������� ����������� ��������
					if (ch == addition || ch == subtraction) {

						// ���� �� ���� �� ���� ����� ���������� ��������������
						if (!isHightPriority && !isLowPriority) {

							// ���� ������ ������ ������� �� ����
							if (get<Operator>(task->top()) == noOperator) {		// || ch == subtraction �� ������, ���� � ������ ��� ��� ����, � �� ���������� �� �����
								get<Operator>(task->top()) = ch;
								isOperation = true;
							}

							// ����� ������, ���� ����� ���� �������� ��� ����������
							else if (get<Layer>(task->top()) != skob.size()) { //get<Operator>(Task.top()) == subtraction ||
								task->push({ skob.size(), "",  ch, "" });
								isOperation = true;
							}

							// ���� ���� �����
							else {
								get<Pol2>(task->top()) = "";
								task->push({ skob.size(), FindPolinom , ch, "" });
								isOperation = true;
							}
						}

						// ���� ����� ���� ������������/������� - ����� ����� ������ c ������������� ������������������
						else {
							//auto tmp = Task->top();
							//Task->pop();
							task->push({ skob.size(), "" , ch, "" });
							//Task->push(tmp);

							isOperation = true;
						}

						isHightPriority = isLowPriority = false;
						isEndPolinom = false;
					}

					// ���� �������� ����������� ����������
					else if (ch == multiplication || ch == division) {

						isEndPolinom = false;
						isLowPriority = !(isHightPriority = ch == multiplication);

						// ���� ����� ���� ���������� � ��������� ������ ���������
						if (get<Operator>(task->top()) == noOperator) {
							get<Operator>(task->top()) = ch;
							isOperation = true;
						}

						// ���� ����� ������ ����������� ���������� �� ��� �� ���� - ����� ������ - � ��������� ������� �������� � ������ ������
						else if (get<Layer>(task->top()) == skob.size()) {
							get<Pol2>(task->top()) = "";
							task->push({ skob.size(), FindPolinom, ch , "" });
							isOperation = true;
						}

						// ���� ����� ���� ������������/������� - ����� ����� ������
						else {
							task->push({ skob.size(), "" , ch, "" });
							isOperation = true;
						}
					}

					// ���� �������
					else if (ch == poww) {
						//isEndPolinom = false;

						// ���� � ������ ���������� 1 �������
						if (!isGroup) {
							readPow(i, sPolinom, task);
							isHightPriority = true;
						}

						// � ������� ���������� ������ ��������� 
						else if (isGroup) {

						}

					}
				}
				
				//if (isGroup) {
				//
				//}
				break;
			}
		}
	}
	catch (const std::exception& e) {
		cout << "\n\t Error: " << e.what() << endl;
	}

	return task;
}

/// <summary>
/// ������������ ����������� ���� ������� � ��������� n-�����
/// </summary>
/// <param name="iter"></param>
/// <param name="sPolinom"></param>
/// <param name="task"></param>
void readPow(int& iter, string sPolinom, Tasks* task) {

	string iPow;
	char ch = sPolinom[++iter];
	while (ch != ' ') {
		if (ch > '0' && ch < '9')
			iPow += ch;
		else if (ch == ')') {
			iter--;
			break;
		}
		else
			throw new exception("�������� ������ �������, �������� ���������� ������");
				

		if (++iter < sPolinom.length())
			ch = sPolinom[iter];
		else
			break;
	}

	string FindPolinom;
	int i(0);

	// ���� ������ ������ ������� �� ����
	if (get<Operator>(task->top()) == noOperator) {
		get<Operator>(task->top()) = multiplication;
		FindPolinom = get<Pol1>(task->top());
		i = 1;
	}
	else {
		FindPolinom = get<Pol2>(task->top());
		get<Pol2>(task->top()) = "";
	}
	
	int layer = get<Layer>(task->top()) + 1;
	// �������� ���� ����� �� ������������ �������� �� 1 ��� ������
	for (; i < stoi(iPow) - 1; i++) {
		task->push({ layer, FindPolinom, multiplication , "" });
	}

	// ���������� ��������� � ��������� ������
	get<Pol2>(task->top()) = FindPolinom;
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
