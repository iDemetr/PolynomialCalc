#pragma once

#ifndef HEADER_H
#define HEADER_H

enum command { poww = '^', multiplication = '*', division = '/', addition = '+', subtraction = '-' };

// ��������� ��� ������� � ������� � �������, ���:
// Layer - ����� ���� ������, ��� ������ - ���� ��������� ��������
// Pol1 - ����� �������
// Pol2 - ������ �������
enum ETask { Layer, Pol1, Operator, Pol2 };

/// <summary>
/// ������ ������
/// </summary>
#define Task std::tuple<BYTE, string, char, string>

/// <summary>
/// ���� �����
/// </summary>
#define Tasks std::stack <Task>

/// <summary>
/// ��� ������
/// </summary>
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

/// <summary>
/// ��� ��������
/// </summary>
typedef std::set<Monom> Polinom;
typedef std::set<Monom>* ptrPolinom;

/// <summary>
/// 
/// </summary>
struct nodeBuffer{
	/// <summary>
	/// ����� ����.
	/// </summary>
	int layer;

	/// <summary>
	/// ����� �������� ������ ���� ���� ���������
	/// </summary>
	char operation;

	/// <summary>
	/// ������ �� ������� ��������� �� ���� ����.
	/// </summary>
	ptrPolinom polinom;
};

/// <summary>
/// ����� ��������
/// </summary>
typedef std::stack<nodeBuffer> Buffer;

// �������� ��� �������� �����
const int noOperator = -1;

#endif HEADER_H