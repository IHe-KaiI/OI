#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=900,M=200000;
int n,m,k,a[25][25];
char s[50];
int DIS(int x1,int y1,int x2,int y2)
{
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
int calc(int x,int y) { return (x-1)*m+y;}
namespace DINIC
{
	int S,T,tot,Next[M],head[N],tree[M],val[M],Queue[N],h[N],cur[N];
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
}
int main()
{
	using namespace DINIC;
	scanf("%d%d%d",&n,&m,&k);
	tot=1;
	S=n*m*2+1;T=n*m*2+2;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) scanf("%1d",&a[i][j]);
	int Ans=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for (int j=1;j<=m;j++)
			if (s[j]=='L') add_edge(S,calc(i,j)+n*m,1),Ans++;
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		if (a[i][j]>0)
		{
			add_edge(calc(i,j)+n*m,calc(i,j),a[i][j]);
			for (int x=1;x<=n;x++)
				for (int y=1;y<=m;y++)
				if (a[x][y]>0&&(x!=i||y!=j)&&DIS(i,j,x,y)<=k*k) add_edge(calc(i,j),calc(x,y)+n*m,1<<29);
			if (DIS(i,j,0,j)<=k*k||DIS(i,j,i,0)<=k*k||DIS(i,j,i,m+1)<=k*k||DIS(i,j,n+1,j)<=k*k)
				add_edge(calc(i,j),T,1<<29);
		}
	printf("%d\n",Ans-dinic());
	return 0;
}
