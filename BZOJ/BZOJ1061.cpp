#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=1050,M=40010;
int n,m,tot,a[N],S,T,Next[M],head[N],tree[M],val[M],From[M],Cost[M],Prev[N],dis[N],Q[N*2];
bool visit[N];
void add(int x,int y,int z,int cost)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
	val[tot]=z;
	From[tot]=x;
	Cost[tot]=cost;
}
void add_edge(int x,int y,int z,int cost)
{
	add(x,y,z,cost);
	add(y,x,0,-cost);
}
bool spfa()
{
	memset(visit,0,sizeof(visit));
	memset(Prev,0,sizeof(Prev));
	for (int i=1;i<=T;i++) dis[i]=1<<29;
	int t=0,w=1;
	Q[1]=S;dis[S]=0;visit[S]=1;
	while (t!=w)
	{
		t++;
		if (t>T*2) t=1;
		int u=Q[t];
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
					Q[w]=v;
					visit[v]=1;
				}
			}
		}
	}
	return Prev[T]!=0;
}
int Get_Ans()
{
	int Flow=1<<29,ans=0;
	for (int i=T;Prev[i];i=From[Prev[i]]) Flow=min(Flow,val[Prev[i]]);
	for (int i=T;Prev[i];i=From[Prev[i]])
	{
		ans+=Cost[Prev[i]]*Flow;
		val[Prev[i]]-=Flow;
		val[Prev[i]^1]+=Flow;
	}
	return ans;
}
int MinCostFlow()
{
	int ans=0;
	while (spfa()) ans+=Get_Ans();
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	tot=1;S=n+2;T=n+3;
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n+1;i++)
	{
		int x=a[i]-a[i-1];
		if (x>=0) add_edge(i,T,x,0);
			else add_edge(S,i,-x,0);
		if (i!=n+1) add_edge(i,i+1,1<<29,0);
	}
	for (int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add_edge(y+1,x,1<<29,z);
	}
	printf("%d\n",MinCostFlow());
	return 0;
}
