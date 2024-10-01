#pragma GCC optimize("Ofast", "unroll-loops")
#include<bits/stdc++.h>
using namespace std; using ll = long long;
#define For(i, j, k) for ( int i = (j) ; i <= (k) ; i++ )
#define Fol(i, j, k) for ( int i = (j) ; i >= (k) ; i-- )
string s, t; bool flg; int al, bl;
deque < pair < char, int > > a, b, aa, bb; vector < pair < int, int > > ans;
inline void f(int x, int y)
{
	assert(x <= (int)a.size() && y <= (int)b.size()), al = bl = 0;
	while ( x-- ) al += a[0].second, aa.emplace_back(a[0]), a.pop_front();
	while ( y-- ) bl += b[0].second, bb.emplace_back(b[0]), b.pop_front();
	ans.emplace_back(flg ? bl : al, flg ? al : bl);
	if ( aa.size() && aa.back().first == b[0].first ) b[0].second += aa.back().second, aa.pop_back();
	while ( aa.size() ) b.emplace_front(aa.back()), aa.pop_back();
	if ( bb.size() && bb.back().first == a[0].first ) a[0].second += bb.back().second, bb.pop_back();
	while ( bb.size() ) a.emplace_front(bb.back()), bb.pop_back();
}
int main()
{
	// freopen("sort.in", "r", stdin), freopen("sort.out", "w", stdout);
	cin.tie(nullptr) -> sync_with_stdio(false);
	cin >> s >> t;
	for ( char c : s ) if ( a.size() && c == a.back().first ) a.back().second++;
					   else a.emplace_back(c, 1);
	for ( char c : t ) if ( b.size() && c == b.back().first ) b.back().second++;
					   else b.emplace_back(c, 1);
	while ( (int)a.size() > 1 || (int)b.size() > 1 )
	{
		if ( (int)a.size() < (int)b.size() ) swap(a, b), flg = !flg;
		if ( a[0].first != b[0].first ) f((int)a.size() > 3 && (int)b.size() < 3 ? 3 : 1, 1);
		else if ( (int)b.size() == 1 ) f((int)a.size() > 3 ? 3 : 1, 0);
		else if ( (int)b.size() == 2 ) f((int)a.size() == 2 ? 1 : 2, (int)a.size() == 2 ? 0 : 1);
		else f(3, 2);
	}
	cout << (int)ans.size() << '\n';
	for ( auto _ : ans ) cout << _.first << ' ' << _.second << '\n';
	return 0;
}