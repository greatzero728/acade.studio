// LUOGU_RID: 109618721
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace std;
typedef long long ll;
inline char getc() {
	static char *p1, *p2, buf[1<<20];
	return p1==p2?(p2=(p1=buf)+fread(buf, 1, 1<<20, stdin), p1==p2?10:*p1++):*p1++;
}
inline int read() {
	int f=1, r=0; char c=getc();
	while (!isdigit(c)) f^=c=='-', c=getc();
	while (isdigit(c)) r=r*10+c-48, c=getc();
	return f?r:-r;
}
template<class T> inline void ckmin(T &x, T y) {if (y<x) x=y;}
template<class T> inline void ckmax(T &x, T y) {if (x<y) x=y;}
const int N=3e5+7;
int n, Q, W, ans[N*2], L[N], R[N], c[N], s_lsh, lsh[N*2], f[N], g[N];
int id[N]; pair<int, int> seq[N];
vector<pair<int, int> > modi[N*2];
__gnu_pbds::gp_hash_table<int, int> cost[N];
namespace sgt {
	int t[N<<2];
	#define ls (p<<1)
	#define rs (p<<1|1)
	inline void upd(int p) {t[p]=max(t[ls], t[rs]);}
	void modify(int p, int l, int r, int x, int v) {
		if (l==r) {t[p]=v; return;} int mid=(l+r)>>1;
		x<=mid?modify(ls, l, mid, x, v):modify(rs, mid+1, r, x, v); upd(p);
	}
	int query(int p, int l, int r, int x) {
		if (r<=x) return t[p]; int mid=(l+r)>>1, res=query(ls, l, mid, x);
		if (x>mid) ckmax(res, query(rs, mid+1, r, x)); return res;
	}
	#undef ls
	#undef rs
}
int main() {
	n=read(), W=read(), lsh[++s_lsh]=0, lsh[++s_lsh]=2e9;
	for (int i=1; i<=n; i++) {
		L[i]=read(), R[i]=read(), c[i]=read();
		lsh[++s_lsh]=L[i], lsh[++s_lsh]=R[i], seq[i]={c[i], i};
	}
	sort(lsh+1, lsh+s_lsh+1), s_lsh=unique(lsh+1, lsh+s_lsh+1)-lsh-1;
	for (int i=1; i<=n; i++) {
		L[i]=lower_bound(lsh+1, lsh+s_lsh+1, L[i])-lsh;
		R[i]=lower_bound(lsh+1, lsh+s_lsh+1, R[i])-lsh;
		modi[L[i]].push_back({i, 1}), modi[R[i]].push_back({i, 0});
	}
	set<int> s; sort(seq+1, seq+n+1);
	for (int i=1; i<=n; i++) id[seq[i].second]=i;
	for (int i=1, mx=0, len=0; i<s_lsh; i++) {
		for (auto [x, op]:modi[i])
			if (op) s.insert(x);
			else s.erase(x);
		if ((int)s.size()>=3) {ans[i]=len+mx; continue;}
		int D=lsh[i+1]-lsh[i];
		if (s.empty()) {len+=D, ans[i]=len+mx; continue;}
		int x=*s.begin();
		if ((int)s.size()==1) {
			f[x]+=D;
			if (c[x]<=W) {
				ckmax(mx, f[x]+g[x]), sgt::modify(1, 1, n, id[x], 0);
				int pos=lower_bound(seq+1, seq+n+1, make_pair(W-c[x], n+1))-seq-1;
				if (pos) ckmax(mx, f[x]+sgt::query(1, 1, n, pos));
				sgt::modify(1, 1, n, id[x], f[x]);
			}
		} else {
			int y=*s.rbegin();
			if (c[x]+c[y]<=W) {
				cost[x][y]+=D;
				ckmax(g[x], f[y]+cost[x][y]), ckmax(g[y], f[x]+cost[x][y]);
				ckmax(mx, max(f[x]+g[x], f[y]+g[y]));
			}
		}
		ans[i]=len+mx;
	}
	Q=read();
	while (Q--) {
		int x=read(), p=lower_bound(ans+1, ans+s_lsh, x)-ans;
		printf("%d\n", lsh[p+1]-(ans[p]-x));
	}
	return 0;
}