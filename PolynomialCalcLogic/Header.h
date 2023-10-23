#pragma once

#ifndef HEADER_H
#define HEADER_H

#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>		
#include <windows.h>

#include <vector>
#include <stack>
#include <tuple>
#include <set>

enum command { poww = '^', multiplication = '*', division = '/', addition = '+', subtraction = '-' };

// ��������� ��� ������� � ������� � �������, ���:
// Layer - ����� ���� ������, ��� ������ - ���� ��������� ��������
// Pol1 - ����� �������
// Pol2 - ������ �������
enum ETask { Layer, Pol1, Operator, Pol2 };

// ��� ������
struct Monom {
	// ����������� ������
	int Ratio;
	// ������� ������
	int Rank;
	// ��������
	std::string variable = "";

    bool operator<(const Monom& monom) const
    {
        return Rank < monom.Rank;
    }

	//��������� ���������
	bool operator== (const Monom& pol2) {
		return Rank == pol2.Rank;
	}

	bool operator!= (const Monom& pol2) {
		return Rank != pol2.Rank;		
	}
};

// ��� ��������
typedef std::set<Monom> Polinom;
typedef std::set<Monom>* ptrPolinom;

// �������� ��� �������� �����
const int noOperator = -1;

#endif HEADER_H