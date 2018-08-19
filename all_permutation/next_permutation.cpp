#include <cstdio>
#include <cstring>

void swap_element(int *num, int i, int j) {
	int tmp = num[i];
	num[i] = num[j];
	num[j] = tmp;
}

void showArray(int *num, int n) {
	for (int i = 0; i < n; ++i) {
		printf("%d ", num[i]);
	}
	puts("");
}

void reverseArray(int *num, int l, int r) {
	while (l < r) {
		swap_element(num, l, r);
		l++, r--;
	}
}

void next_permutation(int *num, int n) {
	int id = -1;
	for (int i = n - 2; i >= 0 && id == -1; --i) {
		if (num[i] < num[i + 1]) {
			id = i;
		}
	}
//	printf("%d\n", id);
	if (id == -1)	return;
	int perferMinx = -1;
	for (int i = n - 1; i > id; --i) {
		if (num[i] > num[id]) {
			if (perferMinx == -1)	perferMinx = i;
			else	perferMinx = num[perferMinx] < num[i] ? perferMinx : i;
		}
	}
	swap_element(num, id, perferMinx);
	reverseArray(num, id + 1, n - 1);
//	showArray(num, n);
}


int main() {
	int num[] = {1, 2, 3, 4, 5, 6, 7, 8};
	int n = 8;
	for(int i = 0; i < n; ++i) {
		next_permutation(num, n);
		showArray(num, n);
	}
}