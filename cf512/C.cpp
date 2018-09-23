#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 1000000007
using namespace std;
const int N=400010;
int n,Q;
ll a[N],w[N],Tree[N*4],sum[N*4];
void up(int x) { Tree[x]=Tree[x<<1]+Tree[x<<1|1];sum[x]=(sum[x<<1]+sum[x<<1|1])%mo;}
void build(int l,int r,int id)
{
	if (l==r) { Tree[id]=w[l];sum[id]=(ll)(a[l]-l)*w[l]%mo;return;}
	int mid=(l+r)>>1;
	build(l,mid,id<<1);
	build(mid+1,r,id<<1|1);
	up(id);
}
void change(int l,int r,int id,int x,int y)
{
	if (l==r) { Tree[id]=y;sum[id]=(ll)(a[l]-l)*y%mo;return;}
	int mid=(l+r)>>1;
	if (x<=mid) change(l,mid,id<<1,x,y);
		else change(mid+1,r,id<<1|1,x,y);
	up(id);
}
ll query_sum(int l,int r,int id,int x,int y)
{
	if (l>y||r<x||Tree[id]==0) return 0;
	if (x<=l&&r<=y) return Tree[id];
	int mid=(l+r)>>1;
	return query_sum(l,mid,id<<1,x,y)+query_sum(mid+1,r,id<<1|1,x,y);
}
ll query(int l,int r,int id,int x,int y)
{
	if (l>y||r<x) return 0;
	if (x<=l&&r<=y) return sum[id];
	int mid=(l+r)>>1;
	return (query(l,mid,id<<1,x,y)+query(mid+1,r,id<<1|1,x,y))%mo;
}
int erfen(int l,int r)
{
	int L=l;
	ll sum=query_sum(1,n,1,l,r);
	while (l<r)
	{
		int mid=(l+r)>>1;
		if (query_sum(1,n,1,L,mid)*2>=sum) r=mid;
			else l=mid+1;
	}
	return r;
}
int main()
{
	scanf("%d%d",&n,&Q);
	for (int i=1;i<=n;i++) scanf("%I64d",&a[i]);
	for (int i=1;i<=n;i++) scanf("%I64d",&w[i]);
	build(1,n,1);
	while (Q--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if (x<0)
		{
			x=-x;
			change(1,n,1,x,y);
		}else
		{
			int p=erfen(x,y);
			ll cnt1=query_sum(1,n,1,x,p),cnt2=query_sum(1,n,1,p,y);
			ll s1=((ll)(a[p]-p)*cnt1%mo-query(1,n,1,x,p))%mo;
			ll s2=(query(1,n,1,p,y)-(ll)(a[p]-p)*cnt2%mo)%mo;
			printf("%I64d\n",((s1+s2)%mo+mo)%mo);
		}
	}
	return 0;
}

