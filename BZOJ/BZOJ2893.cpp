#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=3000,M=30000;
int n,m,Start,End,A[N],B[N],cnt,top,num,dfn[N],low[N],Stack[N],belong[N],Ans;
int tot,S,T,Next[M],head[N],tree[M],val[M],Cost[M],From[M],Prev[N],dis[N],Queue[N*2];
bool visit[N],In[N];
struct node{int x,y;}Edge[M];
namespace MinCostFlow
{
	void add(int x,int y,int z,int d)
	{
		tot++;
		Next[tot]=head[x];
		head[x]=tot;
		tree[tot]=y;
		val[tot]=z;
		Cost[tot]=d;
		From[tot]=x;
	}
	void add_edge(int x,int y,int z,int d)
	{
		add(x,y,z,d);
		add(y,x,0,-d);
	}
	bool spfa()
	{
		memset(visit,0,sizeof(visit));
		memset(Prev,0,sizeof(Prev));
		for (int i=1;i<=T;i++) dis[i]=-1<<29;
		int t=0,w=1;
		Queue[1]=S;visit[S]=1;
		dis[S]=0;
		while (t!=w)
		{
			t++;
			if (t>T*2) t=1;
			int u=Queue[t];
			if (u==T) continue;
			visit[u]=0;
			for (int i=head[u];i;i=Next[i])
			if (val[i]>0)
			{
				int v=tree[i];
				if (dis[v]<dis[u]+Cost[i])
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
	int GetAns()
	{
		int Flow=1<<29,ans=0;
		for (int i=T;Prev[i];i=From[Prev[i]]) Flow=min(val[Prev[i]],Flow);
		for (int i=T;Prev[i];i=From[Prev[i]])
		{
			ans+=Cost[Prev[i]]*Flow;
			val[Prev[i]]-=Flow;
			val[Prev[i]^1]+=Flow;
		}
		return ans;
	}
	int mcf()
	{
		int ans=0;
		Ans=0;
		while (spfa())
		{ 
			ans+=GetAns();
			Ans++;
			if (ans==num) break;
		}
		return ans;
	}
}
void Tarjan(int u)
{
	dfn[u]=low[u]=++cnt;
	Stack[++top]=u;In[u]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (!dfn[v])
		{
			Tarjan(v);
			low[u]=min(low[v],low[u]);
		}else if (In[v]) low[u]=min(low[u],dfn[v]);
	}
	if (low[u]==dfn[u])
	{
		int i;
		num++;
		do
		{
			i=Stack[top--];
			belong[i]=num;
			In[i]=0;
		}while (i!=u);
	}
}
int main()
{
	using namespace MinCostFlow;
	int Case;
	scanf("%d",&Case);
	while (Case--)
	{
		scanf("%d%d%d%d",&n,&m,&Start,&End);
		tot=1;cnt=0;top=0;num=0;
		memset(head,0,sizeof(head));
		memset(dfn,0,sizeof(head));
		memset(In,0,sizeof(In));
		for (int i=1;i<=Start;i++) scanf("%d",&A[i]);
		for (int i=1;i<=End;i++) scanf("%d",&B[i]);
		for (int i=1;i<=m;i++) 
		{
			scanf("%d%d",&Edge[i].x,&Edge[i].y);
			add(Edge[i].x,Edge[i].y,0,0);
		}
		for (int i=1;i<=n;i++) if (!dfn[i]) Tarjan(i);
		S=num*2+1,T=num*2+2;
		tot=1;
		memset(head,0,sizeof(head));
		for (int i=1;i<=m;i++)
		{
			if (belong[Edge[i].x]!=belong[Edge[i].y])
				add_edge(belong[Edge[i].x]+num,belong[Edge[i].y],1<<29,0);
		}
		for (int i=1;i<=Start;i++) add_edge(S,belong[A[i]],1<<29,0);
		for (int i=1;i<=End;i++) add_edge(belong[B[i]]+num,T,1<<29,0);
		for (int i=1;i<=num;i++) add_edge(i,i+num,1,1),add_edge(i,i+num,1<<29,0);
		if (mcf()==num) printf("%d\n",Ans);else puts("no solution");
	}
	return 0;
}
