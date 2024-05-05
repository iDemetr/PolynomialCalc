#pragma once

#include "Header.h"

#ifndef WORKWITHFILE_H
#define WORKWITHFILE_H

const std::string FHistory = "History.json";

/// <summary>
/// ��������� �������� ������ � ���������� � ��������� ���������� � ����
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
bool SaveHistory(std::string, ptrPolinom);

/// <summary>
/// ������� � ��������� ������� �������� � ������������ ������������ 
/// </summary>
/// <returns></returns>
vector <std::pair<std::string, std::string>> ReadHistory();

#endif WORKWITHFILE_H
