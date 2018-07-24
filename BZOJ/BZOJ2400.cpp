#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,m,a[600],S,T,tot,Next[10000],head[600],tree[10000],val[10000],Queue[600],h[600],cur[600];
struct Edge{int x,y;}E[2010];
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
	memset(h,-1,sizeof(h));
	int t=0,w=1;
	Queue[1]=S;h[S]=0;
	while (t<w)
	{
		int u=Queue[++t];
		for (int i=head[u];i;i=Next[i])
		if (val[i]>0)
		{
			int v=tree[i];
			if (h[v]==-1)
			{
				h[v]=h[u]+1;
				Queue[++w]=v;
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
	if (val[i]>0)
	{
		int v=tree[i];
		if (h[v]==h[u]+1)
		{
			int w=dfs(v,min(val[i],low-used));
			used+=w;
			val[i]-=w;val[i^1]+=w;
			cur[u]=i;
			if (used==low) return used;
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
int main()
{
	scanf("%d%d",&n,&m);
	long long Ans=0,Sum=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if (a[i]>=0) Sum+=a[i];
	}
	for (int i=1;i<=m;i++) scanf("%d%d",&E[i].x,&E[i].y);
	S=n+1;T=n+2;
	for (int i=0;i<=30;i++)
	{
		tot=1;
		memset(head,0,sizeof(head));
		for (int j=1;j<=n;j++)
		{
			if (a[j]>=0)
			{
				if (!(a[j]&(1<<i))) add_edge(S,j,1<<29);
					else add_edge(j,T,1<<29);
			}else add_edge(S,j,1);
		}
		for (int j=1;j<=m;j++) add_edge(E[j].x,E[j].y,10000),add_edge(E[j].y,E[j].x,10000);
		int ans=dinic();
		Ans+=(1LL<<i)*(ans/10000);
		Sum+=(1LL<<i)*(ans%10000);
	}
	printf("%lld\n%lld\n",Ans,Sum);
	return 0;
}
