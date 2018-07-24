#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=100010;
int n,m,tot,cnt,Next[N<<1],head[N],tree[N<<1],Fa[N],fa[N],dep[N],size[N],Son[N],tid[N],NUM[N],top[N],Max[N*4],lazy[N*4],son[N][2];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs(int u,int father,int depth)
{
	Fa[u]=fa[u]=father;dep[u]=depth;size[u]=1;Son[u]=0;
	int maxsize=0;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa[u]) continue;
		dfs(v,u,depth+1);
		size[u]+=size[v];
		if (size[v]>maxsize)
		{
			maxsize=size[v];
			Son[u]=v;
		}
	}
}
void dfs1(int u,int ancestor)
{
	tid[u]=++cnt;NUM[cnt]=u;top[u]=ancestor;
	if (Son[u]) dfs1(Son[u],ancestor);
	for (int i=head[u];i;i=Next[i])
		if (tree[i]!=fa[u]&&tree[i]!=Son[u]) dfs1(tree[i],tree[i]);
}
void build(int l,int r,int id)
{
	if (l==r) { Max[id]=dep[NUM[l]];return;}
	int mid=(l+r)>>1;
	build(l,mid,id<<1);
	build(mid+1,r,id<<1|1);
	Max[id]=max(Max[id<<1],Max[id<<1|1]);
}
void down(int id)
{
	if (lazy[id]!=0)
	{
		Max[id<<1]+=lazy[id];
		Max[id<<1|1]+=lazy[id];
		lazy[id<<1]+=lazy[id];
		lazy[id<<1|1]+=lazy[id];
		lazy[id]=0;
	}
}
void change(int l,int r,int id,int x,int y,int d)
{
	if (l>y||r<x) return;
	if (l!=r) down(id);
	if (x<=l&&r<=y)
	{
		Max[id]+=d;
		lazy[id]+=d;
		return;
	}
	int mid=(l+r)>>1;
	change(l,mid,id<<1,x,y,d);
	change(mid+1,r,id<<1|1,x,y,d);
	Max[id]=max(Max[id<<1],Max[id<<1|1]);
}
int query_max(int l,int r,int id,int x,int y)
{
	if (l>y||r<x) return 0;
	if (l!=r) down(id);
	if (x<=l&&r<=y) return Max[id];
	int mid=(l+r)>>1;
	return max(query_max(l,mid,id<<1,x,y),query_max(mid+1,r,id<<1|1,x,y));
}
int query_sum(int l,int r,int id,int x)
{
	if (l>x||r<x) return 0;
	if (l!=r) down(id);
	if (l==r&&l==x) return Max[id];
	int mid=(l+r)>>1;
	return query_sum(l,mid,id<<1,x)+query_sum(mid+1,r,id<<1|1,x);
}
int LCA(int x,int y)
{
	while (top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		x=Fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	return x;
}
int Query(int x)
{
	return query_sum(1,n,1,tid[x]);
}
inline bool isRoot(int x) { return (son[fa[x]][0]!=x)&&(son[fa[x]][1]!=x);}
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
}
inline void splay(int x)
{
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
inline void access(int x)
{
	for (int i=0;x;i=x,x=fa[x])
	{
		splay(x);
		if (son[x][1])
		{
			int id=son[x][1];
			while (son[id][0]) id=son[id][0];
			change(1,n,1,tid[id],tid[id]+size[id]-1,1);
		}
		if (i)
		{
			int id=i;
			while (son[id][0]) id=son[id][0];
			change(1,n,1,tid[id],tid[id]+size[id]-1,-1);
		}
		son[x][1]=i;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	tot=cnt=0;
	for (int i=1;i<=n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0,1);
	dfs1(1,1);
	build(1,n,1);
	while (m--)
	{
		int id,x,y;
		scanf("%d",&id);
		if (id==1) { scanf("%d",&x);access(x);}
		if (id==2) { scanf("%d%d",&x,&y);printf("%d\n",Query(x)+Query(y)-Query(LCA(x,y))*2+1);}
		if (id==3) { scanf("%d",&x);printf("%d\n",query_max(1,n,1,tid[x],tid[x]+size[x]-1));}
	}
	return 0;
}
