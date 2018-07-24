#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=30010;
int n,a[N],Tree[N],Sum[N],q,son[N][2],fa[N],rev[N],Stack[N];
inline bool isRoot(int x) { return (son[fa[x]][0]!=x)&&(son[fa[x]][1]!=x);}
inline void update(int x)
{
	Sum[x]=Sum[son[x][0]]+Sum[son[x][1]]+Tree[x];
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
void access(int x)
{
	for (int i=0;x;i=x,x=fa[x])
	{
		splay(x);
		son[x][1]=i;
		update(x);
	}
}
inline int GetRoot(int x)
{
	access(x);
	splay(x);
	while (son[x][0]) x=son[x][0];
	return x;
}
inline void MakeRoot(int x)
{
	access(x);
	splay(x);
	rev[x]^=1;
}
inline void link(int x,int y)
{
	MakeRoot(x);
	fa[x]=y;
}
inline int Get_Sum(int x,int y)
{
	MakeRoot(x);
	access(y);
	splay(y);
	return Sum[y];
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),Tree[i]=Sum[i]=a[i];
	scanf("%d",&q);
	while (q--)
	{
		char s[15];int x,y;
		scanf("%s",s);
		if (s[0]=='b')
		{
			scanf("%d%d",&x,&y);
			if (GetRoot(x)!=GetRoot(y))
			{
				link(x,y);
				puts("yes");
			}else puts("no");
		}
		if (s[0]=='p')
		{
			scanf("%d%d",&x,&y);
			splay(x);
			Tree[x]=y;
			update(x);
		}
		if (s[0]=='e')
		{
			scanf("%d%d",&x,&y);
			if (GetRoot(x)==GetRoot(y)) printf("%d\n",Get_Sum(x,y));
				else puts("impossible");
		}
	}
	return 0;
}
