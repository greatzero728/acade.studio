#define ONLINE_JUDGE
#include<bits/stdc++.h>

using namespace std;

const int maxn = 100010;

long long arr[maxn*6];

int tp[maxn];

long long L[maxn], R[maxn];

struct Node {

	 Node *ls, *rs;

	 int ch;

	 int sum, sz;

} pool[maxn*12], *cur = pool;

void push_up( Node *u ) {

	u->sum = u->ls->sum + u->rs->sum;

}

Node *build( int L, int R ) {

	Node *ans = cur++;

	ans->ch = ans->sum = 0;

	if( L == R ) { 

	 	ans->sz = 1;

		return ans;

	}

	int md = L + R >> 1;

	ans->ls = build( L, md );

	ans->rs = build( md+1, R );

	push_up( ans );

	ans->sz = ans->ls->sz + ans->rs->sz;

	return ans;

}

void push_down( Node *u ) {

	if( u->ch ) {

		if( u->ch == 1 ) {

			u->ls->ch = u->rs->ch = 1;

			u->ls->sum = u->ls->sz;

			u->rs->sum = u->rs->sz;

		} else if( u->ch == 2 ) {

			u->ls->ch = u->rs->ch = 2;

			u->ls->sum = 0;

			u->rs->sum = 0;

		}

		else {

			u->ls->ch ^= 3;

			u->rs->ch ^= 3;

			u->ls->sum = u->ls->sz - u->ls->sum;

			u->rs->sum = u->rs->sz - u->rs->sum;

		}

		u->ch = 0;

	}

	return;

}

void cha( Node *u, int L, int R, int l, int r, int dir ) {

	if( l > R or L > r ) return;

	if( l <= L and R <= r ) {

		if( dir == 3 ) {

			u->ch ^= 3;

			u->sum = u->sz - u->sum;

		} else {

			u->ch = dir;

			if( dir == 1 ) u->sum = u->sz;

			else u->sum = 0;

		}

		return;

	}

	push_down( u );

	int md = L + R >> 1;

	cha( u->ls, L, md, l, r, dir );

	cha( u->rs, md+1, R, l, r, dir );

	push_up( u );

	return;

}

int find( Node *u, int L, int R ) {

	if( L == R ) return L;

	int md = L + R >> 1;

	push_down( u );

	if( u->ls->sum == u->ls->sz ) find( u->rs, md+1, R );

	else find( u->ls, L, md );

}

int main() {

	int n, num = 0;

	scanf("%d", &n);

	for( int i = 0; i < n; i ++ ) {

		scanf("%d%I64d%I64d", tp+i, L+i, R+i );

		for( int w = -1; w <= 1; w ++ ) {

			if( L[i] + w > 0 ) arr[num++] = L[i] + w;

			if( R[i] + w > 0 ) arr[num++] = R[i] + w;

		}

	}

	arr[num++] = 1;

	sort( arr, arr + num );

	num = unique( arr, arr + num ) - arr;

	Node *root = build( 0, num - 1 );

	for( int i = 0; i < n; i ++ ) {

		int l = lower_bound( arr, arr + num, L[i] ) - arr;

		int r = lower_bound( arr, arr + num, R[i] ) - arr;

		cha( root, 0, num-1, l, r, tp[i] );

		printf("%I64d\n", arr[find(root, 0, num - 1)] );

	}

	return 0;

}
          