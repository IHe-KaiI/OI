#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=101000;
int n,m,tot,Root,ROOT,cnt,a[N],Next[N<<1],head[N],tree[N<<1],fa[N],dep[N],son[N],size[N],tid[N],NUM[N],top[N],End[N];
int f[N][20],lazy[N*4],Tree[N*4];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs(int u,int father,int depth)
{
	fa[u]=father;dep[u]=depth;son[u]=0;
	int maxsize=0;
	size[u]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==father) continue;
		dfs(v,u,depth+1);
		size[u]+=size[v];
		if (size[v]>maxsize) maxsize=size[v],son[u]=v;
	}
}
void dfs1(int u,int ancestor)
{
	tid[u]=++cnt;NUM[cnt]=u;top[u]=ancestor;
	if (son[u]) dfs1(son[u],ancestor);
	for (int i=head[u];i;i=Next[i]) 
		if (tree[i]!=fa[u]&&tree[i]!=son[u]) dfs1(tree[i],tree[i]);
	End[u]=cnt;
}
void down(int id)
{
	if (lazy[id]!=-1)
	{
		Tree[id<<1]=Tree[id<<1|1]=lazy[id];
		lazy[id<<1]=lazy[id<<1|1]=lazy[id];
		lazy[id]=-1;
	}
}
void up(int id) { Tree[id]=min(Tree[id<<1],Tree[id<<1|1]);}
void build(int l,int r,int id)
{
	lazy[id]=-1;
	if (l==r)
	{
		Tree[id]=a[NUM[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,id<<1);
	build(mid+1,r,id<<1|1);
	up(id);
}
int query(int l,int r,int id,int x,int y)
{
	if (x>y||l>y||r<x) return (1LL<<31)-1;
	if (l!=r) down(id);
	if (x<=l&&r<=y) return Tree[id];
	int mid=(l+r)>>1;
	return min(query(l,mid,id<<1,x,y),query(mid+1,r,id<<1|1,x,y));
}
void change(int l,int r,int id,int x,int y,int d)
{
	if (l>y||r<x) return;
	if (l!=r) down(id);
	if (x<=l&&r<=y) { Tree[id]=d;lazy[id]=d;return;}
	int mid=(l+r)>>1;
	change(l,mid,id<<1,x,y,d);
	change(mid+1,r,id<<1|1,x,y,d);
	up(id);
}
int LCA(int x,int y)
{
	while (top[x]!=top[y])
	{
		if (dep[top[x]]>dep[top[y]]) x=fa[top[x]];
			else y=fa[top[y]];
	}
	return (dep[x]<dep[y])?x:y;
}
void Change(int x,int y,int z)
{
	while (top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		change(1,n,1,tid[top[x]],tid[x],z);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	change(1,n,1,tid[x],tid[y],z);
}
int Query(int x)
{
	if (x==Root) return query(1,n,1,1,n);
	if (Root!=ROOT&&LCA(Root,x)==x)
	{
		int i=Root;
		for (int j=17;j>=0;j--)
			if (dep[f[i][j]]>dep[x]) i=f[i][j];
		return min(query(1,n,1,1,tid[i]-1),query(1,n,1,End[i]+1,n));
	}else return query(1,n,1,tid[x],End[x]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	scanf("%d",&Root);
	ROOT=Root;
	dfs(Root,0,1);
	dfs1(Root,Root);
	for (int i=1;i<=n;i++) f[i][0]=fa[i];
	for (int i=1;i<=18;i++)
		for (int j=1;j<=n;j++) f[j][i]=f[f[j][i-1]][i-1];
	build(1,n,1);
	for (int i=1;i<=m;i++)
	{
		int id,x,y,z;
		scanf("%d",&id);
		switch (id)
		{
			case 1:{ scanf("%d",&x);Root=x;break;}
			case 2:{ scanf("%d%d%d",&x,&y,&z);Change(x,y,z);break;}
			case 3:{ scanf("%d",&x);printf("%d\n",Query(x));break;}
		}
	}
	return 0;
}
