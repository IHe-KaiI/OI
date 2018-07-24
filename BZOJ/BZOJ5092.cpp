#include<cstdio>
#include<algorithm>
using namespace std;
int n,f[1<<22],a[300100],sum[300100];
int main()
{
	scanf("%d",&n);
	for (int i=0;i<=(1<<21);i++) f[i]=1<<29;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]^a[i];
		f[sum[i]]=min(f[sum[i]],i);
	}
	for (int i=(1<<20);i>=0;i--)
		for (int j=0;j<=20;j++) f[i]=min(f[i],f[i|(1<<j)]);
	for (int i=1;i<=n;i++)
	{
		int ans=0;
		for (int j=20;j>=0;j--)
		if (!(sum[i]&(1<<j)))
		{
			if (f[ans|(1<<j)]<=i) ans|=1<<j;
		}
		printf("%d\n",ans+(sum[i]^ans));
	}
	return 0;
}
