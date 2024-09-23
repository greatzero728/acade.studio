#include<bits/stdc++.h>



using namespace std;



int a, b, c, d, i;



int main(){

	

	scanf("%d%d%d%d", &a, &b, &c, &d);

	

	if(a<c || b<d || abs(c-d)>1){

		puts("-1");

		return 0;

	}

	

	if(c==d){

		if(a==c){

			if(b==d){

				puts("-1");

				return 0;

			}

			for(i=0; i<d; i++) printf("74");

			for(i=d; i<b; i++) printf("7");

		}

		else{

			for(i=c+1; i<a; i++) printf("4");

			for(i=0; i<c; i++) printf("47");

			for(i=d; i<b; i++) printf("7");

			puts("4");

		}

		return 0;

	}

	

	if(c>d){

		if(b==d){

			puts("-1");

			return 0;

		}

		for(i=c; i<a; i++) printf("4");

		for(i=0; i<c; i++) printf("47");

		for(i=c; i<b; i++) printf("7");

	}

	else{

		if(a==c){

			puts("-1");

			return 0;

		}

		printf("7");

		for(i=c; i<a; i++) printf("4");

		for(i=2; i<d; i++) printf("74");

		for(i=d-1; i<b; i++) printf("7");

		puts("4");

	}

	return 0;

}
                    