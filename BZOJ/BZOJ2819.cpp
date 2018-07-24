#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,a[500100],tot,cnt,Next[1000100],head[500100],tree[1000100],k,F[500100],G[500100],f[1000100],fa[500100][20],dep[500100];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs(int u,int father,int depth)
{
	F[u]=++cnt;fa[u][0]=father;dep[u]=depth;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==father) continue;
		dfs(v,u,depth+1);
	}
	G[u]=++cnt;
}
inline int lowbit(int x) { return x&(-x);}
void Add(int x,int y) { for (int i=x;i<=cnt;i+=lowbit(i)) f[i]^=y;}
int get(int x)
{
	int ans=0;
	for (int i=x;i>=1;i-=lowbit(i)) ans^=f[i];
	return ans;
}
int lca(int x,int y)
{
	if (dep[x]<dep[y]) swap(x,y);
	int z=dep[x]-dep[y];
	for (int i=19;z>0&&i>=0;i--)
		if ((1<<i)<=z) z-=1<<i,x=fa[x][i];
	if (x==y) return x;
	for (int i=19;i>=0;i--)
		if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	tot=cnt=0;
	for (int i=1;i<=n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0,1);
	for (int i=1;i<=19;i++)
		for (int j=1;j<=n;j++) fa[j][i]=fa[fa[j][i-1]][i-1];
	for (int i=1;i<=n;i++) Add(F[i],a[i]),Add(G[i],a[i]);
	scanf("%d",&k);
	while (k--)
	{
		char s[5];
		int x,y;
		scanf("%s%d%d",s,&x,&y);
		if (s[0]=='Q')
		{
			if (get(F[x])^get(F[y])^a[lca(x,y)]) puts("Yes");
				else puts("No");
		}else
		{
			Add(F[x],a[x]);
			Add(F[x],y);
			Add(G[x],a[x]);
			Add(G[x],y);
			a[x]=y;
		}
	}
	return 0;
}
