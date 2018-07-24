#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,m,S,T,tot,Next[200000],head[350],tree[200000],val[200000],Q[350],h[350],cur[350];
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
	Q[1]=S;h[S]=0;
	while (t<w)
	{
		int u=Q[++t];
		for (int i=head[u];i;i=Next[i])
		if (val[i]>0)
		{
			int v=tree[i];
			if (h[v]==-1)
			{
				h[v]=h[u]+1;
				Q[++w]=v;
			}
		}
	}
	return h[T]!=-1;
}
int dfs(int u,int low)
{
	if (u==T) return low;
	int used=0;
	for (int i=head[u];i;i=Next[i])
	if (val[i]>0)
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
		for (int i=1;i<=T;i++) cur[i]=head[i];
		ans+=dfs(S,1<<29);
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	S=n+1;T=n+2;tot=1;
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		if (x) add_edge(S,i,1);else add_edge(i,T,1);
	}
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add_edge(x,y,1);add_edge(y,x,1);
	}
	printf("%d\n",dinic());
	return 0;
}
