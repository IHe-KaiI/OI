#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=100,M=20000;
int n,a1,a2,an,b1,b2,bn,S,T,tot,Next[M],head[N],tree[M],val[M],Queue[N],h[N],cur[N];
char s[60][60];
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
			int w=dfs(v,min(low-used,val[i]));
			used+=w;
			val[i]-=w;val[i^1]+=w;
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
void Pre()
{
	tot=1;
	memset(head,0,sizeof(head));
	add_edge(S,a1,an*2);
	add_edge(S,b1,bn*2);
	add_edge(a2,T,an*2);
	add_edge(b2,T,bn*2);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			if (s[i][j]=='O') add_edge(i,j,2);
			if (s[i][j]=='N') add_edge(i,j,1<<29);
		}
}
int main()
{
	while (scanf("%d%d%d%d%d%d%d",&n,&a1,&a2,&an,&b1,&b2,&bn)!=EOF)
	{
		a1++;a2++;b1++;b2++;
		S=n+1;T=n+2;
		for (int i=1;i<=n;i++) scanf("%s",s[i]+1);
		Pre();
		int Ans=dinic();
		if (Ans!=an*2+bn*2) { puts("No");continue;}
		swap(b1,b2);
		Pre();
		Ans=dinic();
		if (Ans!=an*2+bn*2) puts("No");else puts("Yes");
	}
	return 0;
}
