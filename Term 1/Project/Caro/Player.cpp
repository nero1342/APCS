#include "Defines.h"
#include "Logic.h"
#include "PvC.h"
#include "Console.h"
#include "Player.h"

namespace Player {

	string screen[N], origin[N];
	int table[N][N], HeightOfTable, WidthOfTable, LeftOfTable, UpOfTable;
	char icon[2] = { 'X', 'O' };
	int Level[4][3];
	int color[2];
	int turn, ComputerTurn, DifficultyComputer, LenToWin;
	int columnsformessage = 60;
	int totalStep;

	vector<COORD> history;

	vector< pair<string, int> > ListMessage;
	vector<string> ListSavedGame;
	int cntMessage = 0;

	int GetHeight() {
		return HeightOfTable;
	}

	int GetWidth() {
		return WidthOfTable;
	}

	int GetLengthToWin() {
		return LenToWin;
	}

	void UpdateHeight(int height) {
		HeightOfTable = height;
	}

	void UpdateWidth(int width) {
		WidthOfTable = width;
	}

	void UpdateLengthToWin(int len) {
		LenToWin = len;
	}

	char GetIcon(int id) {
		return icon[id];
	}

	void UpdateIcon(int id, char c) {
		icon[id] = c;
	}

	int GetStatistics(int status, int level) {
		return Level[status][level];
	}

	int idH(int x) {
		if (x < UpOfTable || x > UpOfTable + HeightOfTable * 2 - 1) return N - 1;
		return (x - UpOfTable) / 2;
	}

	int idW(int y) {
		if (y < LeftOfTable || y > LeftOfTable + WidthOfTable * 2 - 1) return N - 1;
		return (y - LeftOfTable) / 2;
	}

	void UpdateInit() {
		ofstream OutStats("Data\\ini.cfg");
		OutStats << HeightOfTable << ' ' << WidthOfTable << ' ' << icon[0] << ' ' << icon[1] << ' ' << LenToWin << endl;
		FOR(i, 1, 3) {
			REP(j, 3) OutStats << Level[i][j] << ' ';
			OutStats << endl;
		}
		OutStats.close();
	}

	void ReadInit() {
		ifstream InStats("Data\\ini.cfg");
		if (!InStats.good()) {
			system("md Data");
			HeightOfTable = 20;
			WidthOfTable = 40;
			icon[0] = 'X';
			icon[1] = 'O';
			LenToWin = 5;
			memset(Level, 0, sizeof Level);
			UpdateInit();
			return;
		}
		InStats >> HeightOfTable >> WidthOfTable >> icon[0] >> icon[1] >> LenToWin;
		FOR(i, 1, 3) REP(j, 3) InStats >> Level[i][j];
		InStats.close();
	}

	void ResetStatistics() {
		FOR(i, 1, 3) REP(j, 3) Level[i][j] = 0;
		UpdateInit();
	}

	void UpdateStatistics(int value, int Difficulty) {
		// 0 : Lose, 1 : Draw, 2 : Win
		Level[Difficulty][value]++;
		UpdateInit();
	}

	void Reload() {
		int rows = GetRows(), columns = GetColumns();
		color[0] = 13;
		color[1] = 14;
		cntMessage = 0;
		ListMessage.clear();
		ClearScreen();
		turn = 0;
		memset(table, -1, sizeof table);
		REP(i, rows) {
			REP(j, columns) {
				REP(k, 2) {
					if (screen[i][j] == icon[k]) {
						TextColor(color[k]);
						int x = idH(i), y = idW(j);
						if (x != N - 1 && y != N - 1) {
							table[x][y] = k;
							turn ^= 1;
							totalStep--;
						}
					}
				}
				cout << screen[i][j];
				TextColor(7);
			}
			cout << endl;
		}
	}

