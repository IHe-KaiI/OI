#include<cstdio>
#define mo 1000000007
using namespace std;
int T,n,a[100];
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		printf("%lld\n",(long long)(a[1]+a[n])%mo*250000002LL%mo);
	}
	return 0;
}
