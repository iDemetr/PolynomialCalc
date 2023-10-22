#include "Header.h"
#include <stack>
#include <tuple>

using namespace std;

enum command { poww = '^', multiplication = '*', division = '/', addition = '+', subtraction = '-' };
const int noOperator = -1;

void Foo(string);
vector<string> ParseMonoms(string);
vector<int>* CreatePolinom(vector<string>);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "\n\t Добро пожаловать в калькулятор полиномов!";
	cout << "------------------------------------------------------------------------------------------------------";
	cout << "\n\n Для начала работы, нажмите любую клавишу...";

	_getch(); system("cls");

	string spolinom;
	//	vector<string> LMonoms;


	cout << "\n Введите полином: ";
	//getline(cin, spolinom);
	//spolinom = "2x + 3x^3 - 4x^4 + 5x^5 + 6x^6";
	spolinom = "(x + 2x^2) * ((2x + 3x^3 - 4x^4) + (5x^4 + 6x^6))";

	// yes  Foo("(x + 2x^2) * ((2x + 3x^3 - 4x^4) + (5x^4 + 6x^6))");
	// yes  Foo("(x + 2x^2) - ((2x + 3x^3 - 4x^4) - (5x^4 + 6x^6))");
	// yes  Foo("(x + 2x^2) * ((2x + 3x^3 - 4x^4) + (5x^4 + 6x^6) + (5x^7 + 6x^8))");
	// yes  Foo("(x + 2x^2) * ((2x + 3x^3 - 4x^4) - (5x^4 + 6x^6) + (5x^7 + 6x^8))");
	// yes  Foo("(x + 2x^2) * ((2x + 3x^3 - 4x^4) + (5x^4 + 6x^6) - (5x^7 + 6x^8))");
	// yes  Foo("(x + 2x^2) * ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^7 + 6x^8))");
	// yes  Foo("(x + 2x^2) * ((2x + 3x^3 - 4x^4) - (5x^4 + 6x^6) * (5x^7 + 6x^8))");
	// yes  Foo("(x + 2x^2) * ((2x + 3x^3 - 4x^4) - (5x^4 + 6x^6) - (5x^7 + 6x^8))");
	// yes  Foo("(x + 2x^2) - (2x + 3x^3 - 4x^4) + (5x^4 + 6x^6)");
	// yes  Foo("(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7)) - (2x + 1)");
	
	// yes  Foo("(x^4+2x) + ((x+1) + (2x+1) * (x^10) * (12x^2 + 23))");

	// no Foo("(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7))/(2x + 1)"); // + добавить проверку на множество действий после группы

	//LMonoms = ParseMonoms(spolinom);
	//vector<int>* polinom = (CreatePolinom(LMonoms));

	std::cout << "Hello World!\n";
}