	void Draw(int Difficulty) {
		int rows = GetRows(), columns = GetColumns();
		turn = 0;
		ReadInit();
		InitListSavedGame();
		ListMessage.clear();
		history.clear();
		if (Difficulty) {
			DifficultyComputer = Difficulty;
			ComputerTurn = 1;
		}
		else {
			ComputerTurn = -1;
			DifficultyComputer = 0;
		}
		ClearScreen();
		//
		int height = HeightOfTable;
		int width = WidthOfTable;
		totalStep = height * width;
		height = height * 2 + 1; width = width * 2 + 1;
		int posY = (rows - height) / 2;
		if (posY % 2 == 0) posY--;
		int posX = (columns - width - columnsformessage) / 2;
		if (posX % 2) posX--;
		LeftOfTable = posX + 1;
		UpOfTable = posY + 1;
		//
		REP(i, rows) {
			screen[i].clear();
			if (i < posY - 1 || i > posY + height) {
				REP(j, columns) screen[i].push_back(' ');
				continue;
			}
			if (i == posY - 1) {
				REP(j, columns) {
					if (j < posX || j >= posX + width) {
						if (j == posX - 1) screen[i].push_back(201);
						else if (j == posX + width) screen[i].push_back(187);
						else screen[i].push_back(' ');
						continue;
					}
					if (j % 2 == 0) screen[i].push_back(209);
					else screen[i].push_back(205);
				}
				continue;
			}
			if (i == posY + height) {
				REP(j, columns) {
					if (j < posX || j >= posX + width) {
						if (j == posX - 1) screen[i].push_back(200);
						else if (j == posX + width) screen[i].push_back(188);
						else screen[i].push_back(' ');
						continue;
					}
					if (j % 2 == 0) screen[i].push_back(207);
					else screen[i].push_back(205);
				}
				continue;
			}
			REP(j, columns) {
				if (j < posX || j >= posX + width) {
					if (j == posX - 1) screen[i].push_back(199);
					else if (j == posX + width) screen[i].push_back(182);
					else screen[i].push_back(' ');
					continue;
					screen[i].push_back(' ');
					continue;
				}
				if (i % 2 == 1) {
					if (j % 2 == 1) screen[i].push_back(196);
					else screen[i].push_back(197);
				}
				else {
					if (j % 2 == 1) {
						if (Rand(0, 1)) screen[i].push_back(' ');
						else screen[i].push_back(' ');
					}
					else screen[i].push_back(179);
				}
			}

		}
		FOR(i, 3, rows - 3) {
			screen[i][columns - 60] = 179;
		}
		string mode;
		if (DifficultyComputer == 0) mode = "Player vs Player";
		if (DifficultyComputer == 1) mode = "Player vs Computer - Easy";
		if (DifficultyComputer == 2) mode = "Player vs Computer - Medium";
		if (DifficultyComputer == 3) mode = "Player vs Computer - Hard";
		if (DifficultyComputer == 4) mode = "Computer vs Computer - Hard vs Hard";
		int i = (columns - columnsformessage + (columnsformessage - mode.size()) / 2);
		for (char x : mode) screen[6][i++] = x;
		string Header = "Notification:";
		i = i = (columns - columnsformessage + (columnsformessage - Header.size()) / 2);
		for (char x : Header) screen[8][i++] = x;
		string Tutorial = "Press W, S, A, D to move, SPACE to choose.";
		i = (columns - columnsformessage - Tutorial.size()) / 2;
		for (char x : Tutorial) screen[rows - 2][i++] = x;
		Tutorial = "1: Help | 2: Save | 3: Load | 4: Remove | U: Undo | ESC: Exit";
		i = (columns - columnsformessage - Tutorial.size()) / 2;
		for (char x : Tutorial) screen[rows - 1][i++] = x;
		Reload();
		//gotoxy(2, 10);  for (int i = 0; i < 80; i += 2) cout << char(180 + i / 2) << ' ';
		//system("pause");

	}

	void Message(string message, int isEndline, int isNumbered) {
		int rows = GetRows(), columns = GetColumns();
		if (isNumbered) ListMessage.push_back(make_pair(message, ++cntMessage));
		else ListMessage.push_back(make_pair(message, 0));
		if (ListMessage.size() == rows - 15) {
			ListMessage.erase(ListMessage.begin());
		}
		COORD pos = GetConsoleCursorPosition(HOUT);
		FOR(r, 10, rows - 1) {
			gotoxy(columns - columnsformessage + 1, r);
			REP(i, columnsformessage) {
				cout << ' ';
			}
		}
		int line = 9;
		REP(i, ListMessage.size()) {
			TextColor(ListMessage[i].second % 10 + 1);
			gotoxy(columns - columnsformessage + 1, ++line);
			if (ListMessage[i].second) cout << ListMessage[i].second << ". " << ListMessage[i].first;
			else {
				cout << "     " << ListMessage[i].first;
			}
			TextColor(7);
		}
		if (isEndline) SetConsoleCursorPosition(HOUT, pos);
	}

	void Unchoose() {
		if (history.empty()) return;
		COORD now = history.back();
		totalStep++;
		history.pop_back();
		string mess = " undo ";
		turn ^= 1;
		mess = icon[turn] + mess + '(' + to_string(idH(now.Y)) + ',' + to_string(idW(now.X)) + ')';
		Message(mess, 1, 1);
		gotoxy(now.X, now.Y);
		cout << ' ';
		gotoxy(now.X, now.Y);
		screen[now.Y][now.X] = ' ';
		table[idH(now.Y)][idW(now.X)] = -1;
	}

