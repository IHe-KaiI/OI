#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=300000,M=3000000;
int n;
namespace DINIC
{
	int S,T,tot=1,Next[M],head[N],tree[M],val[M],Queue[N],h[N],cur[N];
	void add(int x,int y,int z)
	{
		tot++;
		Next[tot]=head[x];
		head[x]=tot;
		tree[tot]=y;
		val[tot]=z;
	}
	void add_edge(int x,int y,int z)
	{
		add(x,y,z);
		add(y,x,0);
	}
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
	int dfs(int u,ll low)
	{
		if (u==T) return low;
		int used=0;
		for (int i=cur[u];i;i=Next[i])
		{
			cur[u]=i;
			int v=tree[i];
			if (val[i]>0&&h[v]==h[u]+1)
			{
				ll w=dfs(v,min((ll)val[i],low-used));
				val[i]-=w;val[i^1]+=w;
				used+=w;
				if (used==low) return low;
			}
		}
		if (used==0) h[u]=-1;
		return used;
	}
	ll dinic()
	{
		ll ans=0;
		while (bfs())
		{
			for (int i=1;i<=T;i++) cur[i]=head[i];
			ans+=dfs(S,1LL<<50);
		}
		return ans;
	}
}
int main()
{
	using namespace DINIC;
	scanf("%d",&n);
	int cnt=n;
	ll sum=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			int x;
			scanf("%d",&x);
			sum+=x;
			cnt++;
			add_edge(i,cnt,1<<29);
			add_edge(j,cnt,1<<29);
		}
	S=cnt+1;T=cnt+2;
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		add_edge(S,i,x);
	}
	for (int i=n+1;i<=cnt;i++) add_edge(i,T,1<<29);
	printf("%lld\n",sum-dinic());
	return 0;
}
