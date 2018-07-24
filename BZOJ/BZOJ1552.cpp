#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,root,Stack[100100];
struct node{int x,id;}a[100100];
struct SPLAY
{
	int size[100100],Min[100100],Min_ID[100100],Tree[100100],fa[100100],son[100100][2],rev[100100];
	void update(int x)
	{
		size[x]=size[son[x][0]]+size[son[x][1]]+1;
		Min[x]=Tree[x];Min_ID[x]=x;
		if (son[x][0]&&Min[son[x][0]]<Min[x]) Min[x]=Min[son[x][0]],Min_ID[x]=Min_ID[son[x][0]];
		if (son[x][1]&&Min[son[x][1]]<Min[x]) Min[x]=Min[son[x][1]],Min_ID[x]=Min_ID[son[x][1]];
	}
	void pushdown(int x)
	{
		if (rev[x])
		{
			if (son[x][0]) rev[son[x][0]]^=1;
			if (son[x][1]) rev[son[x][1]]^=1;
			swap(son[x][0],son[x][1]);
			rev[x]=0;
		}
	}
	void Rotate(int x,int &k)
	{
		int y=fa[x],z=fa[y],l,r;
		if (son[y][0]==x) l=0;else l=1;
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
		int top=0;Stack[++top]=x;
		for (int i=x;fa[i];i=fa[i]) Stack[++top]=fa[i];
		for (int i=top;i;i--) pushdown(Stack[i]);
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
			Tree[l]=a[l].x;
			Min[l]=Tree[l];
			Min_ID[l]=l;
			size[l]=1;
			fa[l]=father;
			son[father][l>=father]=l;
			rev[l]=0;
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid-1,mid);
		build(mid+1,r,mid);
		Tree[mid]=a[mid].x;
		Min[mid]=Tree[mid];
		Min_ID[mid]=mid;
		size[mid]=1;
		fa[mid]=father;
		son[father][mid>=father]=mid;
		rev[mid]=0;
		update(mid);
	}
	int find(int x)
	{
		int i=root;
		while (i)
		{
			pushdown(i);
			if (size[son[i][0]]+1==x) return i;
			if (size[son[i][0]]>=x) i=son[i][0];
				else x-=size[son[i][0]]+1,i=son[i][1];
		}
	}
	int split(int x,int y)
	{
		x=find(x-1),y=find(y+1);
		splay(x,root);
		splay(y,son[x][1]);
		return son[y][0];
	}
	int GetMin_ID(int x,int y)
	{
		int id=split(x,y);
		return Min_ID[id];
	}
	void Reverse(int x,int y)
	{
		int id=split(x,y);
		rev[id]^=1;
	}
}Splay;
bool cmp(node a,node b) { return (a.x==b.x)?a.id<b.id:a.x<b.x;}
bool Cmp(node a,node b) { return a.id<b.id;}
int main()
{
	scanf("%d",&n);
	a[1].x=1<<29;a[n+2].x=1<<29;
	for (int i=2;i<=n+1;i++) scanf("%d",&a[i].x),a[i].id=i;
	sort(a+2,a+n+2,cmp);
	for (int i=2;i<=n+1;i++) a[i].x=i-1;
	sort(a+2,a+n+2,Cmp);
	Splay.build(1,n+2,0);
	root=(n+3)>>1;
	for (int i=1;i<=n;i++)
	{
		int id=Splay.GetMin_ID(i+1,n+1);
		Splay.splay(id,root);
		printf("%d%c",Splay.size[Splay.son[id][0]]," \n"[i==n]);
		Splay.Reverse(i+1,Splay.size[Splay.son[id][0]]+1);
	}
	return 0;
}
