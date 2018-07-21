#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=2005;
int n,m,cnt;
struct node{int u,v,x,y;}Edge[N];
namespace DINIC
{
	int S,T,tot,Next[N<<3],head[N],tree[N<<3],val[N<<3],Q[N],h[N],cur[N],In[N],Out[N];
	void Clear()
	{
		tot=1;
		memset(head,0,sizeof(head));
	}
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
		for (int i=cur[u];i;i=Next[i])
		if (val[i]>0)
		{
			int v=tree[i];
			if (h[v]==h[u]+1)
			{
				int w=dfs(v,min(low-used,val[i]));
				val[i]-=w;val[i^1]+=w;
				used+=w;
				cur[u]=i;
				if (used==low) return low;
			}
		}
		if (!used) h[u]=-1;
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
bool check(int X)
{
	using namespace DINIC;
	memset(In,0,sizeof(In));
	memset(Out,0,sizeof(Out));
	Clear();
	for (int i=1;i<=cnt;i++)
	{
		int x=Edge[i].u,y=Edge[i].v;
		if (Edge[i].x<=X&&Edge[i].y<=X) { Out[x]++;In[y]++;add_edge(y,x,1);continue;}
		if (Edge[i].x<=X) { Out[x]++;In[y]++;}
		if (Edge[i].y<=X) { Out[y]++;In[x]++;}
	}
	S=n+1;T=n+2;
	int sum=0;
	for (int i=1;i<=n;i++)
	{
		if ((In[i]-Out[i])%2) return 0;
		if (In[i]>=Out[i]) add_edge(S,i,(In[i]-Out[i])>>1),sum+=(In[i]-Out[i])>>1;
			else add_edge(i,T,(Out[i]-In[i])>>1);
	}
	return dinic()==sum;
}
int erfen(int l,int r)
{
	while (l<r)
	{
		int mid=(l+r)>>1;
		if (check(mid)) r=mid;
			else l=mid+1;
	}
	return r;
}
int main()
{
	scanf("%d%d",&n,&m);
	int Max=0;
	for (int i=1;i<=m;i++)
	{
		int u,v,x,y;
		scanf("%d%d%d%d",&u,&v,&x,&y);
		Max=max(Max,min(x,y));
		Edge[++cnt]=(node){u,v,x,y};
	}
	int ans=erfen(Max,1001);
	if (ans==1001) puts("NIE");
		else printf("%d\n",ans);
	return 0;
}

