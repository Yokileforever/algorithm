#include <cstdio>
#include <cstring>
#include <cmath>

const int qq = 1e5 + 10;

int treeNum[qq][10];
int value[qq];
int tot;

void clear(int cur) {
//	printf("-1\n");
	memset(treeNum[cur], -1, sizeof(treeNum[cur]));
}

void insert(int x) {
	char num[20];
	memset(num, 0, sizeof(num));
	sprintf(num, "%d", x);
	int len = strlen(num);
	int cur = 0;
	for (int i = 0; i < len; ++i) {
		int idx = num[i] - '0';
		if (treeNum[cur][idx] == -1) {
			clear(++tot);
			treeNum[cur][idx] = tot;
		}
		cur = treeNum[cur][idx];
	}
	value[cur] = 1;
}

void solve(int n) {
	tot = 0;
	clear(tot);
	for (int i = 1; i <= n; ++i) {
		insert(i);
	}
}

void dfs(int now, int cur) {
	if (value[cur]) {
		printf("%d\n", now);
	}
	for (int i = 0; i < 10; ++i) {
		if (treeNum[cur][i] != -1) {
			dfs(now * 10 + i, treeNum[cur][i]);
		}
	}
}

int main() {
	int n;	scanf("%d", &n);
	solve(n);
	dfs(0, 0);
}