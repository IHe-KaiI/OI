#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,lim,m,tot=0,sum[8000010],root[300100],son[8000010][2];
void add(int l,int r,int X,int x,int &y)
{
	y=++tot;
	sum[y]=sum[x]+1;
	if (l==r) return;
	son[y][0]=son[x][0];son[y][1]=son[x][1];
	int mid=(l+r)>>1;
	if (X<=mid) add(l,mid,X,son[x][0],son[y][0]);
		else add(mid+1,r,X,son[x][1],son[y][1]);
}
int query(int X,int Y)
{
	int l=1,r=lim,x=root[X-1],y=root[Y],tmp=(Y-X+1)>>1;
	while (l<r)
	{
		if (sum[y]-sum[x]<=tmp) return 0;
		int mid=(l+r)>>1;
		if (sum[son[y][0]]-sum[son[x][0]]>tmp) r=mid,y=son[y][0],x=son[x][0];
			else if (sum[son[y][1]]-sum[son[x][1]]>tmp) l=mid+1,y=son[y][1],x=son[x][1];
				else return 0;
	}
	return l;
}
int main()
{
	scanf("%d%d",&n,&lim);
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		add(1,lim,x,root[i-1],root[i]);
	}
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		int ans=query(x,y);
		if (ans) printf("yes %d\n",ans);else puts("no");
	}
	return 0;
}

