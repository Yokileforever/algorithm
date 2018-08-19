#include <cstdio>
#include <cstring>

void all_permuation(char *st, int len, bool *vis, char *ans, int cnt) {
	if (cnt == len) {
		printf("%s\n", ans);
		return;
	}
	for (int i = 0; i < len; ++i) {
		if (!vis[i]) {
			vis[i] = true;
			ans[cnt] = st[i];
			all_permuation(st, len, vis, ans, cnt + 1);
			vis[i] = false;
		}
	}
}

int main() {
	char st[] = "123";
	bool vis[strlen(st)];
	memset(vis, 0, sizeof(vis));
	char ans[strlen(st) + 5];
	memset(ans, 0, sizeof(ans));
	all_permuation(st, strlen(st), vis, ans, 0);
}