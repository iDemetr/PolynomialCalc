#pragma once

#include "pch.h"
#include "Header.h"
#include "ParsePolinoms.h"
#include "PrintPolinoms.h"

#include <algorithm>

using namespace std;

#pragma region --- ��� ������� ---

/// <summary>
/// �������� ���������
/// </summary>
/// <param name="p1"></param>
/// <param name="p2"></param>
/// <returns></returns>
ptrPolinom SumPol(const ptrPolinom p1, const ptrPolinom p2) {

	ptrPolinom output = new Polinom;

	// ������ �� �������������� �������.
	vector<Monom> setDifference1, setDifference2;

	set_difference(p1->begin(), p1->end(), p2->begin(), p2->end(), std::back_inserter(setDifference1));
	set_difference(p2->begin(), p2->end(), p1->begin(), p1->end(), std::back_inserter(setDifference2));

	for (Monom monom1 : *p1) {
		for (Monom monom2 : *p2) {
			if (monom1 == monom2 && monom1.Ratio + monom2.Ratio != 0) {
				output->insert({ monom1.Ratio + monom2.Ratio, monom1.Rank, monom1.variable });
				break;
			}
		}
	}

	// � �������������� ������� ����������� �� �������������� ������
	output->insert(setDifference1.begin(), setDifference1.end());
	output->insert(setDifference2.begin(), setDifference2.end());

	return  output;
}

/// <summary>
/// ������� ���������
/// </summary>
/// <param name="p1"></param>
/// <param name="p2"></param>
/// <returns></returns>
ptrPolinom SubtractPol(const ptrPolinom p1, const ptrPolinom p2) {

	ptrPolinom output = new Polinom;

	// ������ �� �������������� �������.
	vector<Monom> setDifference1, setDifference2;

	set_difference(p1->begin(), p1->end(), p2->begin(), p2->end(), std::back_inserter(setDifference1));
	set_difference(p2->begin(), p2->end(), p1->begin(), p1->end(), std::back_inserter(setDifference2));

	for (Monom monom1 : *p1) {
		for (Monom monom2 : *p2) {
			if (monom1 == monom2) {
				output->insert({ monom1.Ratio - monom2.Ratio, monom1.Rank, monom1.variable });
				break;
			}
		}
	}

	// � �������������� ������� ����������� �� �������������� ������
	output->insert(setDifference1.begin(), setDifference1.end());
	output->insert(setDifference2.begin(), setDifference2.end());

	for (auto a : *output) {
		if (a.Ratio == 0) {
			output->erase(a);
		}
	}

	return  output;
}

