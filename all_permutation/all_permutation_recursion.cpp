#include <cstdio>
#include <cstring>

void swap_element(char *st, int i, int j) {
	char ch = st[i];
	st[i] = st[j];
	st[j] = ch;
}

bool check(char *st, int l, int r) {
	for (int i = l ; i < r; ++i) {
		if (st[i] == st[r])	return false;
	}
	return true;
}

void all_permuation(char *st, int start, int len) {
	if (start == len) {
		printf("%s\n", st);
		return;
	}
	for (int i = start; i < len; ++i) {
		if (!check(st, start, i)) continue;
		swap_element(st, i, start);
		all_permuation(st, start + 1, len);
		swap_element(st, i, start);
	}
}

int main() {
	char st[] = "122";
	all_permuation(st, 0, strlen(st));
}