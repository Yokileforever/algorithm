#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;
#define LL long long

LL getCntOfChild(LL curNum, LL n) {
	LL cnt = 1;
	LL p = 10;
	for ( ; curNum * p <= n; p *= 10) {
		if (curNum * p + p - 1 < n) {
			cnt += p;
		} else {
			cnt += n - curNum * p + 1;
		}
	}
	return cnt;
}

LL solve(LL n, LL m) {
	LL ans = 1;
	while (m > 0) {
		LL cnt = getCntOfChild(ans, n);
		if (cnt < m) {
			m -= cnt;
			ans++;
		} else {
			m--;
			if (m == 0)	break;
			ans *= 10;
		}
	}
	return ans;
}

int main() {
	LL n, m;	scanf("%lld%lld", &n, &m);
	printf("%lld\n", solve(n, m));
}