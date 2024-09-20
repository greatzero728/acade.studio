//program 97-A

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

int P(char c)
{
  if(c>='a'&&c<='z')return c-97;
  if(c=='A')return 26;
  if(c=='B')return 27;
  if(c=='.')return -1;
  return -2;
}

int Get()
{
  char c;while(c=getchar(),P(c)==-2);
  return P(c);
}

int R,C,Ans;
int Map[30][30];
int X[14],Y[14],S[14];
int K[28],Color[28][2];
int Used[100];
char Solution[30][30];

int Calc(int T)
{
  int X=Color[T][0],Y=Color[T][1];
  if(X>Y)swap(X,Y);
  return X*10+Y;
}

void Save()
{
  for(int i=0;i<R;i++)
    for(int j=0;j<C;j++)
      Solution[i][j]='.';
  for(int i=0;i<14;i++)
    for(int j=0;j<4;j++)
      Solution[X[i]+(j>>1)][Y[i]+(j&1)]=S[i]+48;
}

void DFS(int Depth)
{
  int All=Depth?6:0;
  if(Depth==14)
    {Ans++;if(Ans==1)Save();return;}
  for(int i=0;i<=All;i++)
    {
      bool OK=true;
      for(int j=0;j<4;j++)
        {
          int T=Map[X[Depth]+(j>>1)][Y[Depth]+(j&1)];
          Color[T][K[T]++]=i;
          if(K[T]==2)
            {
              int Num=Calc(T);
              if(Used[Num])OK=false;
              Used[Num]++;
            }
        }
      S[Depth]=i;if(OK)DFS(Depth+1);
      for(int j=0;j<4;j++)
        {
          int T=Map[X[Depth]+(j>>1)][Y[Depth]+(j&1)];
          if(K[T]==2)Used[Calc(T)]--;K[T]--;
        }
    }
}

int main()
{
  scanf("%d%d",&R,&C);
  for(int i=0;i<R;i++)
    for(int j=0;j<C;j++)
      Map[i][j]=Get();
  static bool Flag[30][30];
  memset(Flag,0,sizeof(Flag));
  int M=0;
  for(int i=0;i<R;i++)
    for(int j=0;j<C;j++)
      if(Map[i][j]!=-1&&!Flag[i][j])
        {
          Flag[i][j]=true;
          Flag[i][j+1]=true;
          Flag[i+1][j]=true;
          Flag[i+1][j+1]=true;
          X[M]=i;Y[M]=j;M++;
        }
  memset(K,0,sizeof(K));
  memset(Used,0,sizeof(Used));
  Ans=0;DFS(0);printf("%d\n",Ans*7);
  for(int i=0;i<R;i++)
    {
      for(int j=0;j<C;j++)
        putchar(Solution[i][j]);
      putchar('\n');
    }
  return 0;
}
