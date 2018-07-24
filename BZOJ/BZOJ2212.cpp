#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
int n,Root,cnt,tot,a[400100],son[400100][2],Tree[4000100],ls[4000100],rs[4000100],root[400100];
ll ans,num1,num2;
void Insert(int l,int r,int &id,int x)
{
	if (!id) id=++tot;
	if (l==r) { Tree[id]=1;return;}
	int mid=(l+r)>>1;
	if (x<=mid) Insert(l,mid,ls[id],x);
		else Insert(mid+1,r,rs[id],x);
	Tree[id]=Tree[ls[id]]+Tree[rs[id]];
}
void READ(int &id)
{
	if (!id) id=++cnt;
	scanf("%d",&a[id]);
	if (!a[id])
	{
		READ(son[id][0]);
		READ(son[id][1]);
	}else Insert(1,n,root[id],a[id]);
}
int merge(int x,int y)
{
	if (!x) return y;
	if (!y) return x;
	num1+=(ll)Tree[ls[x]]*Tree[rs[y]];
	num2+=(ll)Tree[rs[x]]*Tree[ls[y]];
	ls[x]=merge(ls[x],ls[y]);
	rs[x]=merge(rs[x],rs[y]);
	Tree[x]=Tree[ls[x]]+Tree[rs[x]];
	return x;
}
void solve(int id)
{
	if (!id) return;
	solve(son[id][0]);solve(son[id][1]);
	if (!a[id])
	{
		num1=num2=0;
		root[id]=merge(root[son[id][0]],root[son[id][1]]);
		ans+=min(num1,num2);
	}
}
int main()
{
	scanf("%d",&n);
	READ(Root);
	ans=0;
	solve(Root);
	printf("%lld\n",ans);
	return 0;
}
