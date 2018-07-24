#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=100100;
int n,m,a[N],Tree[N],size[N],son[N][2],fa[N],Stack[N],rev[N];
inline bool isRoot(int x) { return (son[fa[x]][0]!=x)&&(son[fa[x]][1]!=x);}
inline void update(int x)
{
	size[x]=size[son[x][0]]+size[son[x][1]]+Tree[x];
}
inline void pushdown(int x)
{
	if (rev[x])
	{
		if (son[x][0]) rev[son[x][0]]^=1;
		if (son[x][1]) rev[son[x][1]]^=1;
		swap(son[x][0],son[x][1]);
		rev[x]=0;
	}
}
inline void Rotate(int x)
{
	int y=fa[x],z=fa[y],l,r;
	if (son[y][0]==x) l=0;else l=1;
	r=l^1;
	if (!isRoot(y))
	{
		if (son[z][0]==y) son[z][0]=x;else son[z][1]=x;
	}
	fa[x]=z;fa[y]=x;fa[son[x][r]]=y;
	son[y][l]=son[x][r];son[x][r]=y;
	update(y);update(x);
}
inline void splay(int x)
{
	int top=0;Stack[++top]=x;
	for (int i=x;!isRoot(i);i=fa[i]) Stack[++top]=fa[i];
	for (;top;top--) pushdown(Stack[top]);
	while (!isRoot(x))
	{
		int y=fa[x],z=fa[y];
		if (!isRoot(y))
		{
			if ((son[y][0]==x)^(son[z][0]==y)) Rotate(x);
				else Rotate(y);
		}
		Rotate(x);
	}
}
void access(int x)
{
	for (int i=0;x;i=x,x=fa[x])
	{
		splay(x);
		Tree[x]+=size[son[x][1]]-size[i];
		son[x][1]=i;
		update(x);
	}
}
inline void MakeRoot(int x)
{
	access(x);
	splay(x);
	rev[x]^=1;
}
inline void compuse(int x,int y)
{
	MakeRoot(x);
	access(y);	
	splay(y);
}
inline void link(int x,int y)
{
	MakeRoot(x);
	MakeRoot(y);
	fa[x]=y;
	Tree[y]+=size[x];
	update(y);
}
inline ll query(int x,int y)
{
	compuse(x,y);
	return (ll)size[x]*Tree[y];
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) size[i]=Tree[i]=1;
	while (m--)
	{
		char s[5];int x,y;
		scanf("%s%d%d",s,&x,&y);
		if (s[0]=='A') link(x,y);
			else printf("%lld\n",query(x,y));
	}
	return 0;
}
