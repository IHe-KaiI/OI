#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 1000000007
using namespace std;
const int N=5000010;
int T,K,tot,prime[N];
struct node{int x,y;}Q[2010];
ll g[N];
bool flag[N];
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
void pre(int n)
{
	g[1]=1;
	for (int i=2;i<=n;i++)
	{
		if (!flag[i]) { prime[++tot]=i;g[i]=(mi(i,K)-1+mo)%mo;}
		for (int j=1;j<=tot;j++)
		{
			int k=prime[j]*i;
			if (k>N) break;
			flag[k]=1;
			if (i%prime[j]==0) { g[k]=(g[prime[j]]+1)*g[i]%mo;break;}
				else g[k]=g[prime[j]]*g[i]%mo;
		}
	}
	for (int i=1;i<=n;i++) (g[i]+=g[i-1])%=mo;
}
void solve(int x,int y)
{
	int j;ll ans=0;
	for (int i=1;i<=x&&i<=y;i=j+1)
	{
		j=min(x/(x/i),y/(y/i));
		(ans+=(g[j]-g[i-1]+mo)%mo*(x/i)%mo*(y/i)%mo)%=mo;
	}
	printf("%lld\n",ans);
}
int main()
{
	scanf("%d%d",&T,&K);
	int Max=0;
	for (int i=1;i<=T;i++)
	{
		scanf("%d%d",&Q[i].x,&Q[i].y);
		Max=max(Max,max(Q[i].x,Q[i].y));
	}
	pre(Max);
	for (int i=1;i<=T;i++) solve(Q[i].x,Q[i].y);
	return 0;
}
