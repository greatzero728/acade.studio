//              +-- -- --++-- +-In the name of ALLAH-+ --++-- -- --+              \\

#include <bits/stdc++.h>

using namespace std ;

int a1 , a2 , a3 , a4 , p ;

int main(){
	ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

	cin >> a1 >> a2 >> a3 >> a4 ;
	a1 -= a3 , a2 -= a3 , a4 -= a3 - 1 ;

	if (a4 == 2) a1 -- , a2 -- , p = 3 ;
	if (a4 == 1) {
		if (a1 > 0) a1 -- , p = 1 ;
		else a2 -- , p = 2 ;
	}

	if (a1 < 0 || a2 < 0 || a4 < 0 || a4 > 2) return cout << "-1\n" , 0 ;

	if (p & 2) cout << '7' ;
	for (int i = 0 ; i < a1 ; i ++) cout << '4' ;
	for (int i = 0 ; i < a3 ; i ++) cout << "47" ;
	for (int i = 0 ; i < a2 ; i ++) cout << '7' ;
	if (p & 1) cout << '4' ;
	cout << '\n' ;
}
