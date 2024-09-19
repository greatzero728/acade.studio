#include <bits/stdc++.h>

using namespace std ;

const int MAX = 2000 + 10 ;

int arr[MAX] , mask[20] = {119, 18, 93, 91, 58, 107, 111, 82, 127, 123} , cost[MAX][20] ;
int n , k ;
int dp[MAX][MAX] ;

bool solve(int idx , int rem)
{
	if(rem < 0)
		return 0 ;
	if(idx == n)
		return (rem == 0) ;
	int &ret = dp[idx][rem] ;
	if(ret != -1)
		return ret ;
	ret = 0 ;
	for(int j = 9 ; j >= 0 ; --j)
	{
		if(cost[idx][j] == -1)
			continue ;
		ret |= solve(idx+1 , rem - cost[idx][j]) ;
	}
	return ret ;
}

void build(int idx , int rem)
{
	if(idx == n)
		return ;
	for(int j = 9 ; j >= 0 ; --j)
	{
		if(cost[idx][j] == -1)
			continue ;
		if(solve(idx+1 , rem - cost[idx][j]) == true)
		{
			cout<<j ;
			build(idx+1 , rem - cost[idx][j]) ;
			return ;
		}
	}
	return ;
}

int main()
{
	memset(dp , -1 , sizeof(dp)) ;
	ios_base::sync_with_stdio(0) ;
	cin.tie(0) ;
	cin>>n>>k ;
	for(int i = 0 ; i < n ; ++i)
	{
		for(int j = 6 ; j >= 0 ; --j)
		{
			char c ;
			cin>>c ;
			if(c == '1')
				arr[i] += (1 << j) ;
		}
	}
	for(int i = 0 ; i < n ; ++i)
	{
		for(int j = 9 ; j >= 0 ; --j)
		{
			int x = (arr[i] & mask[j]) ;
			cost[i][j] = -1 ;
			if(x != arr[i])
				continue ;
			cost[i][j] =  __builtin_popcount(mask[j]) - __builtin_popcount(arr[i]) ;
		}
	}
	bool ans = solve(0 , k) ;
	if(ans == 0)
		return cout<<-1<<"\n" , 0 ;
	build(0 , k) ;
	return 0 ;
}