	bool Choose(COORD cur) {
		history.push_back(cur);
		gotoxy(cur.X, cur.Y);
		screen[cur.Y][cur.X] = icon[turn];
		table[idH(cur.Y)][idW(cur.X)] = turn;
		if (cur.Y == UpOfTable && cur.X == LeftOfTable) {
		//	REP(i, 4) Unchoose();
		}
		
		string step = " choose cell ";
		step = icon[turn] + step + '(' + to_string(1 + idH(cur.Y)) + ',' + to_string(1 + idW(cur.X)) + ')';
		Message(step, 1, 1);
		TextColor(color[turn]);
		cout << icon[turn];
		gotoxy(cur.X, cur.Y);
		TextColor(7);
		if (ValidWin(table, HeightOfTable, WidthOfTable, LenToWin)) {
		//	turn ^= 1;  Unchoose(); return false;
			string message = "Player ";
			message = message + icon[turn] + '(' + to_string(turn) + ')' + " win!! ";
			if (turn == 0 || DifficultyComputer == 0) {
				SoundWin();
			}
			else {
				SoundLose();

			}
		//	REP(i, 4) Unchoose();
			UpdateStatistics(turn * 2, DifficultyComputer);
			turn ^= 1;
			Message(message, 1, 1);
			//REP(i, 4) Unchoose();
			Sleep(3000);
			return true;
		}
		totalStep--;
		if (totalStep == 0) {
			Message("Drawwwwwwwwwwww :v :v :v :v :v :v :) :) :)", 1, 1);
			SoundDraw();
			UpdateStatistics(1, DifficultyComputer);
			Sleep(3000);
			return true;
		}
		turn = 1 - turn;
		Sleep(200);
		return false;
	}

	COORD FindPosition(pp x) {
		COORD cur = { LeftOfTable + x.second * 2, UpOfTable + x.first * 2 };
		return cur;
	}

	void Move() {
		gotoxy(LeftOfTable, UpOfTable);
		int height = HeightOfTable * 2 + 1;
		int width = WidthOfTable * 2 + 1;
		int befturn = 1 - turn;
		while (true) {
			if (GetSound()) Beep(500, 100);
			if (turn != befturn) {
				string stTurn = "Turn ";
				stTurn = stTurn + icon[turn] + '(' + to_string(turn) + ')';
				Message(stTurn, 1, 1);
				befturn = turn;
			}
			if (turn == ComputerTurn || DifficultyComputer == 4) {
				// DifficultyComputer == 4 -> CvC
				Computer::GetData(table, HeightOfTable, WidthOfTable, turn, LenToWin);
				switch (DifficultyComputer) {
				case 1: {
					// Easy
					if (Choose(FindPosition(Computer::Easy()))) return;
					break;
				}
				case 2: {
					// Medium
					if (Choose(FindPosition(Computer::Medium()))) return;
					break;
				}
				case 3:
				case 4: {
					// Hard
					if (Choose(FindPosition(Computer::Hard())))	return;
					break;
				}
				}
				continue;
			}
			while (!_kbhit()) {
			}
			char c = _getch();
			while (c == 0 || c == 224) c = _getch();
			COORD cur = GetConsoleCursorPosition(HOUT);
			if ('A' <= c && c <= 'Z') c += 32;
			switch (c) {
			case 27: {
				return;
			}
			case ' ': {
				if (screen[cur.Y][cur.X] != ' ') {
					Message("This cell has already chosen.", 1, 1);
					break;
				}
				if (Choose(cur)) return;
				break;
			}
			case 'w': { // Up
				if (cur.Y <= UpOfTable) break;
				gotoxy(cur.X, cur.Y - 2);
				break;
			}
			case 's': { // Down
				if (cur.Y >= UpOfTable + height - 3) break;
				gotoxy(cur.X, cur.Y + 2);
				break;
			}
			case 'a': { // Left
				if (cur.X <= LeftOfTable + 1) break;
				gotoxy(cur.X - 2, cur.Y);
				break;
			}
			case 'd': { // Right
				if (cur.X >= LeftOfTable + width - 3) break;
				gotoxy(cur.X + 2, cur.Y);
				break;
			}
			case 'u': { // Undo
				Unchoose();
				if (ComputerTurn != -1) Unchoose();
			}
			case '1': {
				//Help
				break;
			}
			case '2': {
				//Save game
				SaveGame();
				break;
			}
			case '3': {
				// Load game
				LoadGame();
				break;
			}
			case '4': {
				// Remove game
				RemoveGame();
				break;
			}
			}
		}
	}


