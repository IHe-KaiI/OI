#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,m,root,a[100100];
struct SPLAY
{
	int Tree[100100],size[100100],fa[100100],son[100100][2],rev[100100];
	void update(int x)
	{
		size[x]=1;
		if (son[x][0]) size[x]+=size[son[x][0]];
		if (son[x][1]) size[x]+=size[son[x][1]];
	}
	void downdate(int x)
	{
		if (rev[x])
		{
			rev[son[x][0]]^=1;
			rev[son[x][1]]^=1;
			swap(son[x][0],son[x][1]);
			rev[x]=0;
		}
	}
	void Rotate(int x,int &k)
	{
		int y=fa[x],z=fa[y],l,r;
		if (x==son[y][0]) l=0;else l=1;
		r=l^1;
		if (y==k) k=x;
		else
		{
			if (son[z][0]==y) son[z][0]=x;else son[z][1]=x;
		}
		fa[x]=z;fa[y]=x;fa[son[x][r]]=y;
		son[y][l]=son[x][r];son[x][r]=y;
		update(y);update(x);
	}
	void splay(int x,int &k)
	{
		while (x!=k)
		{
			int y=fa[x],z=fa[y];
			if (y!=k)
			{
				if ((son[z][0]==y)^(son[y][0]==x)) Rotate(x,k);
					else Rotate(y,k);
			}
			Rotate(x,k);
		}
	}
	void build(int l,int r,int father)
	{
		if (l>r) return;
		if (l==r)
		{
			Tree[l]=a[l];
			size[l]=1;	
			fa[l]=father;
			if (l<father) son[father][0]=l;
				else son[father][1]=l;
			rev[l]=0;
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid-1,mid);
		build(mid+1,r,mid);
		Tree[mid]=a[mid];
		fa[mid]=father;
		size[mid]=1;
		if (mid<father) son[father][0]=mid;
			else son[father][1]=mid;
		rev[mid]=0;
		update(mid);
	}
	int find(int x)
	{
		int i=root;
		while (i)
		{
			downdate(i);
			if (x==size[son[i][0]]+1) return i;
			if (size[son[i][0]]>=x) i=son[i][0];
				else x-=size[son[i][0]]+1,i=son[i][1];
		}
	}
	void Reverse(int x,int y)
	{
		int i=find(x-1),j=find(y+1);
		splay(i,root);
		splay(j,son[root][1]);
		int z=son[j][0];
		rev[z]^=1;
	}

}Splay;
int main()
{
	scanf("%d%d",&n,&m);
	root=0;
	for (int i=2;i<=n+1;i++) a[i]=i-1;
	Splay.build(1,n+2,0);
	root=(n+3)>>1;
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		Splay.Reverse(x+1,y+1);
	}
	for (int i=1;i<=n;i++) printf("%d ",Splay.Tree[Splay.find(i+1)]);
	puts("");
	return 0;
}
