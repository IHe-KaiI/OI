#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 998244353
using namespace std;
int n,m,tot,cnt,Tree[23000010],son[23000010][2],root[400010];
ll mi(ll x,int y)
{
	ll ans=1;
	while (y)
	{
		if (y&1) ans=ans*x%mo;
		x=x*x%mo;
		y>>=1;
	}
	return ans;
}
inline ll calc(ll x,ll y)
{
	ll ans=(x*y+(1-x)*(1-y))%mo;
	return (ans<0)?ans+mo:ans;
}
int query(int l,int r,int id,int x)
{
	if (!id) return 1;
	if (l==r) return Tree[id];
	int mid=(l+r)>>1;
	if (x<=mid) return calc(Tree[id],query(l,mid,son[id][0],x));
		else return calc(Tree[id],query(mid+1,r,son[id][1],x));
}
int Query(int l,int r,int id,int x,int y)
{
	if (l==r) return query(0,n,root[id],y);
	int mid=(l+r)>>1;
	if (x<=mid) return calc(query(0,n,root[id],y),Query(l,mid,id<<1,x,y));
		else return calc(query(0,n,root[id],y),Query(mid+1,r,id<<1|1,x,y));
}
void change(int l,int r,int &id,int x,int y,ll d)
{
	if (!id) { id=++cnt;Tree[id]=1;}
	if (x<=l&&r<=y) { Tree[id]=calc(Tree[id],d);return;}
	int mid=(l+r)>>1;
	if (x<=mid) change(l,mid,son[id][0],x,y,d);
	if (y>mid) change(mid+1,r,son[id][1],x,y,d);
}
void Change(int l,int r,int id,int x,int y,int X,int Y,ll d)
{
	if (x<=l&&r<=y) { change(0,n,root[id],X,Y,d);return;}
	int mid=(l+r)>>1;
	if (x<=mid) Change(l,mid,id<<1,x,y,X,Y,d);
	if (y>mid) Change(mid+1,r,id<<1|1,x,y,X,Y,d);
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int id,x,y;
		scanf("%d%d%d",&id,&x,&y);
		if (id==1)
		{
			int inv=mi(y-x+1,mo-2);
			if (x!=1) Change(0,n,1,1,x-1,x,y,(1-inv+mo)%mo),Change(0,n,1,0,0,0,x-1,0);
			if (y!=n) Change(0,n,1,x,y,y+1,n,(1-inv+mo)%mo),Change(0,n,1,0,0,y+1,n,0);
			Change(0,n,1,x,y,x,y,(1-inv*2%mo+mo)%mo);Change(0,n,1,0,0,x,y,inv);
		}else
		{
			printf("%d\n",Query(0,n,1,x-1,y));
		}
	}
	return 0;
}
