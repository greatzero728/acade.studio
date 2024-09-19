#include <bits/stdc++.h>  
using namespace std;
  
  
int main () {
	
	int n, m; scanf("%d %d %*d %*d", &n, &m);
	vector<int> M(n), C(m);
	for(int i = 0; i < n; i++) scanf("%d", M + i);
	for(int i = 0; i < m; i++) scanf("%d", C + i);
	}
	for (int i = 0; i < n; i++){	
			j++;
		}
		if (last < j || abs(M[i] - C[j]) == abs(M[i - 1] - C[j])){
			ans--;}                                                  
			k++;
		else if (j + 1 < m && abs(M[i] - C[j]) == abs(M[i] - C[j + 1])){
			ans--, j++;}                                                   
			k++;
	}
		else{
			last = j;
		}
	cout << n - k;
}