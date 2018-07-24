#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mp make_pair
#define fi first
#define se second
using namespace std;
const int N=400100;
int n,m,son[N][2],fa[N],rev[N],Sum[N],w[N],Tree[N],Stack[N];
pair<int,int>Min[N];
struct node{int u,v;}Edge[300100];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline bool isRoot(int x) { return (son[fa[x]][0]!=x)&&(son[fa[x]][1]!=x);}
inline void update(int x)
{
	int l=son[x][0],r=son[x][1];
	Min[x]=min(Min[l],min(Min[r],mp(Tree[x],x)));
	Sum[x]=Sum[l]+Sum[r]+w[x];
}
inline void pushdown(int x)
{
	if (rev[x])
	{
		if (son[x][0]) rev[son[x][0]]^=1;
		if (son[x][1]) rev[son[x][1]]^=1;
		swap(son[x][0],son[x][1]);
		rev[x]^=1;
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
			if ((son[y][0]==x)^(son[z][0]==y)) Rotate(x);
				else Rotate(y);
		}
		Rotate(x);
	}
}
inline void access(int x)
{
	for (int i=0;x;i=x,x=fa[x])
	{
		splay(x);
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
inline int GetRoot(int x)
{
	access(x);
	splay(x);
	while (son[x][0]) x=son[x][0];
	return x;
}
inline int compuse(int x,int y)
{
	MakeRoot(x);
	access(y);
	splay(y);
	return y;
}
inline void link(int x,int y)
{
	MakeRoot(x);
	fa[x]=y;
}
inline void cut(int x,int y)
{
	MakeRoot(x);
	access(y);
	splay(y);
	fa[x]=son[y][0]=0;
	update(y);
}
int main()
{
	scanf("%d%d",&n,&m);
	Min[0]=mp(1<<29,0);
	for (int i=1;i<=n;i++) Tree[i]=1<<29,Min[i]=mp(1<<29,i),Sum[i]=w[i]=0;
	while (m--)
	{
		char s[10];
		scanf("%s",s);
		switch (s[0])
		{
			case 'f':
			{
				int id=read()+n+1,u=read()+1,v=read()+1,t=read(),l=read();
				Edge[id]=(node){u,v};
				Tree[id]=t;Min[id]=mp(t,id);Sum[id]=w[id]=l;
				if (GetRoot(u)==GetRoot(v))
				{
					int ID=compuse(u,v);
					if (Min[ID].fi<t)
					{
						int j=Min[ID].se;
						cut(Edge[j].u,j);cut(j,Edge[j].v);
						link(u,id);link(id,v);
					}
				}else link(u,id),link(id,v);
				break;
			}
			case 'm':
			{
				int x=read()+1,y=read()+1;
				if (GetRoot(x)!=GetRoot(y)) { puts("-1");break;}
				int id=compuse(x,y);
				printf("%d\n",Sum[id]);
				break;
			}
			case 'c':
			{
				int id=read()+n+1,l=read();
				splay(id);
				w[id]=l;
				update(id);
				break;
			}
		}
	}
	return 0;
}
