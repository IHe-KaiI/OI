#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;
int n,m,a[2000100],tot,Next[2000100],head[2000100],tree[2000100],ans,sum[2000100],delta[2000100];
vector<int>E[2000100];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
bool cmp(int a,int b) { return delta[a]<delta[b];}
void dfs(int u)
{
	sum[u]=a[u];
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		dfs(v);
		sum[u]++;
	}
	sort(E[u].begin(),E[u].end(),cmp);
	for (int i=0;i<E[u].size();i++)
	{
		int t=E[u][i];
		if (delta[t]+sum[u]>m) break;
		sum[u]+=delta[t];
		ans++;
	}
	delta[u]=sum[u]-1;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d",&x);
		for (int j=1;j<=x;j++)
		{
			scanf("%d",&y);
			y++;
			add(i,y);
			E[i].push_back(y);
		}
	}
	dfs(1);
	printf("%d\n",ans);
	return 0;
}
