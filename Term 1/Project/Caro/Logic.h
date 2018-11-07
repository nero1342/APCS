#pragma once
#include "Defines.h"


bool inside(int i, int j, int h, int w) {
	return i >= 0 && j >= 0 && i < h && j < w;
}

bool ValidWin(int table[N][N], int h, int w) {
	// Horizontal
	REP(u, h) {
		REP(v, w - 4) if (table[u][v] != -1) {
			int c = table[u][v];
			int cnt = 0;
			for (int vv = v; cnt < 5 && table[u][vv] == c; ++vv) ++cnt;
			if (cnt == 5) return true;
		}
	}
	// Vertical
	REP(u, h - 4) {
		REP(v, w) if (table[u][v] != -1) {
			int c = table[u][v];
			int cnt = 0;
			for (int uu = u; cnt < 5 && table[uu][v] == c; ++uu) ++cnt;
			if (cnt == 5) return true;
		}
	}
	// Digional 1
	REP(u, h - 4) {
		REP(v, w - 4) if (table[u][v] != -1) {
			int c = table[u][v];
			int cnt = 0;
			for (int uu = u, vv = v; cnt < 5 && table[uu][vv] == c; ++uu, ++vv) ++cnt;
			if (cnt == 5) return true;
		}
	}
	// Digional 2
	FOR(u, 3, h - 1) {
		REP(v, w - 4) if (table[u][v] != -1) {
			int c = table[u][v];
			int cnt = 0;
			for (int uu = u, vv = v; cnt < 5 && table[uu][vv] == c; --uu, ++vv) ++cnt;
			if (cnt == 5) return true;
		}
	}
	return false;
}

int SureWin(int table[N][N], int c, int h, int w) {
	// Horizontal
	int cntWaytoWin = 0;
	REP(u, h) {
		FOR(v, 1, w - 4) if (table[u][v] != -1) {
			int cnt = 0;
			for (int vv = v; cnt < 4 && table[u][vv] == c; ++vv) ++cnt;
			if (cnt == 3) {
				if (table[u][v - 1] != 1 - c && table[u][v + 3] != 1 - c)
					cntWaytoWin++;
			}
			if (cnt == 4) {
				if (table[u][v - 1] != 1 - c || (v != w - 4 && table[u][v + 4] != 1 - c)) 
					cntWaytoWin++;
				if (table[u][v - 1] != 1 - c && (v != w - 4 && table[u][v + 4] != 1 - c)) 
					cntWaytoWin++;
			}
		}
	}
	// Vertical
	FOR(u, 1, h - 4) {
		REP(v, w) if (table[u][v] != -1) {
			int cnt = 0;
			for (int uu = u; cnt < 4 && table[uu][v] == c; ++uu) ++cnt;
			if (cnt == 3) {
				if (table[u - 1][v] != 1 - c && table[u + 3][v] != 1 - c) 
					cntWaytoWin++;
			}
			if (cnt == 4) {
				if (table[u - 1][v] != 1 - c || (u != h - 4 && table[u + 4][v] != 1 - c)) 
					cntWaytoWin++;
				if (table[u - 1][v] != 1 - c && (u != h - 4 && table[u + 4][v] != 1 - c)) 
					cntWaytoWin++;
			}
		}
	}
	// Digional 1
	FOR(u, 1, h - 4) {
		FOR(v, 1, w - 4) if (table[u][v] != -1) {
			int cnt = 0;
			for (int uu = u, vv = v; cnt < 4 && table[uu][vv] == c; ++uu, ++vv) ++cnt;
			if (cnt == 3) {
				if (table[u - 1][v - 1] != 1 - c && table[u + 3][v + 3] != 1 - c) 
					cntWaytoWin++;
			}
			if (cnt == 4) {
				if (table[u - 1][v - 1] != 1 - c ||
					(u != h - 4 && v != w && table[u + 4][v + 4] != 1 - c)) 
					cntWaytoWin++;
				if (table[u - 1][v - 1] != 1 - c &&
					(u != h - 4 && v != w && table[u + 4][v + 4] != 1 - c)) 
					cntWaytoWin++;
			}
		}
	}
	// Digional 2
	FOR(u, 3, h - 2) {
		FOR(v, 1, w - 4) if (table[u][v] != -1) {
			int cnt = 0;
			for (int uu = u, vv = v; cnt < 4 && table[uu][vv] == c; --uu, ++vv) ++cnt;
			if (cnt == 3) {
				if (table[u + 1][v - 1] != 1 - c && table[u - 3][v + 3] != 1 - c) 
					cntWaytoWin++;
			}
			if (cnt == 4) {
				if (table[u + 1][v - 1] != 1 - c ||
					(u != 3 && v != w - 4 && table[u - 4][v + 4] != 1 - c)) 
					cntWaytoWin++;
				if (table[u + 1][v - 1] != 1 - c &&
					(u != 3 && v != w - 4 && table[u - 4][v + 4] != 1 - c)) 
					cntWaytoWin++;
			}
		}
	}
	return cntWaytoWin;
}

const int dd[8] = { 0, 0, 1, -1, 1, -1, -1, 1 };
const int cc[8] = { 1, -1, 0, 0, 1, -1, 1, -1 };

pp FindLongest(int table[N][N], int h, int w, int turn) {
	vector<pp> candidate;
	int MX = 0;
	REP(u, h) REP(v, w) if (table[u][v] == -1) {
		REP(dir, 4) {
			int now = -1;
			table[u][v] = turn;
			for (int uu = u, vv = v; inside(uu, vv, h, w) && table[uu][vv] == turn; uu += dd[dir * 2], vv += cc[dir * 2]) ++now;
			for (int uu = u, vv = v; inside(uu, vv, h, w) && table[uu][vv] == turn; uu += dd[dir * 2 + 1], vv += cc[dir * 2 + 1]) ++now;
			if (now > MX) {
				MX = now;
				candidate.clear();
			}
			if (now == MX) {
				candidate.push_back(pp(u, v));
			}
			table[u][v] = -1;
		}
	}
	return candidate[Rand(0, candidate.size() - 1)];
}