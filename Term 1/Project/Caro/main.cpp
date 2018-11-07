#include "Console.h"
#include "Player.h"
#include "Defines.h"

void LaunchScreen(int first);
void MenuGame();
void NewGame(int Difficulty);


long long p[N * N], r[N * N];

void ShowTitle(int first) {
	int magic = 0;
	if (first) Sleep(1000);
	else magic = 7;
	FOR(i, magic, 7) {
		ClearScreen(0);
		TextColor(i);
		gotoxy(1, 10);
		if (sound) {
			Beep(2000, 100);
			Beep(3000, 100);
		}
		Print(" **********          ****             *********         ************", 1);
		Print(" ********           **  **            ***   ****        ****    ****", 1);
		Print(" ****              **    **           ***  ****         ***      ***", 1);
		Print(" ***              ***    ***          *******           **        **", 1);
		Print(" ****            ************         ***  ****         ***      ***", 1);
		Print(" ********       ****      ****        ***   ****        ****    ****", 1);
		Print(" **********    ****        ****       ***    ****       ************", 1);
		Sleep(200);
	}
	Sleep(500);
	Print("                                                           Designed by NERO", 1);
}

string screen[N];

void ShowAbout() {
	REP(i, rows) screen[i].clear();
	REP(i, rows) REP(j, columns) {
		screen[i].push_back(' ');
		r[i * columns + j] = Rand(1, rows * columns);
		p[i * columns + j] = i * columns + j;
	}
	sort(p, p + columns * rows, [](int a, int b) {
		return r[a] < r[b];
	});
	REP(i, rows * columns) {
		gotoxy(p[i] % columns, p[i] / columns);
		TextColor(2);
		cout << '.';
	}
	int now = 3;
	AssignCenter(screen[++now], "      AAA          BBBBBBBB      OOOOOOOOO    UUU     UUU   TTTTTTTTTTT           UUU     UUU    SSSSSSSS");
	AssignCenter(screen[++now], "     A   A         BB     BB    OOOOO OOOOO   UUU     UUU   TTTTTTTTTTT           UUU     UUU   SSSSSSSS ");
	AssignCenter(screen[++now], "    AA   AA        BB    BB     OOO     OOO   UUU     UUU       TTT               UUU     UUU     SSS    ");
	AssignCenter(screen[++now], "   AAA   AAA       BBBBBBBBB    OO       OO   UUU     UUU       TTT               UUU     UUU       SSS  ");
	AssignCenter(screen[++now], "  AAAAAAAAAAA      BB      BB   OOO     OOO   UUU     UUU       TTT               UUU     UUU        SSS ");
	AssignCenter(screen[++now], " AAAA     AAAA     BB      BB   OOOOO OOOOO   UUUUUUUUUUU       TTT               UUUUUUUUUUU    SSSSSSSS");
	AssignCenter(screen[++now], "AAAAA     AAAAA    BBBBBBBBB     OOOOOOOOO     UUUUUUUUU        TTT                UUUUUUUUU    SSSSSSSS ");
	//
	now = 14;
	AssignCenter(screen[++now], "Full name: Nguyen E Ro         ");
	AssignCenter(screen[++now], "Class: 18CTT1 - APCS           ");
	AssignCenter(screen[++now], "HCMUS - Information Science    ");
	AssignCenter(screen[++now], "Email: heathcliff1342@gmail.com");
	REP(i, rows * columns) {
		gotoxy(p[i] % columns, p[i] / columns);
		TextColor(7);
		cout << screen[p[i] / columns][p[i] % columns];
	}
	gotoxy(0, now + 5);
	Print("Press any key to back...", 0);
	char c = _getch();
	while (c == 0 || c == 224) c = _getch();
}

