#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=150010,M=100100;
int n,m,Tree[N],Max[N],rev[N],fa[N],son[N][2],Stack[N];
struct node{int u,v,a,b;}Edge[M];
bool cmp(node a,node b) { return a.a<b.a;}
bool isRoot(int x) { return (son[fa[x]][0]!=x)&&(son[fa[x]][1]!=x);}
void update(int x)
{
	Max[x]=x;
	if (Tree[Max[son[x][0]]]>Tree[Max[x]]) Max[x]=Max[son[x][0]];
	if (Tree[Max[son[x][1]]]>Tree[Max[x]]) Max[x]=Max[son[x][1]];
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
		son[x][1]=i;
		update(x);
	}
}
void MakeRoot(int x)
{
	access(x);
	splay(x);
	rev[x]^=1;
}
int compuse(int x,int y)
{
	MakeRoot(x);
	access(y);
	splay(y);
	return y;
}
int GetRoot(int x)
{
	access(x);
	splay(x);
	while (son[x][0]) x=son[x][0];
	return x;
}
void link(int x,int y)
{
	MakeRoot(x);
	fa[x]=y;
}
void cut(int x,int y)
{
	MakeRoot(x);
	access(y);
	splay(y);
	son[y][0]=fa[x]=0;
	update(y);
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) Max[i]=i,Tree[i]=0;
	for (int i=1;i<=m;i++) scanf("%d%d%d%d",&Edge[i].u,&Edge[i].v,&Edge[i].a,&Edge[i].b);
	sort(Edge+1,Edge+m+1,cmp);
	int ans=1<<29;
	for (int i=1;i<=m;i++)
	{
		int u=Edge[i].u,v=Edge[i].v;
		Tree[n+i]=Edge[i].b;Max[n+i]=n+i;
		if (GetRoot(u)==GetRoot(v))
		{
			int id=compuse(u,v);
			if (Tree[Max[id]]>Tree[n+i])
			{
				int j=Max[id]-n;
				cut(Edge[j].u,j+n);cut(j+n,Edge[j].v);
				link(u,n+i);link(v,n+i);
			}
		}else link(u,n+i),link(v,n+i);
		if (GetRoot(1)==GetRoot(n))
		{
			int id=compuse(1,n);
			ans=min(ans,Edge[i].a+Tree[Max[id]]);
		}
	}
	if (ans==1<<29) puts("-1");
		else printf("%d\n",ans);
	return 0;
}
