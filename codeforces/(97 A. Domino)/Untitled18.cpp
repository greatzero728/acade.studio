#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define li long long
#define ld long double
#define x first
#define y second
#define pt pair<int, int>
#define pll pair<li, li>
#define forn(i, t) for(int i = 0; i < (t); i++)
#define fore(i, f, t) for(int i = (f); i < (t); i++)
#define forr(i, f, t) for(int i = (f) - 1; i >= (t); i--)
#define all(x) (x).begin(), (x).end()
#define ins insert

using namespace std;


const int INF = 1e9;
const int MOD = 1e9 + 7;
const li INF64 = 1e18;
const ld EPS = 1e-7;

mt19937 myrand(time(NULL));

const int N = 31;
const int AL = 7;

int n, m;
char a[N][N];


bool read(){
	if(scanf("%d%d\n", &n, &m) != 2)
		return 0;
	forn(i, n)
		scanf("%s\n", a[i]);
	return 1;
}

int b[N][N];
char g[N][N];
char used[AL][AL];
int cur[N], res[N];
li ans;
int cnt;


void brute(int v, int clr){
	if (v == cnt){
		if (ans == 0)
			forn(i, N)
				res[i] = cur[i];
		ans++;
		return;
	}
	forn(i, min(7, clr + 1)){
		cur[v] = i;
		bool fl = 1;
		forn(j, v + 1)
			if (g[v][j] && used[cur[j]][i])
				fl = 0;
		if (fl){
			forn(j, v + 1)
				if (g[v][j]){
					if (!used[cur[j]][i])
						used[cur[j]][i] = used[i][cur[j]] = 1;
					else
						fl = 0;
				}
			if (fl)
				brute(v + 1, max(clr, i + 1));
			forn(j, v + 1)
				if (g[v][j])
					used[cur[j]][i] = used[i][cur[j]] = 0;
		}
	}
}


void solve(){
	cnt = 0;
	memset(b, 255, sizeof(b));
	forn(i, n)
		forn(j, m)
			if (a[i][j] != '.' && b[i][j] == -1){
				b[i][j] = b[i + 1][j] = b[i][j + 1] = b[i + 1][j + 1] = cnt;
				cnt++;
			}
	ans = 0;
	memset(used, 0, sizeof(used));
	memset(g, 0, sizeof(g));
	
	forn(i, n)
		forn(j, m){
			if (a[i][j] == '.')
				continue;
			if (i > 0 && a[i - 1][j] == a[i][j])
				g[b[i][j]][b[i - 1][j]] = g[b[i - 1][j]][b[i][j]] = 1;
			if (j > 0 && a[i][j - 1] == a[i][j])
				g[b[i][j]][b[i][j - 1]] = g[b[i][j - 1]][b[i][j]] = 1;
		}
	/*forn(i, n){
		forn(j, m)
			printf("%d(%c) ", b[i][j] + 1, a[i][j]);
		printf("\n");
	}
	forn(i, cnt)
		forn(j, i + 1)
			if (g[i][j])
				printf("%d %d\n", j + 1, i + 1);*/
	ans = 0;
	memset(used, 0, sizeof(used));
	memset(cur, 255, sizeof(cur));
	memset(res, 255, sizeof(res));
	brute(0, 0);
	printf("%lld\n", ans * 5040);
	forn(i, n){
		forn(j, m)
			printf("%c", b[i][j] == -1 ? '.' : '0' + res[b[i][j]]);
		printf("\n");
	}
}


int main(){
	#ifdef _DEBUG
		freopen("input.txt", "r", stdin);
	#endif
	while(read())
		solve();
	return 0;
}