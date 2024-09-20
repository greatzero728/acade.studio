#include <bits/stdc++.h>



#define inf 0x3f3f3f3f

#define INF 0x3f3f3f3f3f3f3f3fLL

#define mod 1000000007

#define pb push_back

#define mp make_pair

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



using namespace std;

typedef long long INT;

typedef vector<int> VI;

typedef pair<int, int> pii;

typedef pair<pii, int> pi3;

typedef double DO;



template<typename T, typename U> inline void smin(T &a, U b) {if (a>b) a=b;}

template<typename T, typename U> inline void smax(T &a, U b) {if (a<b) a=b;}



template<class T>inline void gn(T &x) {char c, sg=0; while (c=getchar(), (c>'9' || c<'0') && c!='-');for((c=='-'?sg=1, c=getchar():0), x=0; c>='0' && c<='9'; c=getchar()) x=(x<<1)+(x<<3)+c-'0';if (sg) x=-x;}

template<class T, class T1>inline void gn(T &x, T1 &y) {gn(x); gn(y);}

template<class T, class T1, class T2>inline void gn(T &x, T1 &y, T2 &z) {gn(x); gn(y); gn(z);}

template<class T>inline void print(T x) {if (x<0) {putchar('-');return print(-x);}if (x<10) {putchar('0'+x);return;} print(x/10);putchar(x%10+'0');}

template<class T>inline void printsp(T x) {print(x);putchar(' ');}

template<class T>inline void println(T x) {print(x);putchar('\n');}

int power(int a, int b, int m, int ans=1) {

	for (; b; b>>=1, a=1LL*a*a%m) if (b&1) ans=1LL*ans*a%m;

	return ans;

}



#define NN 222222

#define ls (u<<1)

#define rs (ls+1)



struct node {

	int st, ed, cnt;

	bool f1, f2, f3;

} mem[NN<<4];



void push_up(int u) {

	mem[u].cnt=mem[ls].cnt+mem[rs].cnt;

}



void push_down(int u) {

	if (mem[u].f1) {

		mem[ls].cnt=mem[ls].ed-mem[ls].st;

		mem[rs].cnt=mem[rs].ed-mem[rs].st;

		mem[ls].f1=mem[rs].f1=1, mem[u].f1=0;

		mem[ls].f2=mem[ls].f3=mem[rs].f2=mem[rs].f3=0;

	}

	if (mem[u].f2) {

		mem[ls].cnt=mem[rs].cnt=0;

		mem[ls].f2=mem[rs].f2=1, mem[u].f2=0;

		mem[ls].f1=mem[ls].f3=mem[rs].f1=mem[rs].f3=0;

	}

	if (mem[u].f3) {

		mem[ls].cnt=mem[ls].ed-mem[ls].st-mem[ls].cnt;

		mem[rs].cnt=mem[rs].ed-mem[rs].st-mem[rs].cnt;

		mem[ls].f3^=1, mem[rs].f3^=1, mem[u].f3=0;

	}

}



void build(int u, int L, int R) {

	mem[u].st=L, mem[u].ed=R, mem[u].cnt=0;

	mem[u].f1=mem[u].f2=mem[u].f3=0;

	if (L+1==R) return;

	build(ls, L, L+R>>1);

	build(rs, L+R>>1, R);

	push_up(u);

}



void update(int u, int L, int R, int t) {

	int st=max(mem[u].st, L);

	int ed=min(mem[u].ed, R);

	if (st>=ed) return;

	if (mem[u].st==st && mem[u].ed==ed) {

		if (t==1) mem[u].cnt=mem[u].ed-mem[u].st, mem[u].f1=1, mem[u].f2=mem[u].f3=0;

		if (t==2) mem[u].cnt=0, mem[u].f1=mem[u].f3=0, mem[u].f2=1;

		if (t==3) mem[u].cnt=mem[u].ed-mem[u].st-mem[u].cnt, mem[u].f3^=1;

		return;

	}

	push_down(u);

	update(ls, st, ed, t);

	update(rs, st, ed, t);

	push_up(u);

}



int calc(int u, int L, int R) {

	int st=max(mem[u].st, L);

	int ed=min(mem[u].ed, R);

	if (st>=ed) return 0;

	if (mem[u].st==st && mem[u].ed==ed) return mem[u].cnt;

	push_down(u);

	return calc(ls, st, ed)+calc(rs, st, ed);

}



int t[NN];

INT l[NN], r[NN], arr[NN<<3];



int main(){

#ifndef ONLINE_JUDGE

	freopen("in.in", "r", stdin);

//	freopen("out.out", "w", stdout);

#endif



	int n, m=0;

	cin>>n;

	arr[m++]=0;

	arr[m++]=1;

	for (int i=0; i<n; i++) {

		gn(t[i], l[i], r[i]);

		arr[m++]=l[i]-1, arr[m++]=l[i], arr[m++]=l[i]+1;

		arr[m++]=r[i]-1, arr[m++]=r[i], arr[m++]=r[i]+1;

	}

	sort(arr, arr+m);

	m=unique(arr, arr+m)-arr;

	

	build(1, 0, m);

	for (int i=0; i<n; i++) {

		int L=lower_bound(arr, arr+m, l[i])-arr;

		int R=lower_bound(arr, arr+m, r[i])-arr;

		update(1, L, R+1, t[i]);

		int st=0, ed=m;

		while (ed-st>1) {

			int md=st+ed>>1;

			if (calc(1, 1, md+1)==md) st=md;

			else ed=md;

		}

		println(arr[st]+1);

	}

	return 0;

}


   