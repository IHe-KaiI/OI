#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
int n,S,T,tot,a[1010],Next[2100000],head[1010],tree[2100000],h[1010],Q[1010],cur[1010];
ll val[2100000];
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
ll dfs(int u,ll low)
{
	if (u==T) return low;
	ll used=0;
	for (int i=cur[u];i;i=Next[i])
	if (val[i])
	{
		int v=tree[i];
		if (h[v]==h[u]+1)
		{
			ll w=dfs(v,min(val[i],low-used));
			used+=w;
			val[i]-=w;val[i^1]+=w;
			cur[u]=i;
			if (used==low) return low;
		}
	}
	if (used==0) h[u]=-1;
	return used;
}
ll dinic()
{
	ll ans=0;
	while (bfs())
	{
		for (int i=1;i<=T;i++) cur[i]=head[i];
		ans+=dfs(S,1LL<<60);
	}
	return ans;
}
int main()
{
	scanf("%d",&n);
	S=n+1;T=n+2;tot=1;
	for (int i=1;i<=n;i++) { scanf("%d",&a[i]);add_edge(S,i,a[i]);}
	ll ans=0;
	for (int i=1;i<=n;i++)
	{
		ll sum=0;
		for (int j=1;j<=n;j++)
		{
			int x;
			scanf("%d",&x);
			if (i!=j) add_edge(i,j,x<<1);
			sum+=x;
			ans+=x;
		}
		add_edge(i,T,sum);
	}
	printf("%lld\n",ans-dinic());
	return 0;
}
