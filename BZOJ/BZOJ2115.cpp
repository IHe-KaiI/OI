#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,tot,Next[200100],head[50100],tree[200100],cnt;
bool vis[200100];
long long val[200100],f[50100],A[200100],b[65];
void add(int x,int y,long long z)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
	val[tot]=z;
}
void dfs(int u)
{
	vis[u]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (vis[v]) A[++cnt]=f[u]^f[v]^val[i];
			else f[v]=f[u]^val[i],dfs(v);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int x,y;long long z;
		scanf("%d%d%lld",&x,&y,&z);
		add(x,y,z);add(y,x,z);
	}
	dfs(1);
	for (int i=1;i<=cnt;i++)
	{
		for (int j=62;j>=0;j--)
		if (A[i]&(1LL<<j))
		{
			if (!b[j]) { b[j]=A[i];break;}
				else A[i]^=b[j];
		}
	}
	long long ans=f[n];
	for (int i=62;i>=0;i--)
		if (b[i]&&!(ans&(1LL<<i))) ans^=b[i];
	printf("%lld\n",ans);
	return 0;
}
