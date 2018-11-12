#pragma once

#include "Defines.h"
#include "Console.h"

void InitWindow() {
	FullScreen();
	srand(time(NULL));
}

int GetRows() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(HOUT, &csbi);
	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

int GetColumns() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(HOUT, &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int sound = 1;

int& GetSound() {
	return sound;
}

void TextColor(int color) {
	SetConsoleTextAttribute(HOUT, color);
}

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(HOUT, pos);
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &csbi))
	{
		return csbi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

int GoCenterColumn(int length) {
	gotoxy((GetColumns() - length) / 2, GetConsoleCursorPosition(HOUT).Y);
	return (GetColumns() - length) / 2;
}

void FullScreen() {
	SetConsoleDisplayMode(HOUT, CONSOLE_FULLSCREEN_MODE, 0);
}

void ClearScreen() {
	system("cls");
	TextColor(7);
}

void ClearLine(int line) {
	COORD now = GetConsoleCursorPosition(HOUT);
	gotoxy(0, line);
	REP(i, GetColumns()) std::cout << ' ';
	gotoxy(now.X, now.Y);
}

int Print(string out, bool endline) {
	int pos = GoCenterColumn(out.size());
	cout << out;
	if (endline) cout << endl;
	return pos;
}

void AssignCenter(string &s, string t) {
	if (GetSound()) {
		Beep(1000, 100);
	}
	int pos = (s.length() - t.length()) / 2;
	REP(i, (int)t.length()) s[i + pos] = t[i];
}

void SoundWin() {
	if (GetSound()) {
		REP(i, 6) {
			Beep(i * 100 + 1000, 100 * i);
		}
		Beep(1600, 1000);
	}
}

void SoundLose() {
	if (GetSound()) {
		REP(i, 6) {
			Beep(2000 - i * 100, 100 * i);
		}
		Beep(1400, 1000);
	}
}
