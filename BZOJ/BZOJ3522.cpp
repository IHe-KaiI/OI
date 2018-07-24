#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
int n,tot,Next[10100],head[5010],tree[10100],Max[5010];
ll f[5010][5010],g[5010][5010],ans;
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs(int u,int fa)
{
	f[u][0]=1;Max[u]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa) continue;
		dfs(v,u);
		Max[u]=max(Max[u],Max[v]+1);
		ans+=g[u][1]*f[v][0];
		for (int d=1;d<=Max[u];d++) ans+=g[v][d]*f[u][d-1]+g[u][d+1]*f[v][d];
		for (int d=Max[u];d>=1;d--)
		{
			g[u][d]+=g[v][d+1]+f[u][d]*f[v][d-1];
			f[u][d]+=f[v][d-1];
		}
	}
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
	dfs(1,0);
	printf("%lld\n",ans);
	return 0;
}
