#include "Option.h"


void ShowStatics() {
	int rows = GetRows(), columns = GetColumns();
	FOR(i, 20, rows - 1) ClearLine(i);
	gotoxy(1, 23);
	COORD cursor = GetConsoleCursorPosition(HOUT);
	COORD Top = cursor;
	Top.X = Print("             WIN | DRAW | LOSE ", 1) - 2;
	cursor = GetConsoleCursorPosition(HOUT);
	int easyline = cursor.Y;
	//
	Player::ReadInit();
	//
	string line = "Easy:          ";
	REP(j, 3) line = line + to_string(Player::GetStatic(1, j)) + "     ";
	Print(line, 1);
	line = "Medium:        ";
	REP(j, 3) line = line + to_string(Player::GetStatic(2, j)) + "     ";
	Print(line, 1);
	line = "Hard:          ";
	REP(j, 3) line = line + to_string(Player::GetStatic(3, j)) + "     ";
	Print(line, 1);

	Print("", 1);
	cursor = GetConsoleCursorPosition(HOUT);
	Print("RESET                            ", 1);
	int resetline = cursor.Y;
	cursor = GetConsoleCursorPosition(HOUT);
	Print("BACK                             ", 1);
	int backline = cursor.Y;
	Top.Y = resetline;
	gotoxy(Top.X, Top.Y);
	while (true) {
		if (GetSound()) Beep(600, 100);
		while (!_kbhit()) {
		}
		char c = _getch();
		while (c == 0 || c == 224) c = _getch();
		switch (c) {
		case 13: {
			int y = GetConsoleCursorPosition(HOUT).Y;
			if (y == resetline) {
				Player::ResetStatics();
				ShowStatics();
				return;
			}
			if (y == backline) {
				return;
			}
			break;
		}
		case 'w': { // Up
			COORD cur = GetConsoleCursorPosition(HOUT);
			if (cur.Y <= easyline) break;
			gotoxy(cur.X, cur.Y - 1);
			break;
		}
		case 's': {
			COORD cur = GetConsoleCursorPosition(HOUT);
			if (cur.Y >= backline) break;
			gotoxy(cur.X, cur.Y + 1);
			break;
		}
		}
	}
}

void UpdateIcon() {
	int rows = GetRows(), columns = GetColumns();
	FOR(i, 20, rows - 1) ClearLine(i);
	gotoxy(1, 23);

	Print("Player 1 icon: ", 0); cout << Player::GetIcon(0) << endl;
	Print("Player 2 icon: ", 0); cout << Player::GetIcon(1) << endl;
	Print("Input icon(character) of player 1: ", 0);
	COORD pos = GetConsoleCursorPosition(HOUT);

	while (true) {
		SetConsoleCursorPosition(HOUT, pos);
		while (!_kbhit());
		char c = _getch();
		while (c == 0 || c == 224) c = _getch();
		if (c > 32) {
			Player::UpdateIcon(0, c);
			cout << c << endl;
			break;
		}
	}
	Print("Input icon(character) of player 2: ", 0);
	pos = GetConsoleCursorPosition(HOUT);
	while (true) {
		SetConsoleCursorPosition(HOUT, pos);
		while (!_kbhit());
		char c = _getch();
		while (c == 0 || c == 224) c = _getch();
		if (c > 32) {
			Player::UpdateIcon(1, c);
			cout << c << endl;
			break;
		}
	}
	Player::UpdateInit();
	Print("Change icon successfully.", 1);
	char c = _getch();
	while (c == 0 || c == 224) c = _getch();
}

void UpdateSizeGameBoard() {
	int rows = GetRows(), columns = GetColumns();
	FOR(i, 20, rows - 1) ClearLine(i);
	gotoxy(1, 23);
	Print("Height of table: ", 0); cout << Player::GetHeight() << endl;
	Print("Width of table:  ", 0); cout << Player::GetWidth() << endl;
	Print("Input new height(min = 1, max = 20): ", 0);
	int x;
	cin >> x;
	Player::UpdateHeight(x);
	Print("Input new width(min = 1, max = 40): ", 0);
	cin >> x;
	Player::UpdateWidth(x);
	Player::UpdateInit();
	Print("Change size of game board successfully.", 1);
	char c = _getch();
	while (c == 0 || c == 224) c = _getch();
}

void UpdateSound() {
	GetSound() ^= 1;
}

void ResetToDefault() {
	remove("Data\\ini.cfg");
	Player::ReadInit();
}

void ShowOption() {
	int rows = GetRows(), columns = GetColumns();
	Player::ReadInit();
	FOR(i, 20, rows - 1) ClearLine(i);
	gotoxy(1, 23);
	COORD cursor = GetConsoleCursorPosition(HOUT);
	COORD Top = cursor;
	Top.X =
		Print("CHANGE ICON               ", 1) - 2;
	int iconline = cursor.Y;
	cursor = GetConsoleCursorPosition(HOUT);
	Print("CHANGE SIZE OF GAMEBOARD  ", 1);
	int sizeline = cursor.Y;
	string line;
	if (GetSound())
		line = "TURN OFF SOUND            ";
	else
		line = "TURN ON SOUND             ";
	cursor = GetConsoleCursorPosition(HOUT);
	Print(line, 1);
	int soundline = cursor.Y;
	cursor = GetConsoleCursorPosition(HOUT);
	Print("RESET OPTION TO DEFAULT   ", 1);
	int resetline = cursor.Y;
	cursor = GetConsoleCursorPosition(HOUT);
	Print("BACK                      ", 1);
	int backline = cursor.Y;

	// Create help
	gotoxy(1, rows - 2);
	Print("Press W to move UP, S to move DOWN and press ENTER to choose.", 0);
	gotoxy(Top.X, Top.Y);
	while (true) {
		if (GetSound()) Beep(500, 100);
		while (!_kbhit()) {
		}
		char c = _getch();
		while (c == 0 || c == 224) c = _getch();
		switch (c) {
		case 13: {
			int y = GetConsoleCursorPosition(HOUT).Y;
			if (y == iconline) {
				UpdateIcon();
			}
			if (y == sizeline) {
				UpdateSizeGameBoard();
			}
			if (y == soundline) {
				UpdateSound();
			}
			if (y == resetline) {
				ResetToDefault();
			}
			if (y == backline) {
				// EXIT GAME
				LaunchScreen(0);
				MenuGame();
				break;
			}
			//LaunchScreen(0);
			ShowOption();
			break;
		}
		case 'w': { // Up
			COORD cur = GetConsoleCursorPosition(HOUT);
			if (cur.Y <= iconline) break;
			gotoxy(cur.X, cur.Y - 1);
			break;
		}
		case 's': {
			COORD cur = GetConsoleCursorPosition(HOUT);
			if (cur.Y >= backline) break;
			gotoxy(cur.X, cur.Y + 1);
			break;
		}
		}
	}
}
