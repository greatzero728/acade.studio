#include<stdio.h>
#include<math.h>
#include<vector>
#include<string.h>

int n;
int xs[10],ys[10];
int fx,fy;
double ans,maxLen;

std::vector<int> getInDeltaPoints(int bx,int by,int dx,int dy,int nx,int ny){
	std::vector<int> re;
	int vxs[3],vys[3],dxs[3],dys[3];
	vxs[0]=dx-bx;
	vys[0]=dy-by;
	vxs[1]=nx-dx;
	vys[1]=ny-dy;
	vxs[2]=bx-nx;
	vys[2]=by-ny;
	
	for(int i=0;i<=n;i++){
		int p=0,m=0,zero=0;
		dxs[0]=xs[i]-bx;
		dys[0]=ys[i]-by;
		dxs[1]=xs[i]-dx;
		dys[1]=ys[i]-dy;
		dxs[2]=xs[i]-nx;
		dys[2]=ys[i]-ny;
		for(int j=0;j<3;j++){
			if(dxs[j]==0&&dys[j]==0)continue;
			int g=vxs[j]*dys[j]-dxs[j]*vys[j];
			if(g==0){
				zero++;
			}else if(g<0){
				m++;
			}else{
				p++;
			}
		}
		if(p==3||m==3)re.push_back(i);
		if(zero==1&&(p==2||m==2))re.push_back(i);
	}
	return re;
}

void saiki(int bx,int by,int dx,int dy,int spents[10],double RopeLen,double moveLen);

void saiki2(int bx,int by,int dx,int dy,int gx,int gy,std::vector<int>& perm,int spents[10],double RopeLen,double moveLen){
	if(RopeLen>maxLen)return;
	if(ans!=-1&&ans<moveLen)return ;
	if(getInDeltaPoints(bx,by,dx,dy,gx,gy).empty()==true){
		double lastAdd=sqrt((bx-gx)*(bx-gx)+(by-gy)*(by-gy));
		if(RopeLen+lastAdd>maxLen)return;
		moveLen+=sqrt((dx-gx)*(dx-gx)+(dy-gy)*(dy-gy));
		if(gx==fx&&gy==fy){
			if(ans==-1||ans>moveLen)ans=moveLen;
		}else{
			saiki(bx,by,gx,gy,spents,RopeLen,moveLen);
		}
		return ;
	}
	for(unsigned int i=0;i<perm.size();i++){
		int no=perm[i];
		if(spents[no]==0&&getInDeltaPoints(bx,by,dx,dy,xs[no],ys[no]).empty()==true){
			spents[no]=1;
			double t=sqrt((bx-xs[no])*(bx-xs[no])+(by-ys[no])*(by-ys[no]));
			saiki2(xs[no],ys[no],dx,dy,gx,gy,perm,spents,RopeLen+t,moveLen);
			spents[no]=0;
		}
	}
}

void saiki(int bx,int by,int dx,int dy,int spents[10],double RopeLen,double moveLen){
	std::vector<int> perm=getInDeltaPoints(bx,by,dx,dy,fx,fy);
	saiki2(bx,by,dx,dy,fx,fy,perm,spents,RopeLen,moveLen);
	for(int i=0;i<=n;i++){
		if(spents[i]==0){
			spents[i]=1;
			perm=getInDeltaPoints(bx,by,dx,dy,xs[i],ys[i]);
			saiki2(bx,by,dx,dy,xs[i],ys[i],perm,spents,RopeLen,moveLen);
			spents[i]=0;
		}
	}
}

void calc(){
	int dx,dy;
	scanf("%d %d %d %d",&dx,&dy,&fx,&fy);
	for(int i=0;i<n;i++)scanf("%d %d",&xs[i],&ys[i]);
	xs[n]=0;
	ys[n]=0;
	int spents[10]={0};
	ans=-1;
	maxLen=sqrt(dx*dx+dy*dy);
	saiki(0,0,dx,dy,spents,0,0);
	if(ans==-1){
		printf("-1\n");
	}else{
		printf("%.7lf\n",ans);
	}
}

int main(){
	while(1){
		scanf("%d",&n);
		if(n==0)break;
		calc();
	}
}
