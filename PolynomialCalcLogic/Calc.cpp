#pragma once

#include "Header.h"
#include "ParsePolinoms.h"

#include <set>

using namespace std;

#pragma region --- Мат функции ---


tprPolinom SumPol(tprPolinom pol1, tprPolinom pol2) {
		
	tprPolinom pol = new Polinom();
	bool isAdded = false;

	// Временный буфер потеряшек
	tprPolinom tmp = new Polinom();

	for (Monom monom1 : *pol1) {
		for (Monom monom2 : *pol2) {
			if (monom1.Rank == monom2.Rank) {
				pol->push_back({ monom1.Ratio + monom2.Ratio, monom1.Rank });
				
				tmp->push_back(monom2);			// Пересечение коллекций
				
				isAdded = true;
				break;
			}
		}

		// Если моном не был найден во втором полиноме.
		if (!isAdded) {
			isAdded = false;
			pol->push_back(monom1);
		}
	}

	isAdded = false;
	// Разница коллекций
	for (Monom monom2 : *pol2) {
		for(Monom a : *tmp) {
			if (a.Rank == monom2.Rank) {
				isAdded = true;
				break;
			}
		}

		if (!isAdded) {
			pol->push_back(monom2);
			isAdded = false;
		}
	}

	// Нужна сортировка

	return pol;
}

tprPolinom SubtractPol(tprPolinom pol1, tprPolinom pol2) {
	tprPolinom pol = new Polinom();
	bool isAdded = false;

	// Временный буфер потеряшек
	tprPolinom tmp = new Polinom();

	for (Monom monom1 : *pol1) {
		for (Monom monom2 : *pol2) {
			if (monom1.Rank == monom2.Rank) {
				pol->push_back({ monom1.Ratio - monom2.Ratio, monom1.Rank });

				tmp->push_back(monom2);			// Пересечение коллекций

				isAdded = true;
				break;
			}
		}

		// Если моном не был найден во втором полиноме.
		if (!isAdded) {
			isAdded = false;
			pol->push_back(monom1);
		}
	}

	isAdded = false;
	// Разница коллекций
	for (Monom monom2 : *pol2) {
		for (Monom a : *tmp) {
			if (a.Rank == monom2.Rank) {
				isAdded = true;
				break;
			}
		}

		if (!isAdded) {
			pol->push_back(monom2);
			isAdded = false;
		}
	}

	// Нужна сортировка

	return pol;
}

tprPolinom MultiPol(tprPolinom pol1, tprPolinom pol2) {

	tprPolinom resMulti = new Polinom();
	tprPolinom tmp = nullptr;				// Указатель на новую сумму, для очистки суммы предыдущей итерации 
	tprPolinom sum = nullptr;
	string variable = "";
	int step(0);

	for (int i = 0; i < pol1->size(); i++) {
		for (int j = 0; j < pol2->size(); j++) {
			if ((*pol1)[i].Ratio != 0 && (*pol2)[j].Ratio != 0)

				variable = (*pol1)[i].variable == (*pol2)[j].variable ? (*pol2)[j].variable : (*pol1)[i].variable + (*pol2)[j].variable;

			resMulti->push_back({ (*pol1)[i].Ratio * (*pol2)[j].Ratio, (*pol1)[i].Rank + (*pol2)[j].Rank });
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


tprPolinom Calc(stack <tuple<byte, string, char, string>>* Tasks) {

	string sPol1 = "", sPol2 = "";
	tprPolinom vPol1 = NULL, vPol2 = NULL, resTask = nullptr;

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
		Tasks->pop();
	}

	return resTask;
}
