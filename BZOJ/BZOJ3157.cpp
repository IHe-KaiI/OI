#include<cstdio>
#include<algorithm>
#define mo 1000000007
#define ll long long
using namespace std;
const int N=1010;
int n,m;
ll f[N],finv[N],inv[N],ans[N];
ll C(ll n,ll m) { return f[n]*finv[m]%mo*finv[n-m]%mo;}
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
int main()
{
	scanf("%d%d",&n,&m);
	f[0]=finv[0]=inv[0]=inv[1]=1;
	if (m==1)
	{
		printf("%lld\n",(ll)n*(n+1)/2%mo);
		return 0;
	}
	for (int i=2;i<=m;i++) inv[i]=(ll)(mo-mo/i)*inv[mo%i]%mo;
	for (int i=1;i<=m;i++) finv[i]=finv[i-1]*inv[i]%mo;
	for (int i=1;i<=m;i++) f[i]=f[i-1]*i%mo;
	ll M=mi(m,n+1);
	ans[0]=(M-m+mo)*inv[m-1]%mo;
	for (int p=1;p<=m;p++)
	{
		for (int i=0;i<p;i++)
		{
			ans[p]=(ans[p]+C(p,i)*((p-i&1)?-1:1)*ans[i])%mo;
		}
		ans[p]=(ans[p]+mi(n,p)*M%mo+mo)%mo*inv[m-1]%mo;
	}
	printf("%lld\n",ans[m]);
	return 0;
}
