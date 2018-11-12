#pragma once

namespace Player {
	
	int GetHeight();
	
	int GetWidth();

	int GetLengthToWin();

	void UpdateHeight(int height);

	void UpdateWidth(int width);

	void UpdateLengthToWin(int length);

	char GetIcon(int id);

	void UpdateIcon(int id, char c);

	int GetStatic(int status, int level);

	int idH(int x);

	int idW(int y);

	void UpdateInit();

	void ReadInit();

	void ResetStatics();

	void UpdateStatics(int value, int Difficulty);

	void UpdateSizeTable(int h, int w);

	void Reload();

	void Draw(int isPvComputer);

	void Message(string message, int isEndline, int isNumbered);

	void Unchoose();

	bool Choose(COORD cur);

	COORD FindPosition(pp x);

	void Move();

	void InitListSavedGame();

	void UpdateListSavedGame();

	void ShowSavedGame();

	void RemoveGame();

	void SaveGame();

	void LoadGame();
};
