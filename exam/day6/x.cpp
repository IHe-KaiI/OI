#include<cstdio>
#define ll long long
#define mo 1000000007
using namespace std;
int main()
{
	freopen("1.out","w",stdout);
	ll ans=1;
	int cnt=0;
	printf("f[0]=1;");
	for (int i=1;i<=1000000000;i++)
	{
		ans=ans*i%mo;
		if (i%1000000==0)
		{
			printf("f[%d]=%lld;",++cnt,ans);
		}
	}
	return 0;
}
