#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define INF 1000000000
#define ll long long
using namespace std;
int n,cnt,root,son[1600010][2];
ll lazy[1600010];
void change(int l,int r,int &id,int x,int y,int z)
{
	if (l>y||r<x) return;
	if (!id) id=++cnt;
	if (x<=l&&r<=y)
	{
		lazy[id]=max(lazy[id],(ll)z);
		return;
	}
	int mid=(l+r)>>1;
	change(l,mid,son[id][0],x,y,z);
	change(mid+1,r,son[id][1],x,y,z);
}
ll query(int l,int r,int id)
{
	if (!id) return 0;
	if (l==r) { return lazy[id]*(r-l+1);}
	int mid=(l+r)>>1;
	ll ans=lazy[id]*(r-l+1);
	if (son[id][0])
	{
		lazy[son[id][0]]=max(lazy[son[id][0]],lazy[id]);
		ll X=query(l,mid,son[id][0]);
		ans+=X-lazy[id]*(mid-l+1);
	}
	if (son[id][1])
	{
		lazy[son[id][1]]=max(lazy[son[id][1]],lazy[id]);
		ll X=query(mid+1,r,son[id][1]);
		ans+=X-lazy[id]*(r-mid);
	}
	return ans;
}
int main()
{
	scanf("%d",&n);
	cnt=0;
	for (int i=1;i<=n;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		if (x>=y) continue;
		change(1,INF,root,x,y-1,z);
	}
	printf("%lld\n",query(1,INF,root));
	return 0;
}
