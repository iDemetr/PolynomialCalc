﻿
#include "pch.h"
#include "Header.h"
#include "CreateTask.h"
#include "WorkWithFile.h"
#include "Calc.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "\n\t Добро пожаловать в калькулятор полиномов!";
	cout << "\n-----------------------------------------------------";
	cout << "\n\n Для начала работы, нажмите любую клавишу...";

	string spolinom;

//#define NDEBUG

#ifdef NDEBUG

	_getch(); system("cls");

	int s(0), a;
	enum menu { ReadTask = '1', ReadHist, quit = 27 };
	menu ss;
	Tasks* tasks;

	do {

		cout << "\n Ввести пример с полиномами                      (1)";
		cout << "\n Загрузить историю введенных полиномов из файла  (2)";
		cout << "\n Выйти из программы                             (esc)";

		while (ss = (menu)_getch(), (ss < ReadTask || ss > ReadHist) && ss != quit);

		switch (ss) {
		case ReadTask: {
			cout << "\n Введите полином: ";
			getline(cin, spolinom);

			tasks = CreateTasks(spolinom);
			auto result = Calc(tasks);

			SaveHistory(spolinom, result);
			break;
		}
		
		case menu::ReadHist: {
			system("cls");
			cout << "\n Выберите номер задачи для повторного ввода: ";

			auto History = ReadHistory();
			int num;
			while (num = _getch()-'0', (num < 1 || num > History.size()) && num != quit);

			if (num != quit) {
				spolinom = History[num - 1].first;
				tasks = CreateTasks(spolinom);
				Calc(tasks);
			}
			break;
		}
		
		case quit: {
				cout << "\n Завершение программы.";
				break;
			}
		}

	} while (ss != quit);


#else

	//spolinom = "(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7)) - (2x + 1) - (x + 3x^2) + (3x^3 + 1) + (3x^5 + 3)*(x^3) ";
	// они одинаковые spolinom = "(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7)) - (2x + 1)";
		
	// error spolinom = "(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7))/(2x + 1)"; // + добавить проверку на множество действий после группы
	// error spolinom = "(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7))/(2x + 1) + (234x + 43) - ((114x + 222)+(2x^2 + 1))";
	
	auto tasks = CreateTasks(spolinom);
	auto result = Calc(tasks);
	SaveHistory(spolinom, result);

#endif // _DEBUG




}



