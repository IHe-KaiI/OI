#include<cstdio>
#include<algorithm>
#define mo 1234567891
#define ll long long
using namespace std;
const int N=150;
int T;
ll K,A,n,D,g[N],f[N];
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
ll Largrange(ll *a,ll K,ll n)
{
	if (n<=K) return a[n];
	ll ans=0;
	for (int i=1;i<=K;i++)
	{
		ll X=1,Y=1;
		for (int j=1;j<=K;j++)
		if (i!=j)
		{
			X=X*(n-j)%mo;
			Y=Y*(i-j)%mo;
		}
		ans=(ans+a[i]*X%mo*mi(Y,mo-2)%mo)%mo;
	}
	return ans;
}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%lld%lld%lld%lld",&K,&A,&n,&D);
		for (int i=1;i<=K+3;i++) g[i]=mi(i,K);
		for (int i=1;i<=K+3;i++) g[i]=(g[i-1]+g[i])%mo;
		for (int i=1;i<=K+3;i++) g[i]=(g[i-1]+g[i])%mo;
		f[0]=Largrange(g,K+3,A);
		for (int i=1;i<=K+5;i++) f[i]=Largrange(g,K+3,(D*i+A)%mo),f[i]=(f[i]+f[i-1])%mo;
		printf("%lld\n",(Largrange(f,K+5,n)+mo)%mo);
	}
	return 0;
}
