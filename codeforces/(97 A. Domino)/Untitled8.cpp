#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int max_n = 30;
const int max_num = 6;
const int max_c = ((max_num + 1) * (max_num + 2)) / 2;
int res, num[max_n][max_n], cnt, used[max_c / 2], n, m;
char a[max_n][max_n];
bool used_pairs[max_num + 1][max_num + 1];
vector < pair <int, int> > pairs;

void compute(int k) {
	if (k * 2 == cnt) {
		memset(used_pairs, 0, sizeof(used_pairs));
		bool ok = true;
		for (int i = 0; i < max_c; ++i) {
			int X = used[pairs[i].first], Y = used[pairs[i].second];
			if (used_pairs[X][Y]) {
				ok = false;
				break;
			} else used_pairs[X][Y] = used_pairs[Y][X] = true;
		}
		if (ok) {
			res++;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j)
					if (num[i][j] != -1)
						a[i][j] = used[num[i][j]] + '0';
		}
	} else
		for (int i = 0; i < cnt; ++i)
			if (used[i] == -1) {
				for (int j = i + 1; j < cnt; ++j)
					if (used[j] == -1) {
						used[i] = used[j] = k;
						compute(k + 1);
						used[i] = used[j] = -1;
					}
				break;
			}
}

int main() {
	scanf("%d%d\n", &n, &m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			scanf("%c", &a[i][j]);
		scanf("\n");
	}
	memset(num, -1, sizeof(num));
	cnt = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if ((a[i][j] != '.') && (num[i][j] == -1))
				num[i][j] = num[i + 1][j] = num[i][j + 1] = num[i + 1][j + 1] = cnt++;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (num[i][j] != -1) {
				if ((i < n) && (a[i][j] == a[i + 1][j]))
					pairs.push_back(make_pair(num[i][j], num[i + 1][j]));
				if ((j < m) && (a[i][j] == a[i][j + 1]))
					pairs.push_back(make_pair(num[i][j], num[i][j + 1]));
			}
	res = 0;
	memset(used, -1, sizeof(used));
	compute(0);
	printf("%d\n", res * 5040);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			printf("%c", a[i][j]);
		printf("\n");
	}
	return 0;
}