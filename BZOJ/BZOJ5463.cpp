#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#define ll long long
using namespace std;
const int N=100010,M=200010;
int n,m,tot,Next[M*2],head[N],tree[M*2],size[N],dfn[N],low[N],Stack[N],top,cnt,num,A[N+M],number[N],ID[N+M],vis[N+M];
vector<int>E[N+M];
ll ans=0;
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void Tarjan(int u,int X)
{
	dfn[u]=low[u]=++cnt;
	Stack[++top]=u;
	number[X]++;
	ID[u]=X;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (!dfn[v])
		{
			Tarjan(v,X);
			low[u]=min(low[u],low[v]);
			if (low[v]>=dfn[u])
			{
				ID[++num]=X;
				E[num].push_back(u);
				E[u].push_back(num);
				int i;
				do
				{
					i=Stack[top--];
					E[num].push_back(i);
					E[i].push_back(num);
				}while (i!=v);
			}
		}else low[u]=min(low[u],dfn[v]);
	}
}
void dfs(int u,int fa)
{
	size[u]=(u<=n);
	vis[u]=1;
	for (int i=0;i<(int)E[u].size();i++)
	{
		int v=E[u][i];
		if (v==fa) continue;
		dfs(v,u);
		ans+=(ll)A[u]*size[v]*size[u];
		size[u]+=size[v];
	}
	ans+=(ll)A[u]*(number[ID[u]]-size[u])*size[u];
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	num=n;
	for (int i=1;i<=n;i++)
		if (!dfn[i]) Tarjan(i,i);
	for (int i=1;i<=n;i++) A[i]=-1;
	for (int i=n+1;i<=num;i++) A[i]=E[i].size();
	for (int i=1;i<=n;i++)
		if (!vis[i]) dfs(i,0);
	printf("%lld\n",ans<<1);
	return 0;
}
