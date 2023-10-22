#include "Header.h"
#include "ParsePolinoms.h"
#include "CreateTask.h"

using namespace std;



//void Foo(string);
//vector<string> ParseMonoms(string);
//vector<int>* CreatePolinom(vector<string>);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "\n\t Добро пожаловать в калькулятор полиномов!";
	cout << "-------------------------------------------------------------------------------------";
	cout << "\n\n Для начала работы, нажмите любую клавишу...";

	//_getch(); system("cls");

	string spolinom;

	cout << "\n Введите полином: ";
	//getline(cin, spolinom);
	//spolinom = "(x + 2x^2) * ((2x + 3x^3 - 4x^4) + (5x^4 + 6x^6))";

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
	// yes  Foo("(x + 2x^2) - (2x + 1) - (x + 3x^2) + (3x^3 + 1) + (3x^5 + 3)*(x^3) ");

	CreateTasks("(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7)) - (2x + 1) - (x + 3x^2) + (3x^3 + 1) + (3x^5 + 3)*(x^3) ");
	// no  Foo("(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7))/(2x + 1)"); // + добавить проверку на множество действий после группы

	//LMonoms = ParseMonoms(spolinom);
	//vector<int>* polinom = (CreatePolinom(LMonoms));

	std::cout << "Hello World!\n";
}

