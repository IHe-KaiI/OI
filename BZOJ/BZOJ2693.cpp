#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 100000009
using namespace std;
const int N=10000005;
int T,tot,prime[N];
ll g[N],sum[N];
bool flag[N];
struct node{int x,y;}Q[10010];
ll S(ll x) { return x*(x+1)/2%mo;}
void pre(int n)
{
	g[1]=1;
	for (int i=2;i<=n;i++)
	{
		if (!flag[i]) { prime[++tot]=i;g[i]=-i+1;}
		for (int j=1;j<=tot;j++)
		{
			if (prime[j]*i>n) break;
			int k=prime[j]*i;
			flag[k]=1;
			if (i%prime[j]==0) { g[k]=g[i];break;}
				else g[k]=g[i]*g[prime[j]]%mo;
		}
	}
	for (int i=1;i<=n;i++) sum[i]=(sum[i-1]+g[i]*i%mo+mo)%mo;
}
void solve(int x,int y)
{
	ll ans=0;int j;
	for (int i=1;i<=x&&i<=y;i=j+1)
	{
		j=min(x/(x/i),y/(y/i));
		(ans+=(sum[j]-sum[i-1]+mo)*S(x/i)%mo*S(y/i)%mo)%=mo;
	}
	printf("%lld\n",ans);
}
int main()
{
	scanf("%d",&T);
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
