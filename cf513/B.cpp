#include<iostream>
#include<cstdio> 
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
ll n;
int main()
{
	scanf("%lld",&n);
	if (n<=9) { printf("%lld\n",n);return 0;}
	ll x=9;
	while (x*10+9<=n) x=x*10+9;
	ll y=n-x,ans=0;
	while (x)
	{
		ans=ans+x%10;
		x/=10;
	}
	while (y)
	{
		ans=ans+y%10;
		y/=10;
	}
	printf("%lld\n",ans);
	return 0;
}

