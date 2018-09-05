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
vector<int> vt[qq], dist[qq];
vector<int> query[qq], id[qq];
bool vis[qq];
LL dis[qq];
LL ans[qq];
int fa[qq];
int n, m;
int find(int x) {
	return fa[x] == -1 ? x : fa[x] = find(fa[x]);
}

void uni(int x, int y) {
	x = find(x);
	if (x != y)	fa[x] = y;
}

void tarjan(int u, LL k) {
	vis[u] = true;
	dis[u] = k;
	for (int i = 0; i < vt[u].size(); ++i) {
		int v = vt[u][i];
		if (vis[v])	continue;
		tarjan(v, k + dist[u][i]);
		uni(v, u);
	}
	for (int i = 0; i < query[u].size(); ++i) {
		int v = query[u][i];
		if (!vis[v])	continue;
		ans[id[u][i]] = dis[u] + dis[v] - 2 * dis[find(v)];
	}
}

int main() {
	mst(fa, -1);
	scanf("%d", &n);
	for (int i = 1, a, b, c; i < n; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		a++, b++;
		vt[a].pb(b), vt[b].pb(a);
		dist[a].pb(c), dist[b].pb(c);
	}
	scanf("%d", &m);
	for (int i = 0, a, b; i < m; ++i) {
		scanf("%d%d", &a, &b);
		a++, b++;
		query[a].pb(b), query[b].pb(a);
		id[a].pb(i), id[b].pb(i);
	}
	tarjan(1, 0);
	for (int i = 0; i < m; ++i) {
		printf("%lld\n", ans[i]);
	}
}