#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<set>
#include<assert.h>
using namespace std;
#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define FORD(i,a,b) for(int i = a; i >= b; --i)
#define REP(i,n) FOR(i,0,(n)-1)
#define RI(i,n) FOR(i,1,n)
#define pb push_back
#define mp make_pair
#define st first
#define nd second
#define mini(a,b) a=min(a,b)
#define maxi(a,b) a=max(a,b)
bool debug;
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int inf = 1e9 + 5;
const int nax = 1e6 + 5;

struct wezel{
	int lewy;
	int prawy;
	wezel(int l=-1, int p=-1): lewy(l), prawy(p) {}
};

wezel d[nax];
int n,c,czas,a,b;
int najwi[nax], najmi[nax];
char t[1000];
vector<int> vl[nax], vp[nax];
bool mozna = true;

void swag(int x, int p) {
	int najw = -1;
	int najm = p+1;
	bool zle = false;
	//printf("robimy %d %d %d\n",x,l,p);
	
	if (x > n)
		return;
	
	if (x == p) {
		if (!vl[x].empty() || !vp[x].empty())
			mozna = false;
		return;
	}
	
	for (auto i: vl[x]) {
		najw = max(najw,najwi[i]);
		if (najmi[i] < czas || najwi[i] > p)
			zle = true;
	}
	
	FOR(i,x+1,najw) {
		najw = max(najw,najwi[i]);
	}
	
	for (auto i: vp[x]) {
		najm = min(najm,najmi[i]);
		if (najmi[i] < czas || najwi[i] > p)
			zle = true;
	}

	//printf("%d %d\n",najw,najm);
	
	if (najw >= najm || zle) {
		mozna = false;
		return;
	}
	
	//printf("mamy %d %d %d\n",x,najw,najm);
	if (najw != -1) {
		++czas;
		d[czas] = wezel(-1,-1);
		d[x].lewy = czas;
		swag(czas, najw);
	}
	
	if (czas < p) {
		++czas;
		d[czas] = wezel(-1,-1);
		d[x].prawy = czas;
		swag(czas,p);
	}
}

void inorder(int x) {
	if (d[x].lewy != -1)
		inorder(d[x].lewy);
	printf("%d ",x);
	if (d[x].prawy != -1)
		inorder(d[x].prawy);
}

int main(int argc, char * argv[]) {
	debug = argc > 1;
	scanf("%d%d",&n,&c);
	FOR(i,1,n) najwi[i] = najmi[i] = i;
	REP(i,c) {
		scanf("%d %d %s",&a,&b,t);
		if (b <= a) {
			puts("IMPOSSIBLE");
			return 0;
		}
		if (b > a) {
			if (t[0] == 'L')
				vl[a].pb(b);
			else
				vp[a].pb(b);
		}
	}
	
	FORD(i,n,1) {
		for (auto j: vl[i])
			najwi[i] = max(najwi[i],najwi[j]);
		for (auto j: vp[i])
			najwi[i] = max(najwi[i],najwi[j]);
	}
	
	/*FORD(i,n,1) {
		for (auto j: vl[i])
			najwi[i] = max(najwi[i],najwi[j]);
		for (auto j: vp[i])
			najwi[i] = max(najwi[i],najwi[j]);
	}*/
	
	czas = 1;
	d[1] = wezel(-1,-1);
	//puts("KK");
	swag(1,n);
	if (mozna) {
		//puts("KK");
		inorder(1);
		puts("");
	}
	else
		puts("IMPOSSIBLE");
	return 0;
}
