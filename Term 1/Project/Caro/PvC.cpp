#pragma once
#include "Defines.h"
#include "Console.h"
#include "Logic.h"
#include "PvC.h"

namespace Computer {
	int myTable[N][N], h, w;
	int myTurn;
	int LenToWin;
	
	const long long inf = 1e6;

	void GetData(int table[N][N], int HeightOfTable, int WidthOfTable, int turn, int ltw) {
		REP(i, h = HeightOfTable) REP(j, w = WidthOfTable) myTable[i][j] = table[i][j];
		myTurn = turn;
		LenToWin = ltw;
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

	pp Pivot1(int turn) {
		pp best = pp(-1, -1);
		REP(i, h) REP(j, w) if (myTable[i][j] == -1) {
			myTable[i][j] = turn;
			if (ValidWin(myTable, h, w, LenToWin)) best = pp(i, j);
			myTable[i][j] = -1;
			if (best.first != -1) return best;
		}

		return best;
	}


	long long CalScore(pp Point, int turn) {
		myTable[Point.first][Point.second] = turn;
		long long x = SureWin(myTable, turn, h, w, LenToWin);
		myTable[Point.first][Point.second] = -1;
		return x;
	}

	pp Pivot2(int turn) {
		vector<pp> candidate;
		long long best = 1;
		REP(i, h) REP(j, w) if (myTable[i][j] == -1) {
			long long now = CalScore(pp(i, j), turn);
			if (now > best) {
				candidate.clear();
				best = now;
			}
			if (now == best) candidate.push_back(pp(i, j));
		}
		if (candidate.empty() || best == 1) return pp(-1, -1);
		return candidate[Rand(0, candidate.size() - 1)];
	}

	pp Pivot3(int turn) {
		// Defense
		int cnt = SureWin(myTable, 1 - turn, h, w, LenToWin);
		int best = cnt;
		pp pbest = pp(-1, -1);
		REP(i, h) REP(j, w) if (myTable[i][j] == -1) {
			myTable[i][j] = turn;
			int now = SureWin(myTable, 1 - turn, h, w, LenToWin);
			myTable[i][j] = -1;
			if (now < best) {
				best = now;
				pbest = pp(i, j);
			}
		}
		return pbest;
	}

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

	pp Hard() {
		// Win
		pp Win = Pivot1(myTurn);
		if (Win.first != -1) return Win;
		// Save
		pp Lose = Pivot1(1 - myTurn);
		if (Lose.first != -1) return Lose;
		// Will but not now :))
		// Two ways
		Win = Pivot2(myTurn);
		Lose = Pivot3(1 - myTurn);
		if (Lose.first == -1) Lose = Pivot2(1 - myTurn);
		if (Win.first != -1 && Lose.first != -1) {
			if (CalScore(Lose, 1 - myTurn) >= inf) return Lose;
		}
		if (Win.first != -1) return Win;
		if (Lose.first != -1) return Lose;
		int sum = 0;
		REP(i, h) REP(j, w) {
			if (myTable[i][j] != -1) sum++;
		}
		if (sum = 0) {
			return pp(h / 2, w / 2);
		}
		if (sum == 1)
			return FindLongest(myTable, h, w, 1 - myTurn);
		int t = Rand(0, 1);
		return FindLongest(myTable, h, w, t);
	}
};

