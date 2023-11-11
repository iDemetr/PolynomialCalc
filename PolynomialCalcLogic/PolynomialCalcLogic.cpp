
#include "pch.h"
#include "Header.h"
#include "CreateTask.h"
#include "WorkWithFile.h"
#include "Calc.h"

using namespace std;

void fillBuff(std::string value, INPUT_RECORD*& irec) {
	size_t len = value.length();
	int y = 0;
	
	//INPUT_RECORD irec[50];
	//irec = {};
	for (int i = 0; i < (2 * len) - 1; i += 2) {
		irec[i].EventType = KEY_EVENT;
		irec[i].Event.KeyEvent.bKeyDown = TRUE;
		irec[i].Event.KeyEvent.dwControlKeyState = 0;
		irec[i].Event.KeyEvent.uChar.AsciiChar = int(value[y]);
		irec[i].Event.KeyEvent.wRepeatCount = 1;
		irec[i].Event.KeyEvent.wVirtualKeyCode = (value[y]); /* virtual keycode is always uppercase */
		irec[i].Event.KeyEvent.wVirtualScanCode = MapVirtualKeyA(irec[i].Event.KeyEvent.wVirtualKeyCode & 0x00ff, 0);
		irec[i + 1].EventType = KEY_EVENT;
		irec[i + 1].Event.KeyEvent.bKeyDown = FALSE;
		irec[i + 1].Event.KeyEvent.dwControlKeyState = 0;
		irec[i + 1].Event.KeyEvent.uChar.AsciiChar = int(value[y]);
		irec[i + 1].Event.KeyEvent.wRepeatCount = 1;
		irec[i + 1].Event.KeyEvent.wVirtualKeyCode = toupper(value[y]);
		irec[i + 1].Event.KeyEvent.wVirtualScanCode = MapVirtualKeyA(irec[i + 1].Event.KeyEvent.wVirtualKeyCode & 0x00ff, 0);
		y++;
	}
}

void aaa() {
	HANDLE hConIn = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwTmp;
	INPUT_RECORD ir[4];

	ir[0].EventType = KEY_EVENT;
	ir[0].Event.KeyEvent.bKeyDown = TRUE;
	ir[0].Event.KeyEvent.dwControlKeyState = 0;
	ir[0].Event.KeyEvent.uChar.UnicodeChar = 'u';
	ir[0].Event.KeyEvent.wRepeatCount = 1;
	ir[0].Event.KeyEvent.wVirtualKeyCode = 'U';
	ir[0].Event.KeyEvent.wVirtualScanCode = MapVirtualKey('U', MAPVK_VK_TO_VSC);

	ir[1].EventType = KEY_EVENT;
	ir[1].Event.KeyEvent.bKeyDown = TRUE;
	ir[1].Event.KeyEvent.dwControlKeyState = 0;
	ir[1].Event.KeyEvent.uChar.UnicodeChar = 'c';
	ir[1].Event.KeyEvent.wRepeatCount = 1;
	ir[1].Event.KeyEvent.wVirtualKeyCode = 'C';
	ir[1].Event.KeyEvent.wVirtualScanCode = MapVirtualKey('C', MAPVK_VK_TO_VSC);

	ir[2].EventType = KEY_EVENT;
	ir[2].Event.KeyEvent.bKeyDown = TRUE;
	ir[2].Event.KeyEvent.dwControlKeyState = 0;
	ir[2].Event.KeyEvent.uChar.UnicodeChar = 'i';
	ir[2].Event.KeyEvent.wRepeatCount = 1;
	ir[2].Event.KeyEvent.wVirtualKeyCode = 'I';
	ir[2].Event.KeyEvent.wVirtualScanCode = MapVirtualKey('I', MAPVK_VK_TO_VSC);

	ir[3].EventType = KEY_EVENT;
	ir[3].Event.KeyEvent.bKeyDown = TRUE;
	ir[3].Event.KeyEvent.dwControlKeyState = 0;
	ir[3].Event.KeyEvent.uChar.UnicodeChar = '\n';
	ir[3].Event.KeyEvent.wRepeatCount = 1;
	ir[3].Event.KeyEvent.wVirtualKeyCode = '\n';
	ir[3].Event.KeyEvent.wVirtualScanCode = MapVirtualKey('\n', MAPVK_VK_TO_VSC);

	dwTmp = 0;
	WriteConsoleInput(hConIn, ir, 4, &dwTmp);
}

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
				try
				{
					//aaa();

					//DWORD dw;
					//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					//INPUT_RECORD* records = new INPUT_RECORD[(2 * spolinom.length()) - 1];// = new INPUT_RECORD[50];
					//
					//fillBuff(spolinom, records);
					////WriteConsole(hConsole, records, spolinom.length(),&dw);
					//
					//stream
					//streambuf* strbuff = new streambuf();
					//
					//cin.set_rdbuf(strbuff);

					//COORD startPosition = { 0, 0 };
					//DWORD numberOfCharsWritten;
					//WriteConsoleOutputCharacter(hConsole, spolinom, spolinom.length(), startPosition, &numberOfCharsWritten);	
				}
				catch (const std::exception& e)
				{

				}
				//std::cin.set_rdbuf(new streambuf((spolinom.c_str()));

				tasks = CreateTasks(spolinom);
				Calc(tasks);
			}
			break;
		}
		
		case quit:
			cout << "\n Завершение программы.";
			break;
		}

	} while (ss != quit);


