#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int qq = 1e5 + 10;
const int INF = 1e9 + 10;

int num[] = {10, 5, 4, 3, 100, 200, 4000, 3000, 2000, 2500, 3500, 3400, 3200};
int bucketMaxn[qq], bucketMinx[qq];

int main() {
	int n = sizeof(num) / sizeof(int);
	int maxn = -INF, minx = INF;
	for (int i = 0; i < n; ++i) {
		maxn = max(maxn, num[i]);
		minx = min(minx, num[i]);
	}
	for (int i = 0; i < n + 1; ++i) {
		bucketMinx[i] = INF;
		bucketMaxn[i] = -INF;
	}
	int segment = (maxn - minx) / n;
	for (int i = 0; i < n; ++i) {
		int id = (num[i] - minx) / segment;
		bucketMaxn[id] = max(bucketMaxn[id], num[i]);
		bucketMinx[id] = min(bucketMinx[id], num[i]);
	}
	int preMaxn = -1;
	int ans1 = -1;
	for (int i = 0; i < n + 1; ++i) {
		if (bucketMaxn[i] != -INF) {
			if (preMaxn == -1) {
				preMaxn = bucketMaxn[i];
			} else {
				ans1 = max(ans1, bucketMinx[i] - preMaxn);
				preMaxn = bucketMaxn[i];
			}
		}
	}
	sort(num, num + n);
	int ans2 = -1;
	for (int i = 1; i < n; ++i) {
		ans2 = max(ans2, num[i] - num[i - 1]);
	}
	printf("%d\n%d\n", ans1, ans2);
	return 0;
}