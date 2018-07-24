#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=50000,M=1000000,dx[5]={0,0,0,-1,1},dy[5]={0,-1,1,0,0};
int n,m,S,T,tot,Next[M],head[N],tree[M],val[M],Queue[N],h[N],cur[N];
inline int calc(int x,int y) { return (x-1)*m+y;}
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
int main()
{
	scanf("%d%d",&n,&m);
	tot=1;
	S=n*m*3+1;T=n*m*3+2;
	int sum=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			int x;
			scanf("%d",&x);
			add_edge(S,calc(i,j),x);
			sum+=x;
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			int x;
			scanf("%d",&x);
			add_edge(calc(i,j),T,x);
			sum+=x;
		}
	int now=n*m;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			int x;
			scanf("%d",&x);
			sum+=x;
			now++;
			for (int k=0;k<=4;k++)
			{
				int i1=i+dx[k],j1=j+dy[k];
				if (i1<1||j1<1||i1>n||j1>m) continue;
				add_edge(now,calc(i1,j1),1<<29);
			}
			add_edge(S,now,x);
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			int x;
			scanf("%d",&x);
			sum+=x;
			now++;
			for (int k=0;k<=4;k++)
			{
				int i1=i+dx[k],j1=j+dy[k];
				if (i1<1||j1<1||i1>n||j1>m) continue;
				add_edge(calc(i1,j1),now,1<<29);
			}
			add_edge(now,T,x);
		}
	printf("%d\n",sum-dinic());
	return 0;
}
