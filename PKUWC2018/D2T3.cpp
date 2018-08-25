#include<bits/stdc++.h>
#define mo 998244353
#define ll long long
using namespace std;
const int N=20;
int n,Q,X,tot,Next[N<<1],head[N],tree[N<<1],deg[N],num[1<<N],F[1<<N],a[N],b[N];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
ll mi(ll x,int y)
{
	ll ans=1;
	while (y)
	{
		if (y&1) ans=ans*x%mo;
		x=x*x%mo;
		y>>=1;
	}
	return ans;
}
void dfs(int u,int fa,int S)
{
	if (S&(1<<u-1)) { a[u]=b[u]=0;return;}
	a[u]=deg[u];b[u]=0;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v!=fa)
		{
			dfs(v,u,S);
			a[u]=(a[u]-a[v]+mo)%mo;
			b[u]=(b[u]+b[v])%mo;
		}
	}
	a[u]=mi(a[u],mo-2)%mo;
	b[u]=(ll)a[u]*(b[u]+deg[u])%mo;
}
int main()
{
	scanf("%d%d%d",&n,&Q,&X);
	for (int i=1;i<(1<<n);i++) num[i]=num[i>>1]+(i&1);
	for (int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
		deg[x]++;deg[y]++;
	}
	for (int i=0;i<(1<<n);i++)
	{
		dfs(X,0,i);
		F[i]=b[X];
		if (!(num[i]&1)) F[i]=mo-F[i];
	}
	for (int i=1;i<=n;i++)
		for (int j=0;j<(1<<n);j++)
			if (j&(1<<i-1)) F[j]=(F[j]+F[j^(1<<i-1)])%mo;
	for (int i=1;i<=Q;i++)
	{
		int K,sta=0,x;
		scanf("%d",&K);
		for (int j=1;j<=K;j++)
		{
			scanf("%d",&x);
			sta=sta|(1<<x-1);
		}
		printf("%d\n",F[sta]);
	}
	return 0;
}
