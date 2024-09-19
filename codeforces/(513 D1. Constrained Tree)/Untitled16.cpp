//*
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <functional>
#define MOD 1000000007
#define MAX ((1<<30)-1)
#define MAX2 ((1ll<<62)-1)
#define mp make_pair
#pragma warning(disable:4996)
using namespace std;

typedef long long ll;
typedef unsigned int ui;
typedef long double ldb;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;

int n, m;
vector<int> l[1000005], r[1000005];

vector<int> dab;

void sayno()
{
	printf("IMPOSSIBLE");
	exit(0);
}

int cur;

int back(int now, int en)
{
	int i, j;
	cur=now;
	if(l[now].size() && l[now][0] <= now) sayno();
	if(l[now].size())
	{
		back(now+1, l[now].back());
	}
	dab.push_back(now);
	if(r[now].size() && r[now][0] <= cur) sayno();
	if(r[now].size() || cur < en) back(cur+1, max(en, r[now].size()?r[now].back():en));
	return 1;
}

int main()
{
	int i, j, k;
	cin>>n>>m;
	for(i=0;i<m;i++)
	{
		int x, y;
		char a[10];
		scanf("%d%d%s", &x, &y, a);
		x--, y--;
		if(x >= y) sayno();
		if(a[0] == 'L') l[x].push_back(y);
		else r[x].push_back(y);
	}
	for(i=0;i<n;i++) sort(l[i].begin(), l[i].end()), sort(r[i].begin(), r[i].end());
	int x=back(0, n-1);
	for(i=x+1;i<n;i++) dab.push_back(i);
	for(i=0;i<n;i++) printf("%d ", dab[i]+1);
	return 0;
}
//*/