#pragma once

#include "Header.h"

using namespace std;

string invertPolynom(string);

/// <summary>
/// Разбиение строки с полиномами на последовательность действий.
/// </summary>
/// <param name="sPolinom"></param>
Tasks* CreateTasks(string sPolinom) {
	//vector<vector<int>*>* polinoms = new vector<vector<int>*>();				// Список матриц полиномов

	stack<int> skob;															// стек открытых скобок
	
	// стек последовательности действий с полиномами
	auto* task = new Tasks;

	bool isEndPolinom(0), isOperation(0), isHightPriority(0), isLowPriority(0), isGroup(0);

	char ch;
	string FindPolinom;

	cout << "\n Формирование последовательности действий...";

	// Добавить проверку, есть ли вообще скобки, мб ввелся только 1 полином
	try {
		for (int i = 0; i < sPolinom.length(); i++) {

			ch = sPolinom[i];

			// Встречено начало полинома или группы полиномов
			if (ch == '(') {
				skob.push(i);

				// Если встречена группировка полиномов - вводится множество
				//if (skob.size() > 1 && skob.size()%2 == 0) 
				if (skob.size() > 1 && sPolinom[i - 1] == ch)
					isGroup = true;
			}

			// Встречено окончание полинома
			else if (ch == ')') {
				if (skob.size() != 0) {

					// Пропуск обработки, если скобки закрылись для группы
					if (skob.size() == 1 && sPolinom[i - 1] == ch) {
						skob.pop();
						isGroup = false;
						continue;
					}

					FindPolinom = sPolinom.substr(skob.top() + 1, i - 1 - skob.top());			// Полином
					skob.pop();
					isEndPolinom = true;

					if (isGroup)
						isHightPriority = isLowPriority = false;

					// Если не новый слой и небыло произведения/деления или холодный запуск 
					if (!isGroup && (isOperation || isHightPriority)) {			// недостаточные условия		
						if (get<Operator>(task->top()) == '-') {
							FindPolinom = invertPolynom(FindPolinom);
							get<Operator>(task->top()) = '+';							
						}
						get<Pol2>(task->top()) = FindPolinom;
					}
					
					// Новый слой - новая задача
					else {
						task->push({ skob.size(), FindPolinom, noOperator, "" });
						isGroup = false;
					}
					
					isOperation = false;
				}
				else throw exception("Ошибка в записи полинома.");
			}

			// Добавление нового полинома с последовательным приоритетом действий
			else if (isEndPolinom && (ch == addition || ch == subtraction)) {

				// Если на слое не было задач повышенной приоритетности
				if (!isHightPriority && !isLowPriority) {

					// Если считан первый полином на слое
					if (get<Operator>(task->top()) == noOperator) {		// || ch == subtraction мб ошибка, если у задачи уже был знак, а он заменяется на отриц
						get<Operator>(task->top()) = ch;
						isOperation = true;
					}

					// Новая задача, если ранее было удаление или групировка
					else if (get<Layer>(task->top()) != skob.size()) { //get<Operator>(Task.top()) == subtraction ||
						task->push({ skob.size(), "",  ch, "" });
						isOperation = true;
					}

					// Если была сумма
					else {
						get<Pol2>(task->top()) = "";
						task->push({ skob.size(), FindPolinom , ch, "" });
						isOperation = true;
					}
				}

				// Если ранее было произведение/деление - нужна новая задача c перестановкой последовательности
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

			// Ввод операций повышенного приоритета
			else if (isEndPolinom && (ch == multiplication || ch == division)) {

				isEndPolinom = false;
				isLowPriority = !(isHightPriority = ch == multiplication);

				if (get<Operator>(task->top()) == noOperator) {
					get<Operator>(task->top()) = ch;
					isOperation = true;
				}
				else if (get<Layer>(task->top()) == skob.size()) {
					get<Pol2>(task->top()) = "";
					task->push({ skob.size(), FindPolinom, ch , "" });
					isOperation = true;
				}
				// Если ранее было произведение/деление - нужна новая задача
				else {
					task->push({ skob.size(), "" , ch, "" });
					isOperation = true;
				}
			}
		}
	}
	catch (const std::exception& e) {
		cout << "\n\t Error: " << e.what() << endl;
	}

	return task;
}

/// <summary>
/// Инвертирует знаки входного полинома
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
