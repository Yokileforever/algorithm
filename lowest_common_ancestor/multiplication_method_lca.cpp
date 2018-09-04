#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <utility>
#include <bitset>
#include <unistd.h>
#include <unordered_map>

using namespace std;

#define LL long long
#define pb push_back
#define mk make_pair
#define pill pair<int, int>
#define mst(a, b) memset(a, b, sizeof a)
#define lson (rt << 1)
#define rson ((rt << 1) | 1)

const int qq = 1e5 + 10;
const int INF = 1e9 + 10;
const int MOD = 1e9 + 7;
const int DEG = 20;
int rt, n, m;
int dep[qq];
int f[qq][25];
vector<int> vt[qq];
int bin[30];

void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	f[u][0] = fa;
	for (int i = 1; i < DEG; ++i) {
		f[u][i] = f[f[u][i - 1]][i - 1];
	}
	for (int i = 0; i < (int)vt[u].size(); ++i) {
		int v = vt[u][i];
		if (v == fa)	continue;
		dfs(v, u);
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) {
		swap(u, v);
	}
	for (int i = 0, d = dep[u] - dep[v]; d; ++i, d >>= 1) {
		if (d & 1)	u = f[u][i];
	}
	if (u == v)	return u;
	for (int i = DEG - 1; i >= 0; --i) {
		if (f[u][i] != f[v][i]) {
			u = f[u][i], v = f[v][i];
		}
	}
	return f[u][0];
}

int main() {
	mst(dep, 0);
	scanf("%d", &n);
	for (int u, v, i = 0; i < n; ++i) {
		scanf("%d%d", &u, &v);
		if (v == -1) {
			rt = u;
		} else {
			vt[u].pb(v), vt[v].pb(u);
		}
	}
	dfs(rt, -1);
	scanf("%d", &m);
	int a, b;
	while (m--) {
		scanf("%d%d", &a, &b);
		int fa = lca(a, b);
		int ans;
		if (fa == a) {
			ans = 1;
		} else if (fa == b) {
			ans = 2;
		} else {
			ans = 0;
		}
		printf("%d\n", ans);
	}
	return 0;
}