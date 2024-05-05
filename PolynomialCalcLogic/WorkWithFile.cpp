#pragma once

#include "pch.h"
#include "Header.h"
#include "PrintPolinoms.h"
#include "WorkWithFile.h"


bool SaveHistory(std::string task, ptrPolinom result) {
	std::fstream fHistory (FHistory);

	std::string buff;

	bool flag = false;
	int loc(0);

	if (fHistory.is_open())
	{
		while (fHistory >> buff) {
			if (buff == "{")
			{
				loc = fHistory.get();
				fHistory >> buff;
				//
				std::getline(fHistory, buff);
				buff = buff.substr(2, buff.size() - 4);
				if (buff == task) {
					flag = true;	
					fHistory >> buff;
					loc = fHistory.get() + 1;
					fHistory << result;
					//
					// ������������ ��������� � �����
					//
					break;
				}
			}
		}
		fHistory.close();
	}

	if (!flag) {
		std::ofstream fHistory(FHistory, std::ios_base::app);
		fHistory << "{\n\t\"Task\": \"" << task << "\",";
		fHistory << "\n\t\"Result\": \"" << *result << "\"\n}\n";
	}

	return true;
}


vector <std::pair<std::string, std::string>> ReadHistory() {
	std::ifstream fHistory(FHistory);

	std::string buff;
	std::string task, result;

	vector <std::pair<std::string, std::string>> history;

	if (fHistory.is_open())
	{
		while (fHistory >> buff) {
			if (buff == "{") {
				// ������ �������
				fHistory >> buff;
				std::getline(fHistory, buff);
				task = buff.substr(2, buff.size() - 4);
				// ������ ����������
				fHistory >> buff;
				std::getline(fHistory, buff);
				result = buff.substr(2, buff.size() - 3);

				history.push_back({ task,result });
			}
		}
		fHistory.close();
	}

	int i(1);
	for(auto var : history)
	{ 
		cout << "\n-------------------------------------------------------------";
		cout << "\n �����: " << i++;
		cout << "\n ������: " << var.first;
		cout << "\n ���������: " << var.second;
		cout << "\n-------------------------------------------------------------";
	}
	cout << endl;

	return history;
}