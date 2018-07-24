#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define INF 1e18
#define ll long long
using namespace std;
const int N=500100;
int n,m,a[N];
struct LAZY{ll x,y;}lazy[N*4],lazy_Max[N*4];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline LAZY max(LAZY a,LAZY b) { return (LAZY){max(a.x,b.x),max(a.y,b.y)};}
inline LAZY operator + (LAZY a,LAZY b){ return (LAZY){max((ll)-INF,a.x+b.x),max(max((ll)-INF,a.y+b.x),b.y)};}
inline void down(int id)
{
	lazy_Max[id<<1]=max(lazy_Max[id<<1],lazy[id<<1]+lazy_Max[id]);
	lazy_Max[id<<1|1]=max(lazy_Max[id<<1|1],lazy[id<<1|1]+lazy_Max[id]);
	lazy[id<<1]=lazy[id<<1]+lazy[id];
	lazy[id<<1|1]=lazy[id<<1|1]+lazy[id];
	lazy[id]=(LAZY){0,0};
	lazy_Max[id]=(LAZY){0,0};
}
void change(int l,int r,int id,int x,int y,LAZY d)
{
	if (l>y||r<x) return;
	if (l!=r) down(id);
	if (x<=l&&r<=y)
	{
		lazy[id]=lazy[id]+d;
		lazy_Max[id]=max(lazy_Max[id],lazy[id]);
		return;
	}
	int mid=(l+r)>>1;
	change(l,mid,id<<1,x,y,d);
	change(mid+1,r,id<<1|1,x,y,d);
}
ll query(int l,int r,int id,int x,int Q)
{
	if (l>x||r<x) return -INF;
	if (l!=r) down(id);
	if (l==r&&l==x)
	{
		if (Q) return max((ll)a[l]+lazy_Max[id].x,lazy_Max[id].y);
		return max((ll)a[l]+lazy[id].x,lazy[id].y);
	}
	int mid=(l+r)>>1;
	return max(query(l,mid,id<<1,x,Q),query(mid+1,r,id<<1|1,x,Q));
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=m;i++)
	{
		int id,l,r,x;
		scanf("%d",&id);
		switch (id)
		{
			case 1:l=read(),r=read(),x=read();change(1,n,1,l,r,(LAZY){x,0});break;
			case 2:l=read();r=read();x=read();change(1,n,1,l,r,(LAZY){-x,0});break;
			case 3:l=read();r=read();x=read();change(1,n,1,l,r,(LAZY){(ll)-INF,x});break;
			case 4:x=read();printf("%lld\n",query(1,n,1,x,0));break;
			case 5:x=read();printf("%lld\n",query(1,n,1,x,1));break;
		}
	}
	return 0;
}
