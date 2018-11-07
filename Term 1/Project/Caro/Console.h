#pragma once
#include "Defines.h"

#define HOUT GetStdHandle(STD_OUTPUT_HANDLE)
#define HIN GetStdHandle(STD_INPUT_HANDLE)
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a) for (int i = 0; i < (a); ++i)

void resizeConsole(int width, int height);
void TextColor(int color);
void gotoxy(int x, int y);
void ClearScreen(int isRandom);
void FullScreen();
int GoCenterColumn(int length);
void InitWindow();

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
CONSOLE_SCREEN_BUFFER_INFO csbi;

int rows, columns;

void InitWindow() {
	FullScreen();
	GetConsoleScreenBufferInfo(HOUT, &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	//Random init
	srand(time(NULL));
}

void resizeConsole(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, true);
}

void TextColor(int color) {
	SetConsoleTextAttribute(HOUT, color);
}

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(HOUT, pos);
}


void FullScreen() {
	SetConsoleDisplayMode(HOUT, CONSOLE_FULLSCREEN_MODE, 0);
}

int GoCenterColumn(int length) {
	gotoxy((columns - length) / 2, GetConsoleCursorPosition(HOUT).Y);
	return (columns - length) / 2;
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
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

void ClearLine(int line) {
	COORD now = GetConsoleCursorPosition(HOUT);
	gotoxy(0, line);
	REP(i, columns) std::cout << ' ';
	gotoxy(now.X, now.Y);
}

int Print(string out, bool endline) {
	int pos = GoCenterColumn(out.size());
	cout << out;
	if (endline) cout << endl;
	return pos;
}


int background, sound = 1;
void AssignCenter(string &s, string t) {
	if (sound) {
		Beep(1000, 100);
	}
	int pos = (s.length() - t.length()) / 2;
	REP(i, (int)t.length()) s[i + pos] = t[i];
}

void ClearScreen(int isRandom) {
	system("cls");
	TextColor(7);
}

void SoundWin() {
	if (sound) {
		REP(i, 6) {
			Beep(i * 100 + 1000, 100 * i);
		}
		Beep(1600, 1000);
	}
}

void SoundLose() {
	if (sound) {
		REP(i, 6) {
			Beep(2000 - i * 100, 100 * i);
		}
		Beep(1400, 1000);
	}
}