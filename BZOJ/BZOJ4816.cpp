#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 1000000007
using namespace std;
int T,mu[1000100],prime[1000100],tot;
ll f[1000100],g[1000100],inv[1000100],Inv[1000100];
struct node{int x,y;}Q[1005];
bool flag[1000100];
ll mi(ll x,ll y)
{
	y%=(mo-1);
	ll ans=1;
	while (y)
	{
		if (y&1) ans=ans*x%mo;
		x=x*x%mo;
		y>>=1;
	}
	return ans;
}
void Init(int n)
{
	mu[1]=1;
	f[0]=0;f[1]=1;
	inv[0]=0;inv[1]=1;
	for (int i=2;i<=n;i++) f[i]=(f[i-1]+f[i-2])%mo,inv[i]=mi(f[i],mo-2)%mo;
	for (int i=2;i<=n;i++)
	{
		if (!flag[i]) { prime[++tot]=i;mu[i]=-1;}
		for (int j=1;j<=tot;j++)
		{
			if (prime[j]*i>n) break;
			flag[prime[j]*i]=1;
			if (i%prime[j]==0) { mu[i*prime[j]]=0;break;}
				else mu[i*prime[j]]=-mu[i];
		}
	}
	for (int i=1;i<=n;i++) g[i]=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n/i;j++)
		{
			if (!mu[j]) continue;
			if (mu[j]>0) g[i*j]=g[i*j]*f[i]%mo;
				else g[i*j]=g[i*j]*inv[i]%mo;
		}
	g[0]=1;Inv[0]=1;
	for (int i=1;i<=n;i++) g[i]=g[i-1]*g[i]%mo,Inv[i]=mi(g[i],mo-2)%mo;
}
void solve(int x,int y)
{
	ll ans=1;
	int j;
	for (int i=1;i<=x&&i<=y;i=j+1)
	{
		j=min(x/(x/i),y/(y/i));
		ans=ans*mi((g[j]*Inv[i-1]%mo),(ll)(x/i)*(y/i))%mo;
	}
	printf("%lld\n",ans);
}
int main()
{
	scanf("%d",&T);
	int Max=0;
	for (int i=1;i<=T;i++) { scanf("%d%d",&Q[i].x,&Q[i].y);Max=max(Max,max(Q[i].x,Q[i].y));}
	Init(Max);
	for (int i=1;i<=T;i++) solve(Q[i].x,Q[i].y);
	return 0;
}
