#include "Defines.h"
#include "Logic.h"

const int dd[8] = { 0, 0, 1, -1, 1, -1, -1, 1 };
const int cc[8] = { 1, -1, 0, 0, 1, -1, 1, -1 };
const long long inf = 1e6;

bool inside(int i, int j, int h, int w) {
	return i >= 0 && j >= 0 && i < h && j < w;
}

#define inside(i, j) inside(i, j, h, w)

bool ValidWin(int table[N][N], int h, int w, int LenToWin) {
	REP(dir, 4) {
		int vr = dd[dir * 2], vc = cc[dir * 2];
		REP(u, h) {
			REP(v, w) if (table[u][v] != -1) {
				int cnt = 0;
				int c = table[u][v];
				for (int vv = v, uu = u; inside(uu, vv) && cnt < LenToWin && table[uu][vv] == c; uu += vr, vv += vc) ++cnt;
				if (cnt == LenToWin) return true;
			}
		}
	}
	return false;
}

long long SureWin(int table[N][N], int c, int h, int w, int LenToWin) {
	long long cntWaytoWin = 0, cntMagic = 0;
	REP(dir, 4) {
		int vr = dd[dir * 2], vc = cc[dir * 2];
		REP(u, h) {
			REP(v, w) if (table[u][v] != -1) {
				if (inside(u - vr, v - vc) && table[u - vr][v - vc] == c) continue;
				int cnt = 0;
				for (int vv = v, uu = u; inside(uu, vv) && cnt < LenToWin - 1 && table[uu][vv] == c; uu += vr, vv += vc) ++cnt;
				if (cnt == LenToWin - 3) {
					if (inside(u - vr, v - vc) && table[u - vr][v - vc] != 1 - c && 
						inside(u + 4 * vr, v + 4 * vc) && table[u + 2 * vr][v + 2 * vc] != 1 - c 
						&& table[u + 3 * vr][v + 3 * vc] == c && table[u + 4 * vr][v + 4 * vc] != 1 - c) {
						cntWaytoWin += 1;
						cntMagic += table[u + 4 * vr][v + 4 * vc] == c;
					}
					if (inside(u + 2 * vr, v + 2 * vc) && table[u + 2 * vr][v + 2 * vc] != 1 - c && 
						inside(u - 3 * vr, v - 3 * vc) && table[u - vr][v - vc] != 1 - c 
						&& table[u - 2 * vr][v - 2 * vc] == c && table[u - 3 * vr][v - 3 * vr] != 1 - c) {
						cntWaytoWin += 1;
					}
				}
				if (cnt == LenToWin - 2) {
					if (inside(u - vr, v - vc) && inside(u + 3 * vr, v + 3 * vc) && table[u - vr][v - vc] != 1 - c && table[u + 3 * vr][v + 3 * vc] != 1 - c) {
						cntWaytoWin += 1;
					}
					if (inside(u - 2 * vr, v - 2 * vc) && table[u - vr][v - vc] != 1 - c && table[u - 2 * vr][v - 2 * vc] == c) {
						cntWaytoWin += 1;
						cntMagic++;
					}
					if (inside(u + 4 * vr, v + 4 * vc) && table[u + 3 * vr][v + 3 * vc] != 1 - c && table[u + 4 * vr][v + 4 * vc] == c) {
						cntWaytoWin += 1;
						cntMagic++;
					}
				}
				if (cnt == LenToWin - 1) {
					if (inside(u - vr, v - vc) && table[u - vr][v - vc] != 1 - c) 
						cntWaytoWin += 1, cntMagic++;
					if (inside(u + 4 * vr, v + 4 * vc) && table[u + 4 * vr][v + 4 * vc] != 1 - c)
						cntWaytoWin += 1, cntMagic++;
				}
			}
		}
	}
	return cntWaytoWin + inf * cntMagic;
}

pp FindLongest(int table[N][N], int h, int w, int turn) {
	vector<pp> candidate;
	int MX = 0;
	REP(u, h) REP(v, w) if (table[u][v] == -1) {
		REP(dir, 4) {
			int now = -1;
			table[u][v] = turn;
			for (int uu = u, vv = v; inside(uu, vv) && table[uu][vv] == turn; uu += dd[dir * 2], vv += cc[dir * 2]) ++now;
			for (int uu = u, vv = v; inside(uu, vv) && table[uu][vv] == turn; uu += dd[dir * 2 + 1], vv += cc[dir * 2 + 1]) ++now;
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

#undef inside(i, j) inside(i, j, h, w)