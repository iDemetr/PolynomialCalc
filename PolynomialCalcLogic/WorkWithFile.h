#pragma once

#include "Header.h"

#ifndef WORKWITHFILE_H
#define WORKWITHFILE_H

bool SaveHistory(std::string, ptrPolinom);
vector <std::pair<std::string, std::string>> ReadHistory();

#endif WORKWITHFILE_H
