#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
#define mo 1000000007
using namespace std;
const int N=10100;
ll n,f[N][60],inv[N],K,prime[N],num[N];
void pre(int n)
{
	inv[0]=inv[1]=1;
	for (int i=2;i<=n;i++) inv[i]=(ll)(mo-mo/i)*inv[mo%i]%mo;
}
int main()
{
	scanf("%lld%lld",&n,&K);
	ll cnt=0,Max=1;
	for (ll i=2;(ll)i*i<=n;i++)
	if (n%i==0)
	{
		prime[++cnt]=i;
		while (n%i==0) n/=i,num[cnt]++;
		Max=max(Max,num[cnt]);
	}
	if (n!=1)
	{
		prime[++cnt]=n;
		num[cnt]=1;
	}
	pre(10000);
	ll Ans=1;
	for (ll i=1;i<=cnt;i++)
	{
		memset(f,0,sizeof(f));
		f[0][num[i]]=1;
		for (ll j=1;j<=K;j++)
		{
			f[j][num[i]+1]=0;
			for (ll k=num[i];k>=0;k--) f[j][k]=(f[j][k+1]+f[j-1][k]*inv[k+1]%mo)%mo;
		}
		ll X=1,ans=0;
		for (ll j=0;j<=num[i];j++)
		{
			if (j) X=X*prime[i]%mo;
			ans=(ans+X*f[K][j]%mo)%mo;
		}
		Ans=Ans*ans%mo;
	}
	printf("%lld\n",Ans);
	return 0;
}
