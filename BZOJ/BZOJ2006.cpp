#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#define mp make_pair
using namespace std;
const int N=500100;
int n,K,L,R,a[N],sum[N];
pair<int,int>Tree[N<<2];
struct node{int x,L,R,i,S;};
struct cmp
{
	bool operator () (node a,node b) { return a.x<b.x;}
};
priority_queue<node,vector<node>,cmp>Q;
void build(int id,int l,int r)
{
	Tree[id]=mp(-(1<<30),0);
	if (l==r) return;
	int mid=(l+r)>>1;
	build(id<<1,l,mid);
	build(id<<1|1,mid+1,r);
}
void Insert(int id,int l,int r,int x,int y)
{
	if (l==r) { Tree[id]=mp(y,l);return;}
	int mid=(l+r)>>1;
	if (x<=mid) Insert(id<<1,l,mid,x,y);
		else Insert(id<<1|1,mid+1,r,x,y);
	Tree[id]=max(Tree[id<<1],Tree[id<<1|1]);
}
pair<int,int> query(int id,int l,int r,int x,int y)
{
	if (l>y||r<x) return mp(-(1<<30),0);
	if (x<=l&&r<=y) return Tree[id];
	int mid=(l+r)>>1;
	return max(query(id<<1,l,mid,x,y),query(id<<1|1,mid+1,r,x,y));
}
int main()
{
	scanf("%d%d%d%d",&n,&K,&L,&R);
	for (int i=1;i<=n;i++) { scanf("%d",&a[i]);sum[i]=sum[i-1]+a[i];}
	build(1,1,n);
	for (int i=n;i>=1;i--)
	{
		Insert(1,1,n,i,sum[i]);
		if (i+L-1>n) continue;
		pair<int,int>t=query(1,1,n,i+L-1,min(n,i+R-1));
		Q.push((node){t.first-sum[i-1],i+L-1,min(n,i+R-1),t.second,sum[i-1]});
	}
	long long ans=0;
	while (K--)
	{
		node t=Q.top();
		ans+=t.x;
		Q.pop();
		pair<int,int>X=query(1,1,n,t.L,t.i-1);
		pair<int,int>Y=query(1,1,n,t.i+1,t.R);
		Q.push((node){X.first-t.S,t.L,t.i-1,X.second,t.S});
		Q.push((node){Y.first-t.S,t.i+1,t.R,Y.second,t.S});
	}
	printf("%lld\n",ans);
	return 0;
}
