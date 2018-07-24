#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=1010,M=21000;
int n,m,k,tot,S,T,Next[M],head[N],tree[M],val[M],Cost[M],From[M],h[N],cur[N],Prev[N],FLOW,dis[N],Queue[N*2];
bool visit[N];
struct node{int x,y,z,d;}a[M];
namespace DINIC
{
	bool bfs()
	{
		int t=0,w=1;
		memset(h,-1,sizeof(h));
		Queue[1]=S;h[S]=0;
		while (t!=w)
		{
			int u=Queue[++t];
			for (int i=head[u];i;i=Next[i])
			if (val[i]!=0)
			{
				int v=tree[i];
				if (h[v]==-1)
				{
					Queue[++w]=v;
					h[v]=h[u]+1;
				}
			}
		}
		return h[T]!=-1;
	}
	int dfs(int u,int low)
	{
		if (u==T) return low;
		int used=0;
		for (int i=cur[u];i;i=Next[i])
		{
			cur[u]=i;
			int v=tree[i];
			if (val[i]>0&&h[v]==h[u]+1)
			{
				int w=dfs(v,min(val[i],low-used));
				val[i]-=w;val[i^1]+=w;
				used+=w;
				if (used==low) return low;
			}
		}
		if (used==0) h[u]=-1;
		return used;
	}
	int dinic()
	{
		int ans=0;
		while (bfs())
		{
			for (int i=1;i<=T;i++) cur[i]=head[i];
			ans+=dfs(S,1<<29);
		}
		return ans;
	}
}
namespace MinCostFlow
{
	void add(int x,int y,int z,int d)
	{
		tot++;
		Next[tot]=head[x];
		head[x]=tot;
		tree[tot]=y;
		val[tot]=z;
		Cost[tot]=d;
		From[tot]=x;
	}
	void add_edge(int x,int y,int z,int d)
	{
		add(x,y,z,d);
		add(y,x,0,-d);
	}
	bool spfa()
	{
		memset(visit,0,sizeof(visit));
		memset(Prev,0,sizeof(Prev));
		for (int i=1;i<=T;i++) dis[i]=1<<29;
		int t=0,w=1;
		Queue[1]=S;visit[S]=1;
		dis[S]=0;
		while (t!=w)
		{
			t++;
			if (t>T*2) t=1;
			int u=Queue[t];
			if (u==T) continue;
			visit[u]=0;
			for (int i=head[u];i;i=Next[i])
			if (val[i]>0)
			{
				int v=tree[i];
				if (dis[v]>dis[u]+Cost[i])
				{
					dis[v]=dis[u]+Cost[i];
					Prev[v]=i;
					if (!visit[v])
					{
						w++;
						if (w>T*2) w=1;
						Queue[w]=v;
						visit[v]=1;
					}
				}
			}
		}
		return Prev[T]!=0;
	}
	int GetAns()
	{
		int Flow=1<<29,ans=0;
		for (int i=T;Prev[i];i=From[Prev[i]]) Flow=min(val[Prev[i]],Flow);
		FLOW+=Flow;
		for (int i=T;Prev[i];i=From[Prev[i]])
		{
			ans+=Cost[Prev[i]]*Flow;
			val[Prev[i]]-=Flow;
			val[Prev[i]^1]+=Flow;
		}
		return ans;
	}
	int mcf()
	{
		int ans=0;FLOW=0;
		while (spfa()) ans+=GetAns();
		return ans;
	}
}
int main()
{
	using namespace DINIC;
	using namespace MinCostFlow;
	scanf("%d%d%d",&n,&m,&k);
	tot=1;
	S=1;T=n;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&a[i].x,&a[i].y,&a[i].z,&a[i].d);
		add_edge(a[i].x,a[i].y,a[i].z,0);
	}
	int ans=dinic();
	printf("%d ",ans);
	for (int i=1;i<=m;i++) add_edge(a[i].x,a[i].y,1<<29,a[i].d);
	T++;
	add_edge(n,T,k,0);
	printf("%d\n",mcf());
	return 0;
}
