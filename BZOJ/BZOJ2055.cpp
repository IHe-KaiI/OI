#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=510,M=500010;
int n,m,tot,Next[M],head[N],tree[M],val[M],cost[M],From[M],vis[N],Prev[N],dis[N],Q[N],S,T;
void add(int x,int y,int z,int c)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
	val[tot]=z;
	cost[tot]=c;
	From[tot]=x;
}
void add_edge(int u,int v,int w,int c)
{
	add(u,v,w,c);
	add(v,u,0,-c);
}
bool spfa()
{
	memset(vis,0,sizeof(vis));
	memset(Prev,0,sizeof(Prev));
	for (int i=1;i<=T;i++) dis[i]=1<<29;
	dis[S]=0;
	Q[1]=S;
	vis[S]=1;
	int t=0,w=1;
	while (t!=w)
	{
		t++;
		if (t>T*2) t=1;
		int u=Q[t];
		if (u==T) continue;
		vis[u]=0;
		for (int i=head[u];i;i=Next[i])
		if (val[i]>0)
		{
			int v=tree[i];
			if (dis[v]>dis[u]+cost[i])
			{
				Prev[v]=i;
				dis[v]=dis[u]+cost[i];
				if (!vis[v])
				{
					w++;
					if (w>T*2) w=1;
					Q[w]=v;
		    			vis[v]=1;
				}
	    		}
		}
	}
	return Prev[T]!=0;
}
int GetAns()
{
	int Min=1<<29,ans=0;
	for (int i=T;i!=S;i=From[Prev[i]])
	{
		Min=min(Min,val[Prev[i]]);
	}
	for (int i=T;i!=S;i=From[Prev[i]])
	{
		ans+=Min*cost[Prev[i]];
		val[Prev[i]]-=Min;
		val[Prev[i]^1]+=Min;
	}
	return ans;
}
int MinCostFlow()
{
	int ans=0;
	while (spfa()) ans+=GetAns();
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	S=n+n+1,T=n+n+5;
	int S1=n+n+2,S2=n+n+3,T1=n+n+4,T=n+n+5;
	tot=1;
	add_edge(S1,S2,m,0);
	add_edge(T1,S1,1<<29,0);
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		add_edge(S2,i,1<<29,0);
		add_edge(S,n+i,x,0);
		add_edge(i,T,x,0);
		add_edge(n+i,T1,1<<29,0);
	}
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
		{
			int x;
			scanf("%d",&x);
			if (x!=-1) add_edge(n+i,j,1<<29,x);
		}
	printf("%d\n",MinCostFlow());
	return 0;
}
