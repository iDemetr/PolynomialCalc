#include "Header.h"
#include <stack>
#include <tuple>

using namespace std;

enum command { poww = '^', multiplication = '*', division = '/', addition = '+', subtraction = '-' };

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

	Foo(spolinom);

	//LMonoms = ParseMonoms(spolinom);
	//vector<int>* polinom = (CreatePolinom(LMonoms));

	std::cout << "Hello World!\n";
}

//vector<vector<string>>
void Foo(string sPolinom) {
	stack<int> skob;															// стек открытых скобок
	vector<vector<int>*>* polinoms = new vector<vector<int>*>();				// Список матриц полиномов
	stack <tuple<char, vector<int>*, vector<int>*>> Actions;

	bool isEndPolinom = false;
	bool isAction = false;

	try {
		for (int i = 0; i < sPolinom.length(); i++) {

			// Встречено начало полинома или группы полиномов
			if (sPolinom[i] == '(') {
				skob.push(i);

				// Если встречена группа
				if (skob.size() > 1) isAction = true;
			}

			// Встречено окончание полинома
			else if (sPolinom[i] == ')') {
				if (skob.size() != NULL) {
					string a = sPolinom.substr(skob.top() + 1, i - 1 - skob.top());
					// Преобразование строки с полиномом в матрицу
					polinoms->push_back(CreatePolinom(ParseMonoms(a)));
					skob.pop();

					isEndPolinom = true;

					// Если в слое вводится второй полином
					if (isAction) {
						//auto [ch, vec1, vec2] = Actions.top();
						//(Actions.top()).get<2>() = polinoms->back();
						get<2>(Actions.top()) = polinoms->back();
						//Actions.top() = { get<0>(Actions.top()), get<1>(Actions.top()), polinoms->back() };

						isAction = false;
						//isEndPolinom = false;
					}
				}
				else throw exception("Ошибка в записи полинома.");
			}

			// Ввод последующих полиномов
			else if (isEndPolinom && isAction && (sPolinom[i] == multiplication || sPolinom[i] == division ||
				sPolinom[i] == addition || sPolinom[i] == subtraction))
			{
				isEndPolinom = false;
				auto a = (*polinoms).back();
				vector<int>* vec1 = a;
				//Actions.top()({ sPolinom[i], vec1, NULL });
			}

			// Если введён первый полином
			else if (isEndPolinom && (sPolinom[i] == multiplication || sPolinom[i] == division ||
				sPolinom[i] == addition || sPolinom[i] == subtraction))
			{
				isEndPolinom = false;
				auto a = (*polinoms).back();
				vector<int>* vec1 = a;
				Actions.push({ sPolinom[i], vec1, NULL });
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