	void InitListSavedGame() {
		ListSavedGame.clear();
		ifstream List("Data\\ListSavedGame.dat");
		string name;
		while (List >> name) ListSavedGame.push_back(name);
	}

	void UpdateListSavedGame() {
		sort(ListSavedGame.begin(), ListSavedGame.end());
		ofstream List("Data\\ListSavedGame.dat");
		for (string name : ListSavedGame) List << name << endl;
	}

	void ShowSavedGame() {
		int cnt = 0;
		Message("List of saved game: ", 1, 1);
		for (string name : ListSavedGame) {
			Message(to_string(++cnt) + ". " + name, 1, 0);
		}
		//	gotoxy(columns - columnsformessage + 1, )
	}

	void RemoveGame() {
		if (ListSavedGame.empty()) {
			Message("You don't have any saved games.", 1, 1);
			return;
		}
		ShowSavedGame();
		COORD pos = GetConsoleCursorPosition(HOUT);

		int id;
		while (true) {
			Message("Input the index of game you want to remove: ", 0, 1);
			cin >> id;
			if (id <= 0 || id > ListSavedGame.size()) {
				Message("Invalid index!!", 1, 0);
			}
			else break;
		}
		string filename = "Data\\" + ListSavedGame[id - 1] + ".car";
		remove(filename.c_str());
		ListSavedGame.erase(ListSavedGame.begin() + id - 1);
		UpdateListSavedGame();
		Message("Remove game successfully", 1, 1);
		SetConsoleCursorPosition(HOUT, pos);
	}

	void SaveGame() {
		InitListSavedGame();
		if (ListSavedGame.size() == 10) {
			Message("You can just save at most 10 games.", 1, 1);
			Message("Please delete some games to save this game", 1, 1);
			char c = _getch();
			c = _getch();
			return;
		}
		COORD pos = GetConsoleCursorPosition(HOUT);
		ShowSavedGame();
		string message = "Input name to save: ";
		Message(message, 0, 1);
		string name;
		cin >> name;
		ListMessage.back().first = ListMessage.back().first + name;
		string filename = "Data\\" + name + ".car";
		fstream out(filename);
		if (out.good()) {
			// Exist;
			Message("This name already exists.", 0, 0);
			char ch;
			while (true) {
				Message("Do you want to replace ? (Y / N): ", 0, 0);
				cin >> ch;
				if ('a' <= ch && ch <= 'z') ch -= 32;
				if (ch == 'N') {
					SetConsoleCursorPosition(HOUT, pos);
					return;
				}
				if (ch == 'Y') break;

			}
		}
		else {
			ListSavedGame.push_back(name);
			UpdateListSavedGame();
		}
		
		ofstream output(filename);
		output << HeightOfTable << ' ' << WidthOfTable << ' ' << DifficultyComputer << ' ' << icon[0] << ' ' << icon[1] << endl;
		REP(i, HeightOfTable) {
			REP(j, WidthOfTable) output << table[i][j] << ' ';
			output << endl;
		}
		output.close();
		Message("Save game successfully!!", 1, 1);
		SetConsoleCursorPosition(HOUT, pos);
	}

	void LoadGame() {
		if (ListSavedGame.empty()) {
			Message("You don't have any saved games.", 1, 1);
			return;
		}
		COORD pos = GetConsoleCursorPosition(HOUT);
		ShowSavedGame();
		int id;
		while (true) {
			Message("Input the index of game you want to load: ", 0, 1);
			cin >> id;
			if (id <= 0 || id > ListSavedGame.size()) {
				Message("Invalid index!!", 1, 0);
			}
			else break;
		}
		//
		string filename = ListSavedGame[id - 1];
		filename = "Data\\" + filename + ".car";
		ifstream Data(filename);
		Data >> HeightOfTable >> WidthOfTable >> DifficultyComputer >> icon[0] >> icon[1];
		UpdateInit();
		Draw(DifficultyComputer);
		REP(i, HeightOfTable) REP(j, WidthOfTable) {
			Data >> table[i][j];
			int x = i * 2 + UpOfTable;
			int y = j * 2 + LeftOfTable;
			screen[x][y] = ' ';
			if (table[i][j] != -1) screen[x][y] = icon[table[i][j]];
		}
		Reload();
		//
		ListMessage.clear();
		cntMessage = 0;
		Message("Load game successfully", 1, 1);
		SetConsoleCursorPosition(HOUT, pos);
	}
};
