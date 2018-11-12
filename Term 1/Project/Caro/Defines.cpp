#include "Defines.h"

long long Rand(long long l, long long r) {
	return l + (ra * rm * rm * rm + ra * rm * rm + ra * rm * ra) % (r - l + 1);
}
