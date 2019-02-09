#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int b,K,a[100010];
int main()
{
	scanf("%d%d",&b,&K);
	for (int i=1;i<=K;i++) scanf("%d",&a[i]);
	int ans=0,x=1;
	for (int i=K;i>=1;i--)
	{
		ans=(ans+x*a[i]%2)%2;
		x=x*b%2;
	}
	if (ans&1) puts("odd");else puts("even");
	return 0;
}
