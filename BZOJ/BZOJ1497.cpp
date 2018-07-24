#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=56000,M=500000;
int n,m,tot,S,T,Next[M],head[N],tree[M],val[M],h[N],Queue[N],cur[N];
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
		int v=tree[i];
		if (h[v]==h[u]+1)
		{
			int w=dfs(v,min(val[i],low-used));
			val[i]-=w;val[i^1]+=w;
			used+=w;
			cur[u]=i;
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
		for (int i=1;i<=n+m+2;i++) cur[i]=head[i];
		ans+=dfs(S,1<<29);
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	tot=1;
	S=n+m+1;T=n+m+2;
	int sum=0;
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		add_edge(n+m+1,i,x);
	}
	for (int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add_edge(x,n+i,1<<29);
		add_edge(y,n+i,1<<29);
		add_edge(n+i,n+m+2,z);
		sum+=z;
	}
	printf("%d\n",sum-dinic());
	return 0;
}
