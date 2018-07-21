#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,m,vis[800],size1,size2;
bool p[800][800],f[2000],g[2000];
void dfs(int u,int now)
{
	if (vis[u]!=0)
	{
		if (vis[u]!=now) { puts("-1");exit(0);}
		return;
	}
	if (now==1) size1++;else size2++;
	vis[u]=now;
	for (int i=1;i<=n;i++)
		if (i!=u&&!p[u][i]) dfs(i,-now);
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		p[u][v]=p[v][u]=1;
	}
	f[0]=1;
	for (int i=1;i<=n;i++)
	if (vis[i]==0)
	{
		size1=size2=0;
		dfs(i,1);
		memset(g,0,sizeof(g));
		for (int j=0;j<=n;j++)
		{
			g[j+size1]|=f[j];
			g[j+size2]|=f[j];
		}
		for (int j=0;j<=n;j++) f[j]=g[j];
	}
	int ans=1<<29;
	for (int i=0;i<=n;i++)
		if (f[i]) ans=min(ans,i*(i-1)/2+(n-i)*(n-i-1)/2);
	printf("%d\n",ans);
	return 0;
}
