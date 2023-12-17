#pragma once

#include "Header.h"
using namespace std;

#ifndef PRINT_POLINOMS_H
#define PRINT_POLINOMS_H

/// <summary>
/// ������� ������� � ���� ������ � �������.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <param name=""></param>
void PrintPolinoms(const Polinom&, const char, const Polinom&);

/// <summary>
/// ����������� ������� � ������ 
/// </summary>
/// <param name=""></param>
/// <returns></returns>
string ToString(const Polinom&);

/// <summary>
/// ����������� ����� � ������ 
/// </summary>
/// <param name=""></param>
/// <returns></returns>
string ToString(const Monom&);

/// <summary>
/// �������� ������ ������
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
std::ostream& operator<< (std::ostream&, const Monom&);
/// <summary>
/// �������� ������ ��������
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
std::ostream& operator<< (std::ostream&, const Polinom&);

#endif PRINT_POLINOMS_H