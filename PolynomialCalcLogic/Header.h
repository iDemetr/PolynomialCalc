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
};

// ��� ��������
typedef std::vector<Monom> Polinom;
typedef std::vector<Monom>* tprPolinom;

// �������� ��� �������� �����
const int noOperator = -1;


#endif HEADER_H