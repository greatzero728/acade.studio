#include<cstdio>
#include<algorithm>
#define rep(i,a) for( int i = 0; i != (a); ++i )

typedef long long ll;

int n;
ll bit[100001];

void add( int k, ll x )
{
	for( int i = k+1; i <= n; i += i&-i )
		bit[i] = std::max( bit[i], x );

	return;
}

ll sum( int k )
{
	ll ret = 0;

	for( int i = k; i > 0; i -= i&-i )
		ret = std::max( ret, bit[i] );

	return ret;
}

int main()
{
	scanf( "%d", &n );
	rep( i, n )
	{
		int x;
		scanf( "%d", &x );
		add( x-1, sum( x-1 )+x );
	}

	printf( "%lld\n", (ll(n)*(n+1)>>1)-sum(n) );

	return 0;
}