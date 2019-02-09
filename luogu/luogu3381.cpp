#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
const int N=5010,M=100010;
using namespace std;
int n,m,S,T;
namespace MCMF
{
	int tot,Next[M],head[N],tree[M],val[M],From[M],cost[M],dis[N],vis[N],q[N*2],h[N],pre[N];
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >Q;
	void add(int x,int y,int z,int c)
	{
		tot++;
		Next[tot]=head[x];
		head[x]=tot;
		tree[tot]=y;
		val[tot]=z;
		From[tot]=x;
		cost[tot]=c;
	}
	void add_edge(int x,int y,int z,int c)
	{
		add(x,y,z,c);
		add(y,x,0,-c);
	}
	void SPFA(int S)
	{
		for (int i=1;i<=n;i++) dis[i]=1<<29,vis[i]=0;
		int t=0,w=1;
		q[1]=S;
		vis[S]=1;
		dis[S]=0;
		while (t!=w)
		{
			t++;
			if (t>n*2) t=1;
			int u=q[t];
			vis[u]=0;
			for (int i=head[u];i;i=Next[i])
			if (val[i]>0)
			{
				int v=tree[i];
				if (dis[v]>dis[u]+cost[i])
				{
					dis[v]=dis[u]+cost[i];
					if (!vis[v])
					{
						w++;
						if (w>n*2) w=1;
						q[w]=v;
						vis[v]=1;
					}
				}
			}
		}
	}
	bool Dijkstra(int S,int T)
	{
		for (int i=1;i<=n;i++) dis[i]=1<<29,vis[i]=0;
		dis[S]=0;
		Q.push(make_pair(0,S));
		while (!Q.empty())
		{
			int u=Q.top().second;
			Q.pop();
			if (vis[u]) continue;
			vis[u]=1;
			for (int i=head[u];i;i=Next[i])
			if (val[i]>0)
			{
				int v=tree[i],len=h[u]-h[v]+cost[i];
				if (dis[v]>dis[u]+len)
				{
					pre[v]=i;
					dis[v]=dis[u]+len;
					Q.push(make_pair(dis[v],v));
				}
			}
		}
		return dis[T]!=1<<29;
	}
	void solve(int S,int T)
	{
		SPFA(S);
		for (int i=1;i<=n;i++) h[i]=dis[i];
		int Ans=0,ans=0;
		while (Dijkstra(S,T))
		{
			int Min=1<<29;
			for (int i=T;i!=S;i=From[pre[i]]) Min=min(Min,val[pre[i]]);
			for (int i=T;i!=S;i=From[pre[i]])
			{
				val[pre[i]]-=Min;
				val[pre[i]^1]+=Min;
			}
			Ans+=Min;
			ans+=(dis[T]+h[T]-h[S])*Min;
			for (int i=1;i<=n;i++) h[i]+=dis[i];
		}
		printf("%d %d\n",Ans,ans);
	}
}
int main()
{
	using namespace MCMF;
	scanf("%d%d%d%d",&n,&m,&S,&T);
	tot=1;
	for (int i=1;i<=m;i++)
	{
		int x,y,z,c;
		scanf("%d%d%d%d",&x,&y,&z,&c);
		add_edge(x,y,z,c);
	}
	solve(S,T);
	return 0;
}