void MenuNewGame() {
	// Create MENU
	FOR(i, 20, rows - 1) ClearLine(i);
	gotoxy(1, 23);
	COORD cursor = GetConsoleCursorPosition(HOUT);
	cursor = GetConsoleCursorPosition(HOUT);
	cursor.X = Print("Player vs Player           ", 1) - 2;
	int pvpline = cursor.Y;
	Print("Player vs Computer - Easy  ", 1);
	int easyline = cursor.Y + 1;
	Print("Player vs Computer - Medium", 1);
	int mediumline = cursor.Y + 2;
	Print("Player vs Computer - Hard  ", 1);
	int hardline = cursor.Y + 3;
	Print("BACK                       ", 1);
	int backline = cursor.Y + 4;
	// Create help
	gotoxy(1, rows - 2);
	Print("Press W to move UP, S to move DOWN and press ENTER to choose.", 0);
	gotoxy(cursor.X, cursor.Y);
	while (true) {
		if (sound) Beep(523, 100);
		while (!_kbhit()) {
		}
		char c = _getch();
		while (c == 0 || c == 224) c = _getch();
		switch (c) {
		case 13: {
			int y = GetConsoleCursorPosition(HOUT).Y;
			if (y == pvpline) {
				//NEW GAME
				NewGame(0);
				LaunchScreen(0);
				MenuGame();
				break;
			}
			if (y == easyline) {
				//LOAD GAME
				NewGame(1);
				LaunchScreen(0);
				MenuGame();
				break;
			}
			if (y == mediumline) {
				//TUTORIAL
				NewGame(2);
				LaunchScreen(0);
				MenuGame();
				break;
			}
			if (y == hardline) {
				//ABOUT
				NewGame(3);
				LaunchScreen(0);
				MenuGame();
				return;
			}
			if (y == backline) {
				// EXIT GAME
				LaunchScreen(0);
				MenuGame();
			}
			break;
		}
		case 'w': { // Up
			COORD cur = GetConsoleCursorPosition(HOUT);
			if (cur.Y <= pvpline) break;
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

void ShowStatics() {
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
	REP(j, 3) line = line + to_string(Player::Level[1][j]) + "     ";
	Print(line, 1);
	line = "Medium:        ";
	REP(j, 3) line = line + to_string(Player::Level[2][j]) + "     ";
	Print(line, 1);
	line = "Hard:          ";
	REP(j, 3) line = line + to_string(Player::Level[3][j]) + "     ";
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
		if (sound) Beep(600, 100);
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
	FOR(i, 20, rows - 1) ClearLine(i);
	gotoxy(1, 23);
	Print("Player 1 icon: ", 0); cout << Player::icon[0] << endl;
	Print("Player 2 icon: ", 0); cout << Player::icon[1] << endl;
	Print("Input icon(character) of player 1: ", 0);
	COORD pos = GetConsoleCursorPosition(HOUT);
	
	while (true) {
		SetConsoleCursorPosition(HOUT, pos);
		while (!_kbhit());
		char c = _getch();
		while (c == 0 || c == 224) c = _getch();
		if (c > 32) {
			Player::icon[0] = c;
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
			Player::icon[1] = c;
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
	FOR(i, 20, rows - 1) ClearLine(i);
	gotoxy(1, 23);
	Print("Height of table: ", 0); cout << Player::HeightOfTable << endl;
	Print("Width of table:  ", 0); cout << Player::WidthOfTable << endl;
	Print("Input new height(min = 1, max = 20): ", 0);
	int x;
	cin >> x;
	Player::HeightOfTable = x;
	Print("Input new width(min = 1, max = 40): ", 0);
	cin >> x;
	Player::WidthOfTable = x;
	Player::UpdateInit();
	Print("Change size of game board successfully.", 1);
	char c = _getch();
	while (c == 0 || c == 224) c = _getch();
}

void UpdateBackground() {
	background ^= 1;
}


void UpdateSound() {
	sound ^= 1;
}

void ResetToDefault() {
	remove("Data\\ini.cfg");
	Player::ReadInit();
}

void ShowOption() {
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
	if (sound)
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
		if (sound) Beep(500, 100);
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

void MenuGame() {
	// Create MENU
	FOR(i, 20, rows - 1) ClearLine(i);
	COORD cursor = GetConsoleCursorPosition(HOUT);
	gotoxy(1, 23);
	cursor = GetConsoleCursorPosition(HOUT);
	COORD Top = cursor;
	Top.X = Print("NEW GAME ", 1) - 2;
	int newGameline = cursor.Y;
	cursor = GetConsoleCursorPosition(HOUT);
	Print("LOAD GAME", 1);
	int loadGameline = cursor.Y;
	cursor = GetConsoleCursorPosition(HOUT);
	Print("STATICS  ", 1);
	int staticsline = cursor.Y;
	cursor = GetConsoleCursorPosition(HOUT);
	Print("OPTIONS  ", 1);
	int optionline = cursor.Y;
	cursor = GetConsoleCursorPosition(HOUT);
	Print("TUTORIAL ", 1);
	int tutorialline = cursor.Y;
	cursor = GetConsoleCursorPosition(HOUT);
	Print("ABOUT    ", 1);
	int aboutline = cursor.Y;
	cursor = GetConsoleCursorPosition(HOUT);
	Print("EXIT     ", 1);
	int exitline = cursor.Y;
	// Create help
	gotoxy(1, rows - 2);
	Print("Press W to move UP, S to move DOWN and press ENTER to choose.", 0);
	gotoxy(Top.X, Top.Y);
	while (true) {
		if (sound)	Beep(523, 100);
		while (!_kbhit()) {
		}
		char c = _getch();
		while (c == 0 || c == 224) c = _getch();
		switch (c) {
		case 13: {
			int y = GetConsoleCursorPosition(HOUT).Y;
			if (y == newGameline) {
				//NEW GAME
				MenuNewGame();
			}
			if (y == loadGameline) {
				//LOAD GAME
				Player::Draw(0);
				Player::LoadGame();
				Player::Move();
			}
			if (y == staticsline) {
				//LOAD GAME
				ShowStatics();
			}
			if (y == optionline) {
				//LOAD GAME
				ShowOption();
			}
			if (y == tutorialline) {
				//TUTORIAL
			}
			if (y == aboutline) {
				//ABOUT
				ShowAbout();
			}
			if (y == exitline) {
				// EXIT GAME
				ClearScreen(1);
				gotoxy(1, rows / 2);
				Print("SEE YOU LATER...", 0);
				Sleep(1000);
				exit(0);
			}
			LaunchScreen(0);
			MenuGame();
			break;
		}
		case 'w': { // Up
			COORD cur = GetConsoleCursorPosition(HOUT);
			if (cur.Y <= newGameline) break;
			gotoxy(cur.X, cur.Y - 1);
			break;
		}
		case 's': {
			COORD cur = GetConsoleCursorPosition(HOUT);
			if (cur.Y >= exitline) break;
			gotoxy(cur.X, cur.Y + 1);
			break;
		}
		}
	}
}

void LaunchScreen(int first) {
	ShowTitle(first);
	if (first) {
		Sleep(200);
		gotoxy(1, 20);
		Print("LOADING", 0);
		COORD cursor = GetConsoleCursorPosition(HOUT);
		REP(i, 6) {
			cout << '.';
			if (sound) Beep(300, 100);
			Sleep(500);
			if (i == 2) {
				gotoxy(cursor.X, cursor.Y);
				cout << "   ";
				gotoxy(cursor.X, cursor.Y);
			}
		}
		cursor = GetConsoleCursorPosition(HOUT);
		Print("Okay! Let's start!!", 1);
		Print("Press ENTER to continue...", 0);
		while (true) {
			char c = _getch();
			while (c == 0 || c == 224) c = _getch();
			if (c == 13) break;
		}
		gotoxy(cursor.X, cursor.Y);
		ClearLine(cursor.Y);
		ClearLine(cursor.Y + 1);
	}
}

void NewGame(int Difficulty) {
	Player::Draw(Difficulty);
	Player::Move();
}

int main() {
	InitWindow();
	LaunchScreen(1);
	MenuGame();
	system("pause");
}