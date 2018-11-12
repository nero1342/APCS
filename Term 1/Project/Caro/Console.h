#pragma once

#define HOUT GetStdHandle(STD_OUTPUT_HANDLE)
#define HIN GetStdHandle(STD_INPUT_HANDLE)

void InitWindow();

int GetRows();

int GetColumns();

int& GetSound();

void TextColor(int color);

void gotoxy(int x, int y);

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);

int GoCenterColumn(int length);

void FullScreen();

void ClearScreen();

void ClearLine(int line);

int Print(string out, bool endline);

void AssignCenter(string &s, string t);

void SoundWin();

void SoundLose();

