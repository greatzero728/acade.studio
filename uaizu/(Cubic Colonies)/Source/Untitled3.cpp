#include<stdio.h>
#include<algorithm>
#include<vector>
#include<queue>
#include<math.h>
using namespace std;
char in[3][3][4];
int DIV=7;
int gcd(int a,int b){
	while(a){
		b%=a;int c=a;a=b;b=c;
	}return b;
}
const double EPS = 1e-10;
const double INF = 1e+10;
const double PI = acos(-1);
int sig(double r) { return (r < -EPS) ? -1 : (r > +EPS) ? +1 : 0; }
inline double ABS(double a){return max(a,-a);}
struct Pt {
	double x, y,z;
	Pt() {}
	Pt(double x, double y,double z) : x(x), y(y),z(z) {}
	Pt operator+(const Pt &a) const { return Pt(x + a.x, y + a.y,z+a.z); }
	Pt operator-(const Pt &a) const { return Pt(x - a.x, y - a.y,z-a.z); }
//	Pt operator*(const Pt &a) const { return Pt(x * a.x - y * a.y, x * a.y + y * a.x); }
	Pt operator-() const { return Pt(-x, -y,-z); }
	Pt operator*(const double &k) const { return Pt(x * k, y * k,z*k); }
	Pt operator/(const double &k) const { return Pt(x / k, y / k,z/k); }
	double ABS() const { return sqrt(x * x + y * y+z*z); }
	double abs2() const { return x * x + y * y+z*z; }
//	double arg() const { return atan2(y, x); }
	double dot(const Pt &a) const { return x * a.x + y * a.y+z*a.z; }
//	double det(const Pt &a) const { return x * a.y - y * a.x; }
};
double ijk[110000];
int v[110000];
int can[4][4][4];
int canx[4][4][4];
int cany[4][4][4];
int canz[4][4][4];
int canxy[4][4][4];
int canyz[4][4][4];
int canzx[4][4][4];
int rev[110000];
char ss[4];
int main(){
	int a,b,c,d,e,f;
	while(scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f),a+b+c+d+e+f){
		for(int i=0;i<3;i++)for(int j=0;j<3;j++){
			scanf("%s",ss);
			for(int k=0;k<3;k++)in[k][j][i]=ss[k];
		}
		vector<Pt> hb;
		for(int i=0;i<4;i++)for(int j=0;j<4;j++)for(int k=0;k<4;k++){
			can[i][j][k]=canx[i][j][k]=cany[i][j][k]=canz[i][j][k]=0;
			canxy[i][j][k]=canyz[i][j][k]=canzx[i][j][k]=0;
		}
		for(int i=0;i<4;i++)for(int j=0;j<4;j++)for(int k=0;k<4;k++){
			if(i==0||i==3||j==0||j==3||k==0||k==3)can[i][j][k]=2;
			if(j==0||j==3||k==0||k==3)canx[i][j][k]=2;
			if(i==0||i==3||k==0||k==3)cany[i][j][k]=2;
			if(i==0||i==3||j==0||j==3)canz[i][j][k]=2;
			if(k==0||k==3)canxy[i][j][k]=2;
			if(i==0||i==3)canyz[i][j][k]=2;
			if(j==0||j==3)canzx[i][j][k]=2;
		}
		for(int i=0;i<3;i++)for(int j=0;j<3;j++)for(int k=0;k<3;k++){
			int key=0;
			if(in[i][j][k]=='#'){
				key=1;
			}else{
				key=2;
			}
			for(int l=0;l<8;l++){
				can[i+l/4][j+l%4/2][k+l%2]|=key;
			}
			for(int l=0;l<4;l++){
				canx[i][j+l/2][k+l%2]|=key;
				cany[i+l/2][j][k+l%2]|=key;
				canz[i+l/2][j+l%2][k]|=key;
			}
			for(int l=0;l<2;l++){
				canxy[i][j][k+l%2]|=key;
				canyz[i+l%2][j][k]|=key;
				canzx[i][j+l%2][k]|=key;
			}
		}
		/*for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				for(int k=0;k<4;k++)printf("%d ",can[k][j][i]);
				printf("\n");
			}
			printf("\n");
		}*/
		for(int i=0;i<=3;i++){
			for(int j=0;j<=3;j++){
				for(int k=0;k<=3;k++){
					if(can[i][j][k]==3)hb.push_back(Pt((double)i,(double)j,(double)k));
				}
				for(int k=0;k<3;k++){
					for(int l=2;l<=DIV;l++){
						for(int m=1;m<l;m++){
							if(gcd(m,l)!=1)continue;
							if(canz[i][j][k]==3)hb.push_back(Pt((double)i,(double)j,k+(double)m/l));
							if(cany[i][k][j]==3)hb.push_back(Pt((double)i,k+(double)m/l,(double)j));
							if(canx[k][i][j]==3)hb.push_back(Pt(k+(double)m/l,(double)i,(double)j));
						}
					}
				}
			}
		}
		int sz=hb.size();
		for(int i=0;i<sz;i++){
			v[i]=0;
			ijk[i]=99999999;
		}
		Pt start=Pt(a,b,c);
		Pt goal=Pt(d,e,f);
		for(int i=0;i<sz;i++){
			if((hb[i]-start).ABS()<EPS){
				ijk[i]=0;
			}
		}
		for(int i=0;i<sz;i++){
			int at=0;
			double dist=999999999;
			for(int j=0;j<sz;j++){
				if(!v[j]&&dist>ijk[j]){
					dist=ijk[j];at=j;
				}
			}
			v[at]=1;
		//	printf("%f %f %f: %f\n",hb[at].x,hb[at].y,hb[at].z,ijk[at]);
			if((hb[at]-goal).ABS()<EPS){
				printf("%.12f\n",dist);
				int cur=at;
				//while((hb[cur]-start).ABS()>EPS){
				//	cur=rev[cur];
				//	printf("%f %f %f: %f\n",hb[cur].x,hb[cur].y,hb[cur].z,ijk[cur]);
				//}
				break;
			}
			for(int j=0;j<sz;j++){
				if(v[j])continue;
				bool X=false;
				bool Y=false;
				bool Z=false;
				int xx=(int)(min(hb[j].x,hb[at].x)+EPS);
				int yy=(int)(min(hb[j].y,hb[at].y)+EPS);
				int zz=(int)(min(hb[j].z,hb[at].z)+EPS);
				if(ABS(hb[j].x-hb[at].x)<EPS&&ABS(hb[j].x-xx)<EPS)X=true;
				if(ABS(hb[j].y-hb[at].y)<EPS&&ABS(hb[j].y-yy)<EPS)Y=true;
				if(ABS(hb[j].z-hb[at].z)<EPS&&ABS(hb[j].z-zz)<EPS)Z=true;
				if(!X&&!Y&&!Z)continue;
				if(!X&&(int)(min(hb[j].x+1,hb[at].x+1)+EPS)!=(int)(max(hb[at].x+1,hb[j].x+1)-EPS))continue;
				if(!Y&&(int)(min(hb[j].y+1,hb[at].y+1)+EPS)!=(int)(max(hb[at].y+1,hb[j].y+1)-EPS))continue;
				if(!Z&&(int)(min(hb[j].z+1,hb[at].z+1)+EPS)!=(int)(max(hb[at].z+1,hb[j].z+1)-EPS))continue;
				bool can=false;
				bool Xs=false;
				bool Ys=false;
				bool Zs=false;
				if(ABS(hb[j].x-(int)(hb[j].x+EPS))<EPS)Xs=true;
				if(ABS(hb[j].y-(int)(hb[j].y+EPS))<EPS)Ys=true;
				if(ABS(hb[j].z-(int)(hb[j].z+EPS))<EPS)Zs=true;
				if(X&&canyz[xx][yy][zz]==3)can=true;
				if(Y&&canzx[xx][yy][zz]==3)can=true;
				if(Z&&canxy[xx][yy][zz]==3)can=true;
				if(X&&Y&&Xs&&Ys&&canz[xx][yy][zz]==3)can=true;
				if(Z&&Y&&Zs&&Ys&&canx[xx][yy][zz]==3)can=true;
				if(X&&Z&&Xs&&Zs&&cany[xx][yy][zz]==3)can=true;
				if(can){
					double tmp=(hb[j]-hb[at]).ABS();
					if(ijk[j]>tmp+ijk[at]){
						ijk[j]=tmp+ijk[at];
						rev[j]=at;
					}
				}
			}
		}
	}
}
