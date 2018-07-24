#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define eps 1e-6
using namespace std;
const int N=250,M=30000;
int n,m;
struct node{int x,y;}a[N];
namespace MinCostFlow
{
	int S,T,tot,Next[M],head[N],tree[M],val[M],From[M],Queue[N*2],h[N],cur[N],Prev[N];
	bool visit[N];
	double Cost[M],dis[N];
	void add(int x,int y,int z,double l)
	{
		tot++;
		Next[tot]=head[x];
		head[x]=tot;
		tree[tot]=y;
		val[tot]=z;
		Cost[tot]=l;
		From[tot]=x;
	}
	void add_edge(int x,int y,int z,double l)
	{
		add(x,y,z,l);
		add(y,x,0,-l);
	}
	bool spfa()
	{
		int t=0,w=1;
		memset(visit,0,sizeof(visit));
		memset(Prev,0,sizeof(Prev));
		for (int i=1;i<=T;i++) dis[i]=1e9;
		Queue[1]=S;dis[S]=0;visit[S]=1;
		while (t!=w)
		{
			t++;
			if (t>T*2) t=1;
			int u=Queue[t];
			visit[u]=0;
			for (int i=head[u];i;i=Next[i])
			if (val[i]>0)
			{
				int v=tree[i];
				if (dis[v]>dis[u]+Cost[i]+eps)
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
	double GetAns()
	{
		int ans=0x3f3f3f3f;
		for (int i=T;Prev[i];i=From[Prev[i]]) ans=min(val[Prev[i]],ans);
		double Ans=0;
		for (int i=T;Prev[i];i=From[Prev[i]])
		{
			val[Prev[i]]-=ans;
			val[Prev[i]^1]+=ans;
			Ans+=Cost[Prev[i]]*ans;
		}
		return Ans;
	}
	void Mincostflow()
	{
		double ans;
		while (spfa()) ans+=GetAns();
	}
	void Print()
	{
		for (int i=1;i<=n;i++)
		{
			int ans;
			for (int j=head[i];j;j=Next[j])
			if (val[j]==0)
			{
				int v=tree[j];
				if (v!=S) ans=v-n;
			}
			printf("%d\n",ans);
		}
	}
}
double Dis(int x,int y,int X,int Y) { return sqrt((double)((x-X)*(x-X)+(y-Y)*(y-Y)));}
int main()
{
	using namespace MinCostFlow;
	scanf("%d",&n);
	tot=1;
	S=n*2+1;T=n*2+2;
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		add_edge(S,i,1,0);
	}
	for (int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		for (int j=1;j<=n;j++) add_edge(j,n+i,1,Dis(x,y,a[j].x,a[j].y));
		add_edge(n+i,T,1,0);
	}
	Mincostflow();
	Print();
	return 0;
}
