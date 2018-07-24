#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,m,a[200010],fa[200010],Next[200010],son[200010][2],rev[200010],size[200010],Stack[200010];
bool isRoot(int u)
{
	return son[fa[u]][0]!=u&&son[fa[u]][1]!=u;
}
void update(int x)
{
	size[x]=size[son[x][0]]+size[son[x][1]]+1;
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
void Rotate(int x)
{
	int y=fa[x],z=fa[y],l,r;
	if (x==son[y][0]) l=0;else l=1;
	r=l^1;
	if (!isRoot(y))
	{
		if (son[z][0]==y) son[z][0]=x;else son[z][1]=x;
	}
	fa[x]=z;fa[y]=x;fa[son[x][r]]=y;
	son[y][l]=son[x][r];son[x][r]=y;
	update(y);update(x);
}
void splay(int x)
{
	int top=0;Stack[++top]=x;
	for (int i=x;!isRoot(i);i=fa[i]) Stack[++top]=fa[i];
	for (;top;top--) pushdown(Stack[top]);
	while (!isRoot(x))
	{
		int y=fa[x],z=fa[y];
		if (!isRoot(y))
		{
			if ((son[z][0]==y)^(son[y][0]==x)) Rotate(x);
				else Rotate(y);
		}
		Rotate(x);
	}
}
void access(int u)
{
	for (int i=0;u;i=u,u=fa[u])
	{
		splay(u);
		son[u][1]=i;
		update(u);
	}
}
void MakeRoot(int u)
{
	access(u);
	splay(u);
	rev[u]^=1;
}
void link(int u,int v)
{
	MakeRoot(u);
	fa[u]=v;
}
void cut(int u,int v)
{
	MakeRoot(u);
	access(v);
	splay(v);
	son[v][0]=0;
	fa[u]=0;
	update(v);
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		fa[i]=a[i]+i;size[i]=1;
		if (fa[i]>n+1) fa[i]=n+1;
		Next[i]=fa[i];
	}
	size[n+1]=1;
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		int opt,x,y;
		scanf("%d",&opt);
		if (opt==1)
		{
			scanf("%d",&x);
			x++;
			MakeRoot(n+1);access(x);splay(x);
			printf("%d\n",size[son[x][0]]);
		}else
		{
			scanf("%d%d",&x,&y);
			x++;y+=x;
			if (y>n) y=n+1;
			cut(x,Next[x]);link(x,y);Next[x]=y;
		}
	}
	return 0;
}
