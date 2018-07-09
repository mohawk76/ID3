#pragma once
#ifndef Console_H
#define Console_H

#ifdef _WIN32
#include <Windows.h>
#elif __linux__ ||  __APPLE__
#include <cstdlib>
#endif

#include <iostream>
#include <string>

using namespace std;

namespace Console {
#ifdef _WIN32
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const enum COLOR {
		WHITE = (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN),
		BLACK = 0,
		YELLOW = (FOREGROUND_RED | FOREGROUND_GREEN),
		BLUE = FOREGROUND_BLUE,
		GREEN = FOREGROUND_GREEN,
		RED = FOREGROUND_RED
	};
#elif __linux__ || __APPLE__
	const enum COLOR {
		WHITE = 97,
		BLACK = 30,
		YELLOW = 33,
		BLUE = 33,
		GREEN = 32,
		RED = 31
};
#endif

	void displayError(string);
	void displaySuccess(string);
	void newLine();
	void out(const char*, COLOR color = COLOR::WHITE);
	void pause();
	void clear();
}

#endif