//vector<vector<string>>
void Foo(string sPolinom) {
	stack<int> skob;															// стек открытых скобок
	vector<vector<int>*>* polinoms = new vector<vector<int>*>();				// Список матриц полиномов

	// byte - номер слоя (вложенности), char - оператор, string* - левый операнд, string* - правый операнд
	stack <tuple<byte, string, char, string>> Task;								// стек последовательности действий с полиномами
	enum ETask {Layer, Pol1, Operator, Pol2};									

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
				if(skob.size() > 1 && sPolinom[i - 1] == ch)
					isGroup = true;
			}

			// Встречено окончание полинома
			else if (ch == ')') {
				if (skob.size() != 0) {

					// Пропуск обработки, если скобки закрылись для группы
					if (skob.size() == 1 && sPolinom[i-1] == ch) {
						skob.pop();
						isGroup = false;
						continue;
					}

					FindPolinom = sPolinom.substr(skob.top() + 1, i - 1 - skob.top());			// Полином
					skob.pop();
					isEndPolinom = true;
					
					if(isGroup)
						isHightPriority = isLowPriority = false;

					// Если в слое вводится второй полином и не было встречено действия с повышенным приоритетом
					if (!isGroup && (isOperation || isHightPriority)) {			// недостаточные условия						
							get<Pol2>(Task.top()) = FindPolinom;
					}
					else {
						Task.push({ skob.size(), FindPolinom, noOperator, "" });
						isOperation = false;
						isGroup = false;
					}

				}
				else throw exception("Ошибка в записи полинома.");
 			}

			// Добавление нового полинома с последовательным приоритетом действий
			else if (isEndPolinom && (ch == addition || ch == subtraction)) {
				isEndPolinom = false;

				// Если на слое не было задач повышенной приоритетности
				if (!isHightPriority && !isLowPriority) {
					if (get<Operator>(Task.top()) == noOperator ) {		// || ch == subtraction мб ошибка, если у задачи уже был знак, а он заменяется на отриц
						get<Operator>(Task.top()) = ch;
						isOperation = true;						
					}
					else {
						if (get<Operator>(Task.top()) == subtraction || get<Layer>(Task.top()) != skob.size()) {
							Task.push({ skob.size(), "",  ch, ""});
							isOperation = true;
						}
						else {
							get<Pol2>(Task.top()) = "";
							Task.push({ skob.size(), FindPolinom , ch, "" });
							isOperation = true;
						}
					}
				}
				else {
					Task.push({ skob.size(), "" , ch, ""});
				}

				isHightPriority = isLowPriority = false;
			}
			// Ввод полиномов повышенного приоритета
			else if (isEndPolinom && (ch == multiplication || ch == division)) {

				isEndPolinom = false;
				isLowPriority =	!(isHightPriority = ch == multiplication);

				if (get<Operator>(Task.top()) == noOperator) {
					get<Operator>(Task.top()) = ch;
					isOperation = true;
				}
				//if (get<Operator>(Task.top()) == subtraction) {
				//	Task.push({ skob.size(), "",  ch, "" });
				//}
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

/// <summary>
/// Парсит полином на список мономов
/// </summary>
/// <param name="sPolinom"></param>
/// <returns></returns>
vector<string> ParseMonoms(string sPolinom) {
	vector<string> list;
	int pos(0), numPolinom(0);
	string value, lastValue;

	cout << "Формирование списка монопов..." << endl;

	// Парсинг введенной строки с разбиеним в список по мономам
	do {
		pos = sPolinom.find_first_of(" ");											// Временное ограничение на разделение пробелами мономов и действий
		value = sPolinom.substr(0, pos);											// Получение монома
		sPolinom = sPolinom.substr(pos + 1, sPolinom.length());						// Удаляем из строки распаршенную часть

		if (value != "+") {

			if (lastValue == "-") {													// Фиксация отрицательных значений
				list.push_back("-" + value);
			}
			else if (value != "-") { list.push_back(value); }

			lastValue = value;
		}
	} while (pos != -1);

	cout << "Сформированный список мономов:" << endl;
	for (string var : list) {
		cout << var << ", ";
	}
	cout << "\n";

	return list;
}

/// <summary>
/// Преобразует список мономов в матрицу
/// Добавить поддержку многопараметрических полиномов
/// </summary>
/// <param name="LMonoms"></param>
/// <returns></returns>
vector<int>* CreatePolinom(vector<string> LMonoms) {

	char variable = ' ';
	string  value;
	int rank(0);

	vector<int>* polinom = new vector<int>();

	cout << "Формирование матрицы...\n";

	for (int i = 0; i < 10; i++) {
		polinom->push_back(0);
	}

	try {
		for (string var : LMonoms) {
			bool isDegree = false, isVariable = false;
			value = "";

			// Цикл по слову
			for (char ch : var) {
				// Если степень в слове не была встречена
				if (!isDegree && ch != '^') {
					// Если название переменной не было встречено
					if (!isVariable) {
						rank = 1;
						// Если символ число или знак числа
						if (ch >= '0' && ch <= '9' || ch == '-') value += ch;

						// Если встречена буква - значит это переменная полинома
						else if (!isVariable) {
							isVariable = true;
							variable = ch;
							if (value == "") value += "1";
							rank = 2;
						}
						else if (variable != ch)
							throw exception("\t Ошибка! Больше одной переменных");
					}
					// Генерация ошибки, если после встречи переменной не встречен символ степени
					else throw exception("\t Ошибка! Неверная запись полинома");
				}

				// Если встречено определение степени
				else {
					// Игнорирование символа степени
					if (isDegree) {
						// Если в степени встречен отличный символ от цифры
						if (ch >= '0' && ch <= '9') {
							rank *= 10;
							rank += ch - '0';
						}
						else throw exception("\t Ошибка! Неверная запись полинома");
					}
					else {
						rank = 0;
						isDegree = true;
					}
				}
			}
			(*polinom)[rank - 1] = stoi(value);
		}
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}

	return polinom;
}


