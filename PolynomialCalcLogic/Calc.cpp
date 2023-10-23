#pragma once

#include "Header.h"
#include "ParsePolinoms.h"

#include <algorithm>

using namespace std;

#pragma region --- Мат функции ---


ptrPolinom SumPol(const ptrPolinom p1, const ptrPolinom p2) {
	
	ptrPolinom output = new Polinom;

	vector<Monom> setDifference1, setDifference2;

	set_difference(p1->begin(), p1->end(), p2->begin(), p2->end(), std::back_inserter(setDifference1));
	set_difference(p2->begin(), p2->end(), p1->begin(), p1->end(), std::back_inserter(setDifference2));

	for (Monom monom1 : *p1) {
		for (Monom monom2 : *p2) {
			if (monom1 == monom2) {
				output->insert({ monom1.Ratio + monom2.Ratio, monom1.Rank });
				break;
			}
		}
	}

	output->insert(setDifference1.begin(), setDifference1.end());
	output->insert(setDifference2.begin(), setDifference2.end());
		
	return  output;
}

ptrPolinom SubtractPol(ptrPolinom p1, ptrPolinom p2) {

	ptrPolinom output = new Polinom;

	vector<Monom> setDifference1, setDifference2;

	set_difference(p1->begin(), p1->end(), p2->begin(), p2->end(), std::back_inserter(setDifference1));
	set_difference(p2->begin(), p2->end(), p1->begin(), p1->end(), std::back_inserter(setDifference2));

	for (Monom monom1 : *p1) {
		for (Monom monom2 : *p2) {
			if (monom1 == monom2) {
				output->insert({ monom1.Ratio - monom2.Ratio, monom1.Rank });
				break;
			}
		}
	}

	output->insert(setDifference1.begin(), setDifference1.end());
	output->insert(setDifference2.begin(), setDifference2.end());

	return  output;
}

ptrPolinom MultiPol(ptrPolinom pol1, ptrPolinom pol2) {

	ptrPolinom resMulti = new Polinom();
	ptrPolinom tmp = nullptr;				// Указатель на новую сумму, для очистки суммы предыдущей итерации 
	ptrPolinom sum = nullptr;
	string variable = "";
	int step(0);

	for (Monom monom1 : (*pol1)) {
		for (Monom monom2 : (*pol2)) {
			if (monom1.Ratio != 0 && monom2.Ratio != 0)
				variable = monom1.variable == monom2.variable ? monom2.variable : monom1.variable + monom2.variable;

			resMulti->insert({ monom1.Ratio * monom2.Ratio, monom1.Rank + monom2.Rank });
		}

		if (sum != nullptr) {
			tmp = SumPol(sum, resMulti);
			delete sum;
			sum = tmp;
		}
		else { sum = resMulti; }
		resMulti = new Polinom();
	}

	return sum;
}

#pragma endregion


ptrPolinom Calc(stack <tuple<byte, string, char, string>>* Tasks) {

	string sPol1 = "", sPol2 = "";
	ptrPolinom vPol1 = NULL, vPol2 = NULL, resTask = nullptr;

	if (Tasks == nullptr)
		return nullptr;

	while (Tasks->size() != 0) {

		auto Task = Tasks->top();

		#pragma region --- Селектор ---

		sPol2 = get<Pol2>(Task);
		if (sPol2 != "")
			vPol2 = CreatePolinom(ParseMonoms(sPol2));
		else {
			vPol2 = resTask;
		}

		sPol1 = get<Pol1>(Task);
		if (sPol1 != "")
			vPol1 = CreatePolinom(ParseMonoms(sPol1));		
		else if (sPol1 == "") {
			Tasks->pop();
			continue;
		}

		#pragma endregion


		cout << "\n Вычисление: \n\t";
		if(get<Pol1>(Task) != "")
			cout << get<Pol1>(Task) << " " << get<Operator>(Task) << " " << get<Pol2>(Task);
		else if(resTask != nullptr && get<Pol1>(Task) != "")
			cout << get<Pol1>(Task) << " " << get<Operator>(Task) << " " << resTask;
		else if(resTask != nullptr && get<Pol2>(Task) != "")
			cout << resTask << " " << get<Operator>(Task) << " " << get<Pol2>(Task);
			

		switch (get<Operator>(Task))
		{
		case addition:
			resTask = SumPol(vPol1, vPol2);
			break;

		case subtraction:
			resTask = SubtractPol(vPol1, vPol2);
			break;

		case multiplication:
			resTask = MultiPol(vPol1, vPol2);
			break;

		case division:
			//resTask = SumPol(vPol1, vPol2);
			break;

		default:
			break;
		}

		cout << "\n Результат: " << (*resTask);

		Tasks->pop();
	}

	return resTask;
}
