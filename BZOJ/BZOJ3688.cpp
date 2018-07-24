#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 100007
using namespace std;
int n,K,A[50010];
struct node{int x,y;}a[50010];
void Add(int &x,int y) { x+=y;if (x>=mo) x-=mo;}
struct SegmentTree
{
	int Tree[200010];
	void add(int l,int r,int id,int x,int y)
	{
		if (l>x||r<x) return;
		if (l==r&&l==x) { Add(Tree[id],y);return;}
		int mid=(l+r)>>1;
		add(l,mid,id<<1,x,y);
		add(mid+1,r,id<<1|1,x,y);
		Tree[id]=(Tree[id<<1]+Tree[id<<1|1])%mo;
	}
	int query(int l,int r,int id,int x,int y)
	{
		if (l>y||r<x) return 0;
		if (x<=l&&r<=y) return Tree[id];
		int mid=(l+r)>>1;
		return (query(l,mid,id<<1,x,y)+query(mid+1,r,id<<1|1,x,y))%mo;
	}
}TREE[22];
bool cmp(node a,node b) { return a.x<b.x;}
int main()
{
	scanf("%d%d",&n,&K);
	int tot=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		A[++tot]=a[i].y;
	}
	sort(a+1,a+n+1,cmp);
	sort(A+1,A+tot+1);
	tot=unique(A+1,A+tot+1)-A-1;
	for (int i=1;i<=n;i++) a[i].y=lower_bound(A+1,A+tot+1,a[i].y)-A;
	for (int i=1;i<=n;i++)
	{
		TREE[0].add(1,tot,1,a[i].y,1);
		TREE[K+1].add(1,tot,1,a[i].y,1);
		for (int j=1;j<=K;j++)
		{
			int x=0,y=0;
			x=TREE[j].query(1,tot,1,1,a[i].y-1);
			y=TREE[j+K].query(1,tot,1,1,a[i].y-1);
			TREE[j].add(1,tot,1,a[i].y,x+y);
			x=0;y=0;
			x=TREE[j+K+1].query(1,tot,1,a[i].y+1,tot);
			y=TREE[j-1].query(1,tot,1,a[i].y+1,tot);
			TREE[j+K+1].add(1,tot,1,a[i].y,x+y);
		}
	}
	printf("%d\n",(TREE[K].Tree[1]+TREE[K+K+1].Tree[1])%mo);
	return 0;
}
