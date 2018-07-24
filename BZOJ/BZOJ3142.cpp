#include<cstdio>
#define ll long long
using namespace std;
ll n,k,m,mo;
ll mi(ll x,ll y)
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
	scanf("%lld%lld%lld%lld",&n,&k,&m,&mo);
	n%=mo;
	printf("%lld\n",(n*mi(m,k-1)%mo-mi(m,k-2)*(m*(m+1)/2%mo)%mo*(k-1)%mo+mo)%mo);
	return 0;
}
