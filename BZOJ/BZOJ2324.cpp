#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=350,M=90000;
int n,m,K,f[160][160];
namespace MinCostFlow
{
	int tot,S,T,Next[M],head[N],tree[M],val[M],Cost[M],From[M],Prev[N],FLOW,dis[N],Queue[N*2];
	bool visit[N];
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
	using namespace MinCostFlow;
	scanf("%d%d%d",&n,&m,&K);
	n++;
	memset(f,0x3f,sizeof(f));
	for (int i=1;i<=n;i++) f[i][i]=0;
	for (int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		x++;y++;
		f[x][y]=f[y][x]=min(f[x][y],z);
	}
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++)
			for (int j=k;j<=n;j++)
			f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	tot=1;
	S=n*2+1;T=n*2+2;
	add_edge(S,n+1,K,0);
	for (int i=2;i<=n;i++)  add_edge(i,T,1,0),add_edge(S,i+n,1,0);
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++) add_edge(i+n,j,1<<29,f[i][j]);
	printf("%d\n",mcf());
	return 0;
}
