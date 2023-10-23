#pragma once

#include "Header.h"

using namespace std;

string invertPolynom(string);

/// <summary>
/// Разбиение строки с полиномами на последовательность действий.
/// </summary>
/// <param name="sPolinom"></param>
stack <tuple<byte, string, char, string>>* CreateTasks(string sPolinom) {
	//vector<vector<int>*>* polinoms = new vector<vector<int>*>();				// Список матриц полиномов

	stack<int> skob;															// стек открытых скобок
	
	// byte - номер слоя (вложенности), char - оператор, string* - левый операнд, string* - правый перанд
	// стек последовательности действий с полиномами
	auto* Task = new stack <tuple<byte, string, char, string>>;

	bool isEndPolinom(0), isOperation(0), isHightPriority(0), isLowPriority(0), isGroup(0);

	char ch;
	string FindPolinom;

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
						if (get<Operator>(Task->top()) == '-') {
							FindPolinom = invertPolynom(FindPolinom);
							get<Operator>(Task->top()) = '+';							
						}
						get<Pol2>(Task->top()) = FindPolinom;
					}
					
					// Новый слой - новая задача
					else {
						Task->push({ skob.size(), FindPolinom, noOperator, "" });
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
					if (get<Operator>(Task->top()) == noOperator) {		// || ch == subtraction мб ошибка, если у задачи уже был знак, а он заменяется на отриц
						get<Operator>(Task->top()) = ch;
						isOperation = true;
					}

					// Новая задача, если ранее было удаление или групировка
					else if (get<Layer>(Task->top()) != skob.size()) { //get<Operator>(Task.top()) == subtraction ||
						Task->push({ skob.size(), "",  ch, "" });
						isOperation = true;
					}

					// Если была сумма
					else {
						get<Pol2>(Task->top()) = "";
						Task->push({ skob.size(), FindPolinom , ch, "" });
						isOperation = true;
					}
				}

				// Если ранее было произведение/деление - нужна новая задача
				else {
					Task->push({ skob.size(), "" , ch, "" });
					isOperation = true;
				}

				isHightPriority = isLowPriority = false;
				isEndPolinom = false;
			}

			// Ввод операций повышенного приоритета
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
				// Если ранее было произведение/деление - нужна новая задача
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
