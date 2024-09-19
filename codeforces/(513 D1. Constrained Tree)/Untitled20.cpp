#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <ctime>
#include <cassert>
#include <queue>
#include <stack>
#include <bitset>
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define NAME ""

using namespace std;
	
typedef long long ll;
typedef long double ld;

const ld PI = acos(-1.0);

const int MAXN = 501;

int g1[MAXN], g2[MAXN], g3[MAXN];
int lg[MAXN], rg[MAXN];
bool f[MAXN][MAXN];
int l[MAXN][MAXN];

char s[10];
int n, c;
void dfs(int v, int r)
{
	if (l[v][r] != v)
	{
		dfs(v + 1, l[v][r]);
	}
	printf("%d ", v);
	if (l[v][r] != r)
	{
		dfs(l[v][r] + 1, r);
	}
}

int main()
{
	scanf("%d%d", &n, &c);
	for (int i = 1; i <= n; i++)
	{
		g1[i] = i, g2[i] = n, g3[i] = i;
	}
	bool ok = true;
	for (int i = 0; i < c; i++)
	{
		int a, b;
		scanf("%d%d%s", &a, &b, s);
		if (a >= b) ok = false;
		if (s[0] == 'L')
		{
			g1[a] = max(g1[a], b);
		}
		else
		{
			g2[a] = min(g2[a], b - 1);
			g3[a] = max(g3[a], b);
		}
	}
	if (!ok)
	{
		printf("IMPOSSIBLE\n");
		return 0;
	}
	for (int i = n; i >= 1; i--)
	{
		for (int j = 1; j <= n; j++) f[i][j] = false;
		for (int j = g1[i]; j <= g2[i];  j++)
		{
			for (int ll = max(j, g3[i]); ll <= n; ll++)
			{
				bool ok = true;
				if (j != i)
				{
					ok = ok && f[i + 1][j];
				}
				if (ll != j)
				{
					ok = ok && f[j + 1][ll];
				}
				if (ok)
				{
					f[i][ll] = true;
					l[i][ll] = j;
				}
			}
		}
	}
	if (f[1][n])
	{
		dfs(1, n);
	}
	else printf("IMPOSSIBLE\n");
	return 0;
}