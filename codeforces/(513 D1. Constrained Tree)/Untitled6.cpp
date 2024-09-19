#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:100000000")
#include <stdio.h>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <fstream>
#include <iostream>
using namespace std;
#define N 1000100
int l[N], r[N], t[N], v[N], c, f, e;
void dfs(int i, int g, int h)
{
    e++;
    g=max(g, t[i]);
    if(r[i]<=l[i] || g>=h) { f=1; return; }
    if(l[i]!=-1)
    { 
        dfs(i+1, l[i], min(r[i], h));
    }
    v[c++]=i;
    if(e<=g) dfs(e, g, h);
}
int main()
{
    int i, j, n, q;
    scanf("%d%d", &n, &q);
    for(i=0; i<n; l[i]=-1, r[i]=n, t[i]=-1, i++);
    for(; q--; )
    {
        char s[10];
        scanf("%d%d%s", &i, &j, s); i--; j--;
        if(i>=j) { printf("IMPOSSIBLE\n"); return 0; }
        if(s[0]=='L') l[i]=max(l[i], j);
        else { r[i]=min(r[i], j); t[i]=max(t[i], j); }
    }
    dfs(0, n-1, n);
    if(f) { printf("IMPOSSIBLE\n"); return 0; }
    for(i=0; i<n; printf("%d ", v[i]+1), i++);
    return 0;
}