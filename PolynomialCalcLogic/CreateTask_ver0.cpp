#pragma once

#include "pch.h"
#include "Header.h"

using namespace std;

void readPow(int&, string, Tasks*);
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

			switch (ch) 
			{
				// Встречен символ начала группы
			case '[': {
				skob.push(i);
				isGroup = true;
				break;
			}

					// Встречен символ окончания группы
			case ']': {
				isGroup = false;
				skob.pop();
				break;
			}

					// Встречено начало полинома или группы полиномов
			case '(': {
				skob.push(i);

				// Если встречена группировка полиномов - вводится множество
				if (skob.size() > 1 && sPolinom[i - 1] == ch)
					isGroup = true;
				else
					isGroup = false;
				break;
			}

					// Встречено окончание полинома
			case ')': {
				if (skob.size() != 0) {

					// Пропуск обработки, если скобки закрылись для группы
					if ((skob.size() > 1 || task->size() > 1) && !isOperation) {
 						skob.pop();
						isGroup = true;			// Установка флага об окончании группы для логики степени
						//isEndPolinom = false;
						continue;
					}

					FindPolinom = sPolinom.substr(skob.top() + 1, i - 1 - skob.top());			// Полином
					skob.pop();
					isEndPolinom = true;

					if (isGroup)
						isHightPriority = isLowPriority = false;

					// Если не новый слой и была операция произведения/деления или не холодный запуск 
					if (!isGroup && (isOperation || isHightPriority)) {			// недостаточные условия		
						if (get<Operator>(task->top()) == '-') {
							FindPolinom = invertPolynom(FindPolinom);
							get<Operator>(task->top()) = '+';
						}
						get<Pol2>(task->top()) = FindPolinom;
					}

					// Новый слой или понижение приоритета - новая задача
					else {
						task->push({ skob.size(), FindPolinom, noOperator, "" });
						isGroup = false;
					}

					isOperation = false;
				}
				else throw exception("Ошибка в записи полинома.");
				break;
			}
			
			default:
				// Если был встречен конец полинома или слоя
				if (isEndPolinom) {
					// Добавление нового полинома с последовательным приоритетом действий
					if (ch == addition || ch == subtraction) {

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
					else if (ch == multiplication || ch == division) {

						isEndPolinom = false;
						isLowPriority = !(isHightPriority = ch == multiplication);

						// Если новый слой добавление к последней задачи оператора
						if (get<Operator>(task->top()) == noOperator) {
							get<Operator>(task->top()) = ch;
							isOperation = true;
						}

						// Если новая задача повышенного приоритета на том же слое - новая задача - с миграцией правого операнда с краней задачи
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

					// Ввод степени
					else if (ch == poww) {
						//isEndPolinom = false;

						// Если в степнь возводится 1 полином
						if (!isGroup) {
							readPow(i, sPolinom, task);
							isHightPriority = true;
						}

						// В степень возводится группа полиномов 
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
/// Обрабатывает встреченный знак степени и формирует n-задач
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
			throw new exception("Неверная запись степени, встречен невалидный символ");
				

		if (++iter < sPolinom.length())
			ch = sPolinom[iter];
		else
			break;
	}

	string FindPolinom;
	int i(0);

	// Если считан первый полином на слое
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
	// Плодится стек задач по перемножению полинома на 1 раз меньше
	for (; i < stoi(iPow) - 1; i++) {
		task->push({ layer, FindPolinom, multiplication , "" });
	}

	// Добавление потеряшки в последнюю задачу
	get<Pol2>(task->top()) = FindPolinom;
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
