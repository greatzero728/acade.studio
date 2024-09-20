#include <bits/stdc++.h>



#define inf 0x3f3f3f3f

#define MOD 1000000007

#define pb push_back

#define sq(x) ((x)*(x))

#define x first

#define y second

#define eps 1e-8

#define bpt(x) (__builtin_popcount(x))

#define bptl(x) (__builtin_popcountll(x))

#define bit(x, y) (((x)>>(y))&1)

#define bclz(x) (__builtin_clz(x))

#define bclzl(x) (__builtin_clzll(x))

#define bctz(x) (__builtin_ctz(x))

#define bctzl(x) (__builtin_ctzll(x))

#define debug(x) cout << #x << " = " << x << endl



using namespace std;

typedef long long INT;

typedef vector<int> VI;

typedef pair<int, int> pii;

typedef pair<pii, int> pi3;

typedef double DO;



template<typename T, typename U> inline void smin(T &a, U b) {if (a>b) a=b;}

template<typename T, typename U> inline void smax(T &a, U b) {if (a<b) a=b;}



#define NN 510

char s[NN][NN];

int n, m, ans[6000010];



struct query {

	int x1, y1, x2, y2, id;

	void input(int _id){

		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		id=_id;

	}

} Q;



bitset <NN> dp[2][NN][NN];

void solve(int L, int R, vector <query> v){

	if(L>R) return ;

	int mid=L+R>>1;

	

	for(int i=mid; i>=L; i--){

		for(int j=m; j; j--){

			dp[0][i][j].reset();

			if(s[i][j]=='.'){

				dp[0][i][j]|=dp[0][i][j+1];

				if(i==mid) dp[0][i][j].set(j);

				else dp[0][i][j]|=dp[0][i+1][j];

			}

		}

	}

	

	for(int i=mid; i<=R; i++){

		for(int j=1; j<=m; j++){

			dp[1][i][j].reset();

			if(s[i][j]=='.'){

				dp[1][i][j]|=dp[1][i][j-1];

				if(i==mid) dp[1][i][j].set(j);

				else dp[1][i][j]|=dp[1][i-1][j];

			}

		}

	}

	

	vector <query> v1, v2;

	for(int i=v.size(); i--; ){

		if(v[i].x1<=mid && v[i].x2>=mid){

			ans[v[i].id]=(dp[0][v[i].x1][v[i].y1]&dp[1][v[i].x2][v[i].y2]).any();

		}

		else if(v[i].x2<mid) v1.pb(v[i]);

		else v2.pb(v[i]);

	}

	

	solve(L, mid-1, v1);

	solve(mid+1, R, v2);

}



vector <query> v;

int main() {

	

	cin >> n >> m;

	for(int i=1; i<=n; i++) scanf("%s", s[i]+1);

	

	int q;

	cin >> q;

	

	for(int i=0; i<q; i++){

		Q.input(i);

		v.pb(Q);

	}

	

	solve(1, n, v);

	

	for(int i=0; i<q; i++){

		puts(ans[i] ? "Yes" : "No");

	}

	

	return 0;

}
                             