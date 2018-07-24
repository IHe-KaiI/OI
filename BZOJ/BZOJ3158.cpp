#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define Sqr(x) ((x)*(x))
using namespace std;
int n,a[3050],b[3050],tot,S,T,Next[6000100],head[3050],tree[6000100],val[6000100],cur[3050],h[3050],Queue[3050];
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
int gcd(int x,int y) { return (!y)?x:gcd(y,x%y);}
bool calc(int x,int y) { return gcd(a[x],a[y])==1;}
bool calc1(ll x,ll y)
{
	return Sqr((ll)sqrt(Sqr(x)+Sqr(y)))==Sqr(x)+Sqr(y);
}
bool bfs()
{
	int t=0,w=1;
	memset(h,-1,sizeof(h));
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
				Queue[++w]=v;
				h[v]=h[u]+1;
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
	if (val[i]>0)
	{
		int v=tree[i];
		if (h[v]==h[u]+1)
		{
			ll w=dfs(v,min((ll)val[i],low-used));
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
	tot=1;
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++) scanf("%d",&b[i]);
	ll ans=0;
	S=n+1;T=n+2;
	for (int i=1;i<=n;i++)
	{
		ans+=b[i];
		if (a[i]&1) add_edge(S,i,b[i]);
			else { add_edge(i,T,b[i]);continue;}
		for (int j=1;j<=n;j++)
			if (i!=j&&calc(i,j)&&calc1(a[i],a[j])) add_edge(i,j,1<<29);
	}
	printf("%lld\n",ans-dinic());
	return 0;
}
