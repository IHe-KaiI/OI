#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=5000,M=4000000;
int n,m;
namespace DINIC
{
	int S,T,tot,Next[M],head[N],tree[M],val[M],Queue[N],h[N],cur[N];
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
int main()
{
	using namespace DINIC;
	scanf("%d%d",&n,&m);
	S=n+m+1;T=n+m+2;
	tot=1;
	int sum=0;
	for (int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add_edge(S,i,x);
		sum+=x;
		for (int j=1;j<=y;j++)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			add_edge(i,a+n,b);
		}
	}
	for (int i=1;i<=m;i++)
	{
		int x;
		scanf("%d",&x);
		add_edge(i+n,T,x);
	}
	printf("%d\n",sum-dinic());
	return 0;
}
