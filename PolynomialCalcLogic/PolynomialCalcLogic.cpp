#include "Header.h"
//#include "ParsePolinoms.h"
#include "CreateTask.h"
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

//#define _DEBUG

#ifdef NDEBUG

	_getch(); system("cls");

	int s(0), a;
	enum menu { ReadTask = '1', ReadHistory, quit = 27 };
	menu ss;
	Tasks* tasks;

	do {

		cout << "\n Ввести пример с полиномами                      (1)";
		cout << "\n Считывание истории введенных полиномов из файла (2)";
		cout << "\n Выйти из программы                             (esc)";

		while (ss = (menu)_getch(), s != quit);

		switch (ss) {
		case ReadTask:
			cout << "\n Введите полином: ";
			getline(cin, spolinom);
			tasks = CreateTasks(spolinom);
			Calc(tasks);
			break;
		case ReadHistory:
			break;
		case quit:
			cout << "\n Завершение прогрммы.";
			break;
		}

	} while (ss != quit);


#else

	//spolinom = ("(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7)) - (2x + 1) - (x + 3x^2) + (3x^3 + 1) + (3x^5 + 3)*(x^3) ");
	//spolinom = "(x^2 + 2x + 1) - (x^4 - 7x^3 - x + 10)^3";
	//spolinom = "(x^2 + 2x + 1) - (x^4 - 7x^3 - x + 10)^3 * (x^3 + 3x + 3) + (x^5 + 5x + 5)";
	//spolinom = "(x^2 + 2x + 1) - (x^4 - 7x^3 - x + 10)^3 + ((x^3 + 3x + 3) + (x^5 + 5x + 5))";
	//spolinom = "(x^2 + 2x + 1) - (x^4 - 7x^3 - x + 10)^3 + ((x^3 + 3x + 3)^2 + (x^5 + 5x + 5))";
	spolinom = "(x^2 + 2x + 1) - (x^4 - 7x^3 - x + 10)^3 + ((x^3 + 3x + 3)+ (x^5 + 5x + 5)^2) + (x^2 + 2x + 2)";	// Ошибка в уровне последнего полинома

	auto tasks = CreateTasks(spolinom);
	Calc(tasks);

#endif // _DEBUG



	//spolinom = "(x + 2x^2) * ((2x + 3x^3 - 4x^4) + (5x^4 + 6x^6))";
	//spolinom = "(x^2 + 2x + 1) * (x^3 - 7x + 5)";
	//spolinom = "(x^2 + 2x + 1) - (x^4 - 7x^3 - x + 10)";

	// yes  Foo("(x + 2x^2) * ((2x + 3x^3 - 4x^4) + (5x^4 + 6x^6))");
	//CreateTasks("(x + 2x^2) - ((2x + 3x^3 - 4x^4) - (5x^4 + 6x^6))");
	// yes  Foo("(x + 2x^2) * ((2x + 3x^3 - 4x^4) + (5x^4 + 6x^6) + (5x^7 + 6x^8))");
	//CreateTasks("(x + 2x^2) * ((2x + 3x^3 - 4x^4) - (5x^4 + 6x^6) + (5x^7 + 6x^8))");
	//CreateTasks("(x + 2x^2) * ((2x + 3x^3 - 4x^4) + (5x^4 + 6x^6) - (5x^7 + 6x^8))");
	// yes  Foo("(x + 2x^2) * ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^7 + 6x^8))");
	// yes  Foo("(x + 2x^2) * ((2x + 3x^3 - 4x^4) - (5x^4 + 6x^6) * (5x^7 + 6x^8))");
	// yes  Foo("(x + 2x^2) * ((2x + 3x^3 - 4x^4) - (5x^4 + 6x^6) - (5x^7 + 6x^8))");
	// yes  Foo("(x + 2x^2) - (2x + 3x^3 - 4x^4) + (5x^4 + 6x^6)");
	//CreateTasks("(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7)) - (2x + 1)");

	//CreateTasks("(x^4+2x) + ((x+1) + (2x+1) * (x^10) * (12x^2 + 23))");
	//CreateTasks("(x + 2x^2) - (2x + 1) - (x + 3x^2) + (3x^3 + 1) + (3x^5 + 3)*(x^3) ");

	//CreateTasks("(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7)) - (2x + 1) - (x + 3x^2) + (3x^3 + 1) + (3x^5 + 3)*(x^3) ");
	
	//CreateTasks("(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7))/(2x + 1)"); // + добавить проверку на множество действий после группы
	//CreateTasks("(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7))/(2x + 1) + (234x + 43) - ((114x + 222)+(2x^2 + 1))");
}



