#pragma once
#include "Defines.h"
#include "Console.h"
#include "Logic.h"

namespace Computer {
	int myTable[N][N], h, w;
	int myTurn;

	void GetData(int table[N][N], int HeightOfTable, int WidthOfTable, int turn) {
		REP(i, h = HeightOfTable) REP(j, w = WidthOfTable) myTable[i][j] = table[i][j];
		myTurn = turn;
	}

	pp Implementation() {// Easy
		vector<pp> candidate;
		REP(i, h) REP(j, w) if (myTable[i][j] == -1) {
			bool ok = false;
			FOR(x, i - 1, i + 1) FOR(y, j - 1, j + 1) if (inside(x, y, h, w) && myTable[x][y] != -1) {
				ok = true;
			}
			if (ok) 
				candidate.push_back(pp(i, j));
		}
		if (candidate.empty()) {
			return pp(Rand(0, h - 1), Rand(0, w - 1));
		}
		int mychoice = Rand(0, candidate.size() - 1);
		return candidate[mychoice];
	}
	/*
	pp Random(int x, int y) {
		FOR(k, 1, min(h, w)) {
			vector<pp> candidate;
			FOR(i, x - k, x + k) FOR(j, y - k, y + k) if (inside(i, j, h, w)) {
				candidate.push_back(pp(i, j));
			}
			if (!candidate.empty()) {
				int mychoice = Rand(0, candidate.size() - 1);
				return candidate[mychoice];
			}
		}
	}
	*/

	pp Pivot1(int turn) {
		REP(i, h) REP(j, w) if (myTable[i][j] == -1) {
			myTable[i][j] = turn;
			if (ValidWin(myTable, h, w)) return pp(i, j);
			myTable[i][j] = -1;
		}
		return pp(-1, -1);
	}

	pp Pivot2(int turn) {
		REP(i, h) REP(j, w) if (myTable[i][j] == -1) {
			myTable[i][j] = turn;
			if (SureWin(myTable, turn, h, w) > 1) 
				return pp(i, j);
			myTable[i][j] = -1;
		}
		return pp(-1, -1);
	}

	/*pp Pivot3(int turn) {
		REP(i, h) REP(j, w) if (myTable[i][j] == -1) {
			myTable[i][j] = turn;
			if (SureWin(myTable, turn, h, w) > 0) return pp(i, j);
			myTable[i][j] = -1;
		}
		return pp(-1, -1);
	}
	*/
	pp Medium() {
		// Win
		pp Win = Pivot1(myTurn);
		if (Win.first != -1) return Win;
		// Save
		pp Lose = Pivot1(1 - myTurn);
		if (Lose.first != -1) return Lose;
		// Will but not now :))
		// Two ways
		Win = Pivot2(myTurn);
		if (Win.first != -1) return Win;
		Lose = Pivot2(1 - myTurn);
		if (Lose.first != -1) return Lose;
		int sum = 0;
		REP(i, h) REP(j, w) {
			if (myTable[i][j] != -1) sum++;

		}
		if (sum == 1) 
			return FindLongest(myTable, h, w, 1 - myTurn);
		int t = Rand(0, 1);
		return FindLongest(myTable, h, w, t);
	}
};
