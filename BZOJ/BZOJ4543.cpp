#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=100005;
int n,tot,Next[N<<1],head[N],tree[N<<1],son[N],top[N],d[N],cnt;
ll *f[N],*g[N],F[N*5],G[N*5],ans;
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs1(int u,int fa)
{
	d[u]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa) continue;
		dfs1(v,u);
		if (d[v]+1>d[u]) d[u]=d[v]+1,son[u]=v;
	}
}
void dfs2(int u,int ancestor,int fa)
{
	top[u]=ancestor;
	if (son[u]) dfs2(son[u],ancestor,u);
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa||v==son[u]) continue;
		dfs2(v,v,u);
	}
}
void dfs(int u,int fa)
{
	for (int i=head[u];i;i=Next[i])
		if (tree[i]!=fa) dfs(tree[i],u);
	if (son[u])
	{
		g[u]=g[son[u]]+1;
		f[u]=f[son[u]]-1;
	}else
	{
		f[u]=F+cnt+d[top[u]]-1;
		g[u]=G+cnt;
		cnt+=d[top[u]]<<1;
	}
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa||v==son[u]) continue;
		ans+=g[u][1]*f[v][0];
		for (int j=1;j<d[v];j++) ans+=g[v][j]*f[u][j-1]+g[u][j+1]*f[v][j];
		for (int j=d[v];j>=1;j--)
		{
			if (j<d[v]-1) g[u][j]+=g[v][j+1];
			g[u][j]+=f[u][j]*f[v][j-1];
			f[u][j]+=f[v][j-1];
		}
		g[u][0]+=g[v][1];
	}
	f[u][0]++;ans+=g[u][0];
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	ans=0;
	dfs1(1,0);
	dfs2(1,1,0);
	dfs(1,0);
	printf("%lld\n",ans);
	return 0;
}
