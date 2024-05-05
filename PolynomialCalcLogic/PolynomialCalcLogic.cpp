
#include "pch.h"
#include "Header.h"
#include "CreateTask.h"
#include "WorkWithFile.h"
#include "Calc.h"

using namespace std;

int ReadNumHist();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "\n\t Добро пожаловать в калькулятор полиномов!";
	cout << "\n-----------------------------------------------------";
	cout << "\n\n Для начала работы, нажмите любую клавишу...";

	string spolinom;

	//#define NDEBUG

#ifndef DEBUG

	_getch(); system("cls");

	int s(0), a;
	enum menu { ReadTask = '1', DivMode, ReadHist, quit = 27 };
	menu ss;
	Tasks* tasks;

	do {
		cout << "\n Режим мат. операций без деления                 (1)";
		cout << "\n Режим деления полиномов                         (2)";
		cout << "\n Загрузить историю введенных полиномов из файла  (3)";
		cout << "\n Выйти из программы                             (esc)";

		while (ss = (menu)_getch(), (ss < ReadTask || ss > ReadHist) && ss != quit);

		switch (ss) {
		case menu::ReadTask: {
			cout << "\n Введите полином: ";
			getline(cin, spolinom);
			if (spolinom == "esc" || spolinom == "")
				break;

			try {
				tasks = CreateTasks(spolinom);
				auto result = Calc(tasks);

				SaveHistory(spolinom, result);
			}
			catch (const std::exception* e) {
				std::cout << e->what();
			}
			catch (...){}
			break;
		}

		case menu::DivMode: {
			system("cls");
			cout << "\n Этот режим предназначен для выполнения операции деления по схеме Горнера,";
			cout << "\n где:    делитель - полином первого порядка, ";
			cout << "\n         делимое - полином любого порядка ";
			bool flag = true;
			do {
				cout << "\n Введите полином: ";				
				getline(cin, spolinom);
				if (spolinom == "esc" || spolinom == "")
					break;

				try {
					tasks = CreateTasks(spolinom);

					if (tasks->size() > 1) {
						cout << "\n Ввёденный полином содержит больше одной операции.";
						cout << "\n Выбранный режим пользволяет осуществить только деление между двумя полиномами.";
						continue;
					}
					else {
						flag = false;
						auto result = Calc(tasks);
						SaveHistory(spolinom, result);
					}
				}
				catch (const std::exception* e) {
					std::cout << e->what();					
				}
				catch (...) { break; }

			} while (flag);
			break;
		}

		case menu::ReadHist: {
			system("cls");
			cout << "\n Выберите номер задачи для повторного ввода: ";

			auto History = ReadHistory();
			if (History.size() != 0) {
				int num;
				while (num = ReadNumHist(), (num < 1 || num > History.size()) && num != -1);

				if (num != -1) {
					std::cout << "\n Выбран пример №" << num << ".";
					std::cout << "\n Расчёты: " << History[num - 1].first << ".";
					spolinom = History[num - 1].first;
					tasks = CreateTasks(spolinom);
					Calc(tasks);
				}
			}
			else {
				std::cout << "\n Файл истории пуст.";
			}
			break;
		}

		case menu::quit: {
			cout << "\n Завершение программы.";
			break;
		}
		}

	} while (ss != menu::quit);


#else

	//spolinom = "(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7)) - (2x + 1) - (x + 3x^2) + (3x^3 + 1) + (3x^5 + 3)*(x^3) ";
	// они одинаковые spolinom = "(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7)) - (2x + 1)";

	// error spolinom = "(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7))/(2x + 1)"; // + добавить проверку на множество действий после группы
	// error spolinom = "(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7))/(2x + 1) + (234x + 43) - ((114x + 222)+(2x^2 + 1))";

	//spolinom = "(x + 2x^2)/(x + 1)";
	spolinom = "(x^2 + 2x + 1) - (x^4 - 7x^3 - x + 10)^3 + ((x^3 + 3x + 3)+ (x^5 + 5x + 5)^2) + (x^2 + 2x + 2)";

	auto tasks = CreateTasks(spolinom);
	auto result = Calc(tasks);
	SaveHistory(spolinom, result);

#endif // _DEBUG

}

/// <summary>
/// Считывает номер предложения
/// </summary>
/// <returns></returns>
int ReadNumHist() {

	bool isRepit = true;
	int menu;
	string buff = "";
	do {
		getline(cin, buff);
		if (buff == "esc" || buff == "") {
			return -1;
			break;
		}

		try {
			menu = std::stoi(buff);
			isRepit = false;
		}
		catch (exception& e) {}

	} while (isRepit);

	return menu;
}


