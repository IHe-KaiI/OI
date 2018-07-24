#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=2010,M=15010;
int n,A,B,F,Fa,Fb,a[1010];
namespace MinCostFlow
{
	int tot,S,T,Next[M],head[N],tree[M],val[M],Cost[M],From[M],Prev[N],dis[N],Queue[N*2];
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
		int ans=0;
		while (spfa()) ans+=GetAns();
		return ans;
	}
}
int main()
{
	using namespace MinCostFlow;
	scanf("%d%d%d%d%d%d",&n,&A,&B,&F,&Fa,&Fb);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	tot=1;
	S=n+n+1;T=n+n+2;
	for (int i=1;i<=n;i++) 
	{
		add_edge(S,i,a[i],F);
		add_edge(S,n+i,a[i],0);
		add_edge(i,T,a[i],0);
		if (i+1<=n) add_edge(i,i+1,1<<29,0);
		if (i+A+1<=n) add_edge(n+i,i+A+1,a[i],Fa);
		if (i+B+1<=n) add_edge(n+i,i+B+1,a[i],Fb);
	}
	printf("%d\n",mcf());
	return 0;
}
