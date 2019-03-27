#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define MOD 999911659
using namespace std;
ll n,G,f[4][50010],inv[4][50010],ans[4];
ll prime[4]={2,3,4679,35617};
ll C(int x,int y,int mo)
{
	if (x<y) return 0;
	return f[mo][x]*inv[mo][y]%prime[mo]*inv[mo][x-y]%prime[mo];
}
ll lucas(ll x,ll y,int mo)
{
	if (x==0||x<y) return 0;
	if (x<prime[mo]) return C(x,y,mo);
	return lucas(x/prime[mo],y/prime[mo],mo)*C(x%prime[mo],y%prime[mo],mo)%prime[mo];
}
void solve(ll x)
{
	for (int i=0;i<4;i++)
	{
		ans[i]=(ans[i]+lucas(n,x,i))%prime[i];
	}
}
ll mi(ll x,int y,ll mo)
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
ll Union()
{
	ll M=MOD-1,Ans=0;
	for (int i=0;i<4;i++)
	{
		ll m=M/prime[i];
		Ans=(Ans+ans[i]*m%M*mi(m,prime[i]-2,prime[i])%M)%M;
	}
	return Ans;
}
int main()
{
	scanf("%lld%lld",&n,&G);
	if (G==MOD) { puts("0");return 0;}
	for (int i=0;i<4;i++)
	{
		f[i][0]=inv[i][0]=inv[i][1]=1;
		for (int j=1;j<=50000;j++) f[i][j]=f[i][j-1]*j%prime[i];
		for (int j=2;j<=50000;j++) inv[i][j]=(ll)(prime[i]-prime[i]/j)*inv[i][prime[i]%j]%prime[i];
		for (int j=2;j<=50000;j++) inv[i][j]=inv[i][j]*inv[i][j-1]%prime[i];
	}
	for (int i=1;i*i<=n;i++)
	if (n%i==0)
	{
		solve(i);
		if (n/i!=i) solve(n/i);
	}
	ll Ans=Union();
	printf("%lld\n",mi(G%MOD,Ans,MOD));
	return 0;
}
