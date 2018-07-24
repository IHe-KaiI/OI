#include<cstdio>
#define ll long long
ll a,b;
int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		scanf("%lld%lld",&a,&b);
		ll ans=a/b*(b-1);
		if (a%b) ans+=a%b-1;
		puts((ans&1)?"0":"1");
	}
	return 0;
}
