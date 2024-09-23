#include<bits/stdc++.h>
using namespace std;
struct node{
	int l,r,val;
	bool operator <(const node &b)const{
		return val<b.val;
	}
}a[300005];
struct nade{
	int x,y,id;
	bool operator <(const nade &b)const{
		return x<b.x;
	}
}b[600005];
struct Query{
	int x,id;
	bool operator <(const Query &b)const{
		return x<b.x;
	}
}que[300005];
int n,m,q,tot;
int ans[300005];
int num[300005];
set<int> S;
map<int,int> mp[300005];
int opt[300005];
int tree[1200005],mxpos[1200005];
int get(int x,int y){
	if(x>y)swap(x,y);
	return num[x]+num[y]+mp[x][y];
}
void change(int k,int l,int r,int x,int y){
	if(l==r)return tree[k]=y,mxpos[k]=l,void();
	int mid=l+r>>1;
	if(x<=mid)change(k*2,l,mid,x,y);
	else change(k*2+1,mid+1,r,x,y);
	tree[k]=max(tree[k*2],tree[k*2+1]);
	if(tree[k]==tree[k*2])mxpos[k]=mxpos[k*2];
	else mxpos[k]=mxpos[k*2+1];
}
int query(int k,int l,int r,int x,int y){
	if(l>=x&&r<=y)return mxpos[k];
	int mid=l+r>>1,res=0;
	if(x<=mid)res=query(k*2,l,mid,x,y);
	if(y>mid){
		int ans=query(k*2+1,mid+1,r,x,y);
		if(num[ans]>num[res])res=ans;
	}
	return res;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].val);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		b[++tot]=(nade){a[i].l,1,i};
		b[++tot]=(nade){a[i].r,0,i};
	}
	sort(b+1,b+2*n+1);
	b[2*n+1]=(nade){0x7f3f3f3f,1,n+1};
	scanf("%d",&q);
	for(int i=1;i<=q;i++)scanf("%d",&que[i].x),que[i].id=i;
	sort(que+1,que+q+1);
	int sum=0,lst=0,mx=0;
	for(int i=1,j=1;i<=2*n+1;i++){
		int len=b[i].x-lst;lst=b[i].x;
		if(!S.size())sum+=len;
		else if(S.size()==1){
			auto it=S.begin();
			int x=*it;
			num[x]+=len;change(1,1,n,x,num[x]);	
			opt[x]+=len;
			int p=m-a[x].val;
			if(p>=0){
				int val=num[x];
				if(p>=a[1].val){
					int l=1,r=n;
					while(l<r){
						int mid=l+r+1>>1;
						if(a[mid].val<=p)l=mid;
						else r=mid-1;
					}
					int ql=1,qr=l;
					if(x==qr)qr--;
					if(x<qr){
						ql=x+1;
						if(ql<=qr)val=max(val,get(x,query(1,1,n,ql,qr)));
						ql=1,qr=x-1;
					}
					if(ql<=qr)val=max(val,get(x,query(1,1,n,ql,qr)));
				}
				opt[x]=max(opt[x],val);
				mx=max(mx,opt[x]);
			}
		}else if(S.size()==2){
			auto it=S.begin();
			int x=*it;
			it++;int y=*it;
			mp[x][y]+=len;
//			printf("len=%d mpxy=%d numx=%d numy=%d x=%d y=%d\n",len,mp[x][y],num[x],num[y],x,y);
			if(a[x].val+a[y].val<=m){
				opt[x]=max(opt[x],get(x,y));
				opt[y]=max(opt[y],get(x,y));
				mx=max(mx,opt[x]);
			}
		}
		while(j<=q&&mx+sum>=que[j].x)ans[que[j].id]=b[i].x-(mx+sum-que[j].x),j++;
		if(j>q)break;
		if(b[i].y)S.insert(b[i].id);
		else S.erase(b[i].id);
//		printf("i=%d\n",b[i].x);for(auto x:S)printf("%d ",x);puts("");
//		printf("mx=%d sum=%d\n",mx,sum);
	} 
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
	return 0;  
}