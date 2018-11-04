#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 1000000007 
using namespace std;
int n;
ll a[100010],f[100010],inv[100010];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
	f[0]=1;
	for (int i=1;i<=n;i++) f[i]=f[i-1]*i%mo;
	inv[0]=inv[1]=1;
	ll ans=0,sum=0;
	for (int i=2;i<=n;i++) inv[i]=(ll)(mo-mo/i)*inv[mo%i]%mo;
	for (int i=1;i<=n;i++) sum=(sum+f[n]*inv[i]%mo)%mo;
	for (int i=1;i<=n;i++)
	{
		ans=(ans+a[i]*sum%mo)%mo;
		(sum-=f[n]*inv[n-i+1]%mo)%=mo;
		(sum+=f[n]*inv[i+1]%mo)%=mo;
	}
	printf("%lld\n",(ans+mo)%mo);
	return 0;
}