#else

	//spolinom = ("(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7)) - (2x + 1) - (x + 3x^2) + (3x^3 + 1) + (3x^5 + 3)*(x^3) ");
	//spolinom = "(x^2 + 2x + 1) - (x^4 - 7x^3 - x + 10)^3";
	//spolinom = "(x^2 + 2x + 1) - (x^4 - 7x^3 - x + 10)^3 * (x^3 + 3x + 3) + (x^5 + 5x + 5)";
	//spolinom = "(x^2 + 2x + 1) - (x^4 - 7x^3 - x + 10)^3 + ((x^3 + 3x + 3) + (x^5 + 5x + 5))";
	//spolinom = "(x^2 + 2x + 1) - (x^4 - 7x^3 - x + 10)^3 + ((x^3 + 3x + 3)^2 + (x^5 + 5x + 5))";
	
	//spolinom = "(x + 2x^2) * ((2x + 3x^3 - 4x^4) + (5x^4 + 6x^6))";
	//spolinom = "(x^2 + 2x + 1) * (x^3 - 7x + 5)";
	//spolinom = "(x^2 + 2x + 1) - (x^4 - 7x^3 - x + 10)";

	//spolinom = "(x + 2x^2) * ((2x + 3x^3 - 4x^4) + (5x^4 + 6x^6))";
	//spolinom = "(x + 2x^2) - ((2x + 3x^3 - 4x^4) - (5x^4 + 6x^6))";
	//spolinom = "(x + 2x^2) * ((2x + 3x^3 - 4x^4) + (5x^4 + 6x^6) + (5x^7 + 6x^8))";
	//spolinom = "(x + 2x^2) * ((2x + 3x^3 - 4x^4) - (5x^4 + 6x^6) + (5x^7 + 6x^8))";
	//spolinom = "(x + 2x^2) * ((2x + 3x^3 - 4x^4) + (5x^4 + 6x^6) - (5x^7 + 6x^8))";
	
	//spolinom = "(x + 2x^2) * ((2x + 3x^3 - 4x^4) - (5x^4 + 6x^6) * (5x^7 + 6x^8))";
	//spolinom = "(x + 2x^2) * ((2x + 3x^3 - 4x^4) - (5x^4 + 6x^6) - (5x^7 + 6x^8))";
	//spolinom = "(x + 2x^2) - (2x + 3x^3 - 4x^4) + (5x^4 + 6x^6)";

	spolinom = "(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7)) - (2x + 1) - (x + 3x^2) + (3x^3 + 1) + (3x^5 + 3)*(x^3) ";
	// они одинаковые spolinom = "(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7)) - (2x + 1)";

	// error spolinom ="(x^4+2x) + ((x+1) + (2x+1) * (x^10) * (12x^2 + 23))";	
	// error spolinom = "(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7))/(2x + 1)"; // + добавить проверку на множество действий после группы
	// error spolinom = "(x + 2x^2) + ((2x + 3x^3 - 4x^4) * (5x^4 + 6x^6) + (5x^3 + 6x^7))/(2x + 1) + (234x + 43) - ((114x + 222)+(2x^2 + 1))";
	

	auto tasks = CreateTasks(spolinom);
	auto result = Calc(tasks);
	SaveHistory(spolinom, result);

#endif // _DEBUG




}



