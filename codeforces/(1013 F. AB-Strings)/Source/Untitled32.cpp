#include<bits/stdc++.h>



using namespace std;

typedef pair<int,int> operate;

const int NN=555555;



operate op[NN];

char tmpa[NN];

char tmpb[NN];

char a[NN];

char b[NN];

int la[NN];

int lb[NN];

int opn;

int na;

int nb;

int i,j,k,l,ax,bx,pria,prib,mn;



void add(int i,int j){

  op[opn++]={i,j};

}



void change(int ax,int bx){

  if(ax || bx) add(ax,bx);

  na=strlen(a+1);

  nb=strlen(b+1);

  

  int i;

  for(i=1; i<=bx; i++){

    tmpa[i]=b[i];

  }

  for(i=ax+1; i<=na; i++){

    tmpa[i-ax+bx]=a[i];

  }

  for(i=1; i<=ax; i++){

    tmpb[i]=a[i];

  }

  for(i=bx+1; i<=nb; i++){

    tmpb[i-bx+ax]=b[i];

  }

  na=na+bx-ax;

  nb=nb+ax-bx;

  for(i=1; i<=na; i++){

    a[i]=tmpa[i];

  }

  for(i=1; i<=nb; i++){

    b[i]=tmpb[i];

  }

  a[na+1]=0;

  b[nb+1]=0;

  for(i=1; i<=na; i++){

    la[i]=la[i-1];

    if(a[i]!=a[i-1]){

      la[i]++;

    }

  }

  for(i=1; i<=nb; i++){

    lb[i]=lb[i-1];

    if(b[i]!=b[i-1]){

      lb[i]++;

    }

  }

  for(::ax=1; a[::ax]==a[1]; ::ax++);::ax--;

  for(::bx=1; b[::bx]==b[1]; ::bx++);::bx--;

}





void print(){

  printf("%d\n",opn);

//  exit(0);

  for(int i=0; i<opn; i++){

    printf("%d %d\n",op[i].first,op[i].second);

  }

}



void solve(){

  mn=NN;

  int tmn=NN;

  int tpria;

  int tprib;

  

  for(i=1; i<na; i++){

    if(a[i]==a[i+1]) continue;

    //pria>0 prib=0

    j=la[na]-la[i];

    k=la[i]+lb[nb]-(a[i]==b[1]);

    if(abs(j-k)<=1){

      if(a[1]!=a[i+1]){

        if(max(j,k)-1<mn){

          mn=max(j,k)-1;

          pria=i;

          prib=0;

        }

      }else if(j!=k){

        if(tmn>min(j,k)){

          tmn=min(j,k);

          tpria=i;

          tprib=0;

        }

      }

    }

    

    //pria>0,prib=bx

    j=la[na]-la[i]+1-(b[bx]==a[i+1]);

    k=lb[nb]-1+la[i]-(a[i]==b[bx+1]);

//    cerr<<j<<' '<<k<<endl;

    

    if(abs(j-k)<=1){

      if(a[1]!=b[1]){

        if(max(j,k)-1<mn){

          mn=max(j,k)-1;

          pria=i;

          prib=bx;

        }

      }else if(j!=k){

        if(tmn>min(j,k)){

          tmn=min(j,k);

          tpria=i;

          tprib=bx;

        }

      }

    }

  }

  for(i=1; i<nb; i++){

    if(b[i]==b[i+1]) continue;

    //pria=0,prib>0

    j=la[na]+lb[i]-(b[i]==a[1]);

    k=lb[nb]-lb[i];

    if(abs(j-k)<=1){

      if(b[1]!=b[i+1]){

        if(max(j,k)-1<mn){

          mn=max(j,k)-1;

          pria=0;

          prib=i;

        }

      }else if(j!=k){

        if(tmn>min(j,k)){

          tmn=min(j,k);

          tpria=0;

          tprib=i;

        }

      }

    }

    //pria=ax,prib>0

    j=la[na]-1+lb[i]-(b[i]==a[ax+1]);

    k=lb[nb]-lb[i]+1-(a[ax]==b[i+1]);

    if(abs(j-k)<=1){

      if(a[1]!=b[1]){

        if(max(j,k)-1<mn){

          mn=max(j,k)-1;

          pria=ax;

          prib=i;

        }

      }else if(j!=k){

        if(tmn>min(j,k)){

          tmn=min(j,k);

          tpria=ax;

          tprib=i;

        }

      }

    }

  }

  if(mn==NN){

    pria=tpria;

    prib=tprib;

  }

}



void pp(){

  printf("%s\n%s\n\n",a+1,b+1);

}



int main(){

#ifndef ONLINE_JUDGE

  freopen("in.in","r",stdin);

  freopen("out.out","w",stdout);

#endif

  scanf("%s%s",a+1,b+1);

  change(0,0);

  if(a[1]==b[1] || abs(la[na]-lb[nb])>1){

    solve();

    change(pria,prib);

    if(mn==NN){

      solve();

      change(pria,prib);

    }

  }else{

    mn=max(la[na],lb[nb])-1;

  }

//  printf("%s\n%s\n",a+1,b+1);

  

  pria=0;

  prib=0;

  for(i=j=1; mn--; ){

    for(k=i; i<=na && a[k]==a[i]; i++);

    for(l=j; j<=nb && b[l]==b[j]; j++);

    add(pria+i-k,prib+j-l);

    pria+=i-k;

    prib+=j-l;

    swap(pria,prib);

  }

  print();

  

  return 0;

}
                       