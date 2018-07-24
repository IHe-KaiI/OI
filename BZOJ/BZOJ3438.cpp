#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=5010,M=15000000;
int n,tot,S,T,m,Max,Next[M],head[N],tree[M],val[M],cur[N],Q[N],h[N];
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
			if (used==low) return low;
		}
	}
	if (used==0) h[u]=-1;
	return used;
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
int dinic()
{
	int ans=0;
	while (bfs())
	{
		for (int i=1;i<=Max;i++) cur[i]=head[i];
		ans+=dfs(S,1<<29);
	}
	return ans;
}
int main()
{
	scanf("%d",&n);
	int ans=0;
	tot=1;S=n+n+1;T=n+n+2;
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		add_edge(S,i,x);
		add_edge(i,i+n,1<<29);
		add_edge(n+i,i,1<<29);
		ans+=x;
	}
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		add_edge(i+n,T,x);
		ans+=x;
	}
	Max=T;
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		int x,y,z,k;
		scanf("%d%d%d",&x,&y,&z);
		add_edge(++Max,T,z);
		add_edge(S,++Max,y);
		while (x--)
		{
			scanf("%d",&k);
			add_edge(k,Max-1,1<<29);
			add_edge(Max,k+n,1<<29);
		}
		ans+=y+z;
	}
	printf("%d\n",ans-dinic());
	return 0;
}
