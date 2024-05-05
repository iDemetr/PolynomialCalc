#pragma once

#include "pch.h"
#include "Header.h"

using namespace std;

int readPow(int&, const string&);
void AddTaskPow(int&, const string&, Tasks*);
string invertPolynom(string);


Tasks* CreateTasks(string sPolinom) {

	stack<int> skob;															// ���� �������� ������

	// ���� ������������������ �������� � ����������
	auto* task = new Tasks;

	bool isEndPolinom(0), isOperation(0), isHightPriority(0), isLowPriority(0), isGroup(0);

	char ch;
	string FindPolinom;

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
				else throw new exception("\n ������ � ������ ��������.\n");
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
							AddTaskPow(i, sPolinom, task);
							isHightPriority = true;
						}

						// � ������� ���������� ������ ��������� 
						else if (isGroup) {
							task->push({ skob.size(), "", ch, std::to_string(readPow(i,sPolinom))});
							isHightPriority = true;
						}

					}
				}
				
				break;
			}
		}

		if (get<Pol2>(task->top()) == "") {
			throw new exception("\n ����� ������ ���� �������, �������� ���� ��� ������� ���� ��������� � ���. ����������.\n");
		}
	}
	
	catch (const std::exception& e) {
		cout << "\n\t Error: " << e.what() << endl;
		throw;
	}
	
	catch (...) { throw; }

	return task;
}

/// <summary>
/// ������������ ����������� ���� �������
/// </summary>
/// <param name="iter"></param>
/// <param name="sPolinom"></param>
int readPow(int& iter, const string &sPolinom) {

	string iPow;
	char ch;
	iter++;
	do {
		ch = sPolinom[iter];

		if (ch > '0' && ch < '9') iPow += ch;
		else if (ch == ')') {
			iter--; break;
		}
		else
			throw new exception("\n �������� ������ �������, �������� ���������� ������.\n");
				
	} while (++iter < sPolinom.length() && ch != ' ');

	return stoi(iPow);
}

/// <summary>
/// ��������� n-���� ����� ������������ �������� � �������
/// </summary>
/// <param name="iter"></param>
/// <param name="sPolinom"></param>
/// <param name="task"></param>
void AddTaskPow(int& iter, const string &sPolinom, Tasks* task) {

	string FindPolinom;
	int i(0);
	int pow = readPow(iter, sPolinom);

	int layer = get<Layer>(task->top()) + 1;

	// ���� ������ ������ ������� �� ����
	if (get<Operator>(task->top()) == noOperator) {
		get<Operator>(task->top()) = multiplication;
		get<Layer>(task->top()) += 1;
		FindPolinom = get<Pol1>(task->top());
		i = 1;
	}
	else {
		FindPolinom = get<Pol2>(task->top());
		get<Pol2>(task->top()) = "";
	}

	// �������� ���� ����� �� ������������ �������� �� 1 ��� ������
	for (; i < pow - 1; i++) {
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