/// <summary>
/// ������������ ���������
/// </summary>
/// <param name="pol1"></param>
/// <param name="pol2"></param>
/// <returns></returns>
ptrPolinom MultiPol(const ptrPolinom pol1, const ptrPolinom pol2) {

	ptrPolinom resMulti = new Polinom(),
		tmp = nullptr,				// ��������� �� ����� �����, ��� ������� ����� ���������� �������� 
		sum = nullptr;
	string variable = "";
	int step(0);

	for (Monom monom1 : (*pol1)) {
		for (Monom monom2 : (*pol2)) {
			if (monom1.Ratio != 0 && monom2.Ratio != 0)
				variable = monom1.variable == monom2.variable ? monom2.variable : monom1.variable + monom2.variable;

			resMulti->insert({ monom1.Ratio * monom2.Ratio, monom1.Rank + monom2.Rank, variable });
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

/// <summary>
/// ��������� ��������� ���� ��������� ������� ������� � ��������
/// </summary>
/// <param name="pol1">�������</param>
/// <param name="pol2">��������</param>
/// <returns></returns>
ptrPolinom DivisionPol(const ptrPolinom pol1, const ptrPolinom pol2) {

	Monom HightMonom;
	vector<Monom> divisible;	

	if ((*(pol1->begin())).Rank != 0) {
		int rank = 0;
		// ���������� �������� �������� � ������, ���� ����������� ���� �� ����� 0.
		while (rank != (*(pol1->begin())).Rank ) {
			divisible.push_back(Monom(0, rank++));
		}
	}

	// ���������� ������� ������ ������� �������� ��������, ������� ������ � �������������� 0
	for (auto x = pol1->begin(); x != pol1->end(); ++x) {
		if (divisible.empty()) {
			divisible.push_back(*x);
			//x++;
		}
		else if ((*x).Rank - 1 == divisible.back().Rank) {
			divisible.push_back(*x);			
		}
		else {
			while (divisible.back().Rank + 1 != (*x).Rank) {
				divisible.push_back(Monom(0, divisible.back().Rank+1));
			}
			divisible.push_back(*x);
		}
		HightMonom = *x;
	}

	int Spine = 0;						// ���������� ��������.
	for (auto x : *pol2) {				// ��������� �������� ������ ��� ��������� ����������� ��������
		Spine = -x.Ratio;
		break;
	}

	int last = 0;
	vector<int> TableGorner;

	// ���������� ������� �������, ������� �� �������� �����
	for (auto monom = divisible.rbegin(); monom != divisible.rend(); monom++) {
		TableGorner.push_back((*monom).Ratio + last * Spine);
		last = TableGorner.back();
	}

	int Rank = HightMonom.Rank - 1;
	// �������������� ������� ������������ ��������������� �������� � ������ ��������
	ptrPolinom result = new Polinom();
	for (auto x : TableGorner) {
		if (x != 0) {
			if (Rank < 0) {
				result->insert({x,Rank--,ToString(*pol2)});
			}
			else
				result->insert({x,Rank--,HightMonom.variable});
		}
	}

	if (last == 0) {
		cout << "\n ������� ��� �������.";
	}
	else {
		cout << "\n ������� �� �������: " << last;	
	}

	return result;
}

/// <summary>
/// ���������� �������
/// </summary>
/// <param name="pol1"></param>
/// <param name="pol2"></param>
/// <returns></returns>
ptrPolinom PowPol(const ptrPolinom pol1, const ptrPolinom pol2) {

	// ��������� �������
	int pow = (*(pol2->begin())).Ratio;

	ptrPolinom resPow = pol1;

	for (size_t i = 1; i < pow; i++) {
		resPow = MultiPol(resPow, pol1);
	}

	return resPow;
}

#pragma endregion


ptrPolinom CulcSwitch(ptrPolinom, char, ptrPolinom);
ptrPolinom CompleteBuff(BYTE, Buffer&, ptrPolinom, bool);

ptrPolinom Calc(Tasks* tasks) {

	string sPol1 = "";
	string sPol2 = "";
	ptrPolinom vPol1 = nullptr;
	ptrPolinom vPol2 = nullptr;
	ptrPolinom resTask = nullptr;

	Buffer buffer;

	Task* task;
	Task taskLast;

	if (tasks == nullptr)
		return nullptr;

	// �������� - ��������-�� ������� ������ ������������� � ������ ��������� ����������� ����������, 
	// ������� ������� ���������� � ������ ������� � ����������� ����������� �� ������� ����
	auto isMulti = [](Task* task) {
		return (get<Operator>(*task) == '*' && get<Pol1>(*task) != "" && get<Pol2>(*task) != "");
		};

	// �������� - ��������-�� ������� ������ ������ � ������ ��������� ����������� ����������, 
	// ������� ������� ���������� � ������ ������� � ����������� ����������� �� ������� ����
	auto isSum = [](Task* task) {
		return (get<Operator>(*task) == '+' && get<Pol2>(*task) == "");
		};

	cout << "\n\n ==========================  ���������� ========================== \n";

	while (!tasks->empty()) {

		task = &tasks->top();

		#pragma region --- ����������� ��� �������� �� ����� ���� ��� ���������� ������� ---

		// ������ ���������� �������� ���� � �����.
		if (get<Layer>(*task) > get<Layer>(taskLast) || isMulti(task)) {	//
			if (resTask != nullptr) {
				buffer.push({ get<Layer>(taskLast),get<Operator>(taskLast), resTask });
				cout << "\n �����������: ";
				cout << "\n ���������: " << (int)get<Layer>(taskLast) << " ������������� ��������� �� ����: " << *resTask;
			}
		}
		// ���� ����� ������ ���� �� ���� - ��������� ��� �������� �� ������ � ������� ����� � ������������
		else if (get<Layer>(*task) < get<Layer>(taskLast)) {
			resTask = CompleteBuff(get<Layer>(*task), buffer, resTask, true);
		}
		// ���� ����� ������ �������� ���������� - ��������� ��� �������� �� ������ � ����� �� �����.
		else if (isSum(task) && !buffer.empty()) {
			resTask = CompleteBuff(get<Layer>(*task), buffer, resTask, false);
		}

		#pragma endregion

		#pragma region --- �������� ---

		sPol2 = get<Pol2>(*task);
		if (sPol2 != "")
			vPol2 = CreatePolinom(ParseMonoms(sPol2));
		else {
			vPol2 = resTask;
		}

		sPol1 = get<Pol1>(*task);
		if (sPol1 != "")
			vPol1 = CreatePolinom(ParseMonoms(sPol1));
		else {
			taskLast = *task;
			tasks->pop();							// �������� ������
			resTask = vPol2;						// ���� ������� ������� ������ ��� ������ - ������� �� ��������� ������ ��� ���������
			continue;
		}

		#pragma endregion

		resTask = CulcSwitch(vPol1, get<Operator>(*task), vPol2);

		taskLast = *task;
		tasks->pop();
	}

	cout << "\n\n =====================  ���������� ��������� ===================== \n";
	cout << "\n ���������:  " << *resTask << endl << endl;

	return resTask;
}

/// <summary>
/// ������������ ��������� �� �������� ������� � ����������� �� ��������� ���������
/// </summary>
/// <param name="pol1">			����� �������</param>
/// <param name="operation">	��������</param>
/// <param name="pol2">			������ �������</param>
/// <returns></returns>
ptrPolinom CulcSwitch(ptrPolinom pol1, char operation, ptrPolinom pol2) {

	ptrPolinom resTask = nullptr;

	cout << "\n\n ����������: \t";
	PrintPolinoms(*pol1, operation, *pol2);

	switch (operation)
	{
	case addition:
		resTask = SumPol(pol1, pol2);
		break;

	case subtraction:
		resTask = SubtractPol(pol1, pol2);
		break;

	case multiplication:
		resTask = MultiPol(pol1, pol2);
		break;

	case division:
		resTask = DivisionPol(pol1, pol2);
		break;

	case poww:
		resTask = PowPol(pol1, pol2);
		break;

	default:
		break;
	}

	cout << "\n ���������: " << *resTask;
	return resTask;
}

/// <summary>
/// ��������� ��� ���������� ���������� �� �������� ����.
/// </summary>
/// <param name="layer"></param>
/// <param name="buffer"></param>
/// <param name="pol1"></param>
/// <returns></returns>
ptrPolinom CompleteBuff(BYTE layer, Buffer& buffer, ptrPolinom pol1, bool flag = false) {

	auto buff = &buffer.top();

	if (buff->layer > layer && !flag)
		throw new exception("��������� ������������������ ���������� ��������!");

	while (((buff->layer == layer && !flag) || (buff->layer >= layer && flag)) && !buffer.empty()) {
		pol1 = CulcSwitch(pol1, buff->operation, buff->polinom);
		buffer.pop();
		if (!buffer.empty())
			buff = &buffer.top();
		else
			break;
	}

	return pol1;
}