#include<bits/stdc++.h>
#define ll long long
#define mo 1000000007
using namespace std;
const int N=200;
int T,n,a[N],b[N],inv[20010];
void pre()
{
	inv[0]=inv[1]=1;
	for (int i=2;i<=20000;i++) inv[i]=(ll)(mo-mo/i)*inv[mo%i]%mo;
}
ll get_sum(ll x,ll y)
{
	return (x+y)*(y-x+1)%mo*inv[2]%mo;
}
ll get(int S,int x)
{
	ll ans=1;
	for (int i=1;i<=n;i++)
	{
		if (x<a[i]) return 0;
		if (x<=b[i])
		{
			ll L=x-a[i]+1;
			ans=ans*(L*S%mo-get_sum(a[i],x)+L)%mo*inv[b[i]-a[i]+1]%mo;
		}else
		{
			ll L=b[i]-a[i]+1;
			ans=ans*(L*S%mo-get_sum(a[i],b[i])+L)%mo*inv[b[i]-a[i]+1]%mo;
		}
	}
	return (ans+mo)%mo;
}
int main()
{
	scanf("%d",&T);
	pre();
	while (T--)
	{
		scanf("%d",&n);
		int Max=0;
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d",&a[i],&b[i]);
			Max=max(Max,b[i]);
		}
		ll ans=0;
		for (int i=1;i<=Max;i++)
		{
			ans=(ans+get(i,i)-get(i,i-1)+mo)%mo;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
