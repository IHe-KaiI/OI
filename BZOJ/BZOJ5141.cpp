#include<cstdio>
#include<iostream>
#define mo 1000000007
using namespace std;
int n,k,tot,Next[200100],head[100100],tree[200100],a[100100];
long long f[100100][4];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs(int u,int fa)
{
	if (a[u]) f[u][a[u]]=1;
		else f[u][1]=f[u][2]=f[u][3]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa) continue;
		dfs(v,u);
		if (a[u])
		{
			long long sum=0;
			for (int j=1;j<=3;j++)
				if (j!=a[u]) sum=(sum+f[v][j])%mo;
			f[u][a[u]]=f[u][a[u]]*sum%mo;
		}else
		{
			for (int j=1;j<=3;j++)
			{
				long long sum=0;
				for (int k=1;k<=3;k++)
					if (j!=k) sum=(sum+f[v][k])%mo;
				f[u][j]=(f[u][j]*sum)%mo;
			}
		}
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	for (int i=1;i<=k;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[x]=y;
	}
	dfs(1,0);
	printf("%lld\n",((f[1][1]+f[1][2])%mo+f[1][3])%mo);
	return 0;
}
