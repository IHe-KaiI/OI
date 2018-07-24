#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,K,tot,Next[205],head[105],tree[205],f[105][105][2];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs(int u,int fa)
{
	f[u][0][0]=f[u][0][1]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa) continue;
		dfs(v,u);
		for (int j=K;j>=0;j--)
			for (int k=K-j-1;k>=0;k--)
			{
				if (j+k+2<=K)
				{
					f[u][j+k+2][0]=max(f[u][j+k+2][0],f[u][j][0]+f[v][k][0]);
					f[u][j+k+2][1]=max(f[u][j+k+2][1],f[u][j][1]+f[v][k][0]);
				}
				f[u][j+k+1][1]=max(f[u][j+k+1][1],f[u][j][0]+f[v][k][1]);
			}
	}
}
int main()
{
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		x++;y++;
		add(x,y);add(y,x);
	}
	dfs(1,0);
	int ans=0;
	for (int i=0;i<=K;i++) ans=max(ans,max(f[1][i][0],f[1][i][1]));
	printf("%d\n",ans);
	return 0;
}
