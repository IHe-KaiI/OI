#include<cstdio>
#include<algorithm>
#define mo 1000000007
#define ll long long
using namespace std;
const int N=18;
int n,a[N][N];
ll g[1<<N],f[1<<N];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) scanf("%d",&a[i][j]);
	for (int i=0;i<=(1<<n)-1;i++)
	{
		g[i]=1;
		for (int j=1;j<=n;j++)
		if (i&(1<<j-1))
			for (int k=1;k<j;k++)
				if (i&(1<<k-1)) g[i]=g[i]*(a[j][k]+1)%mo;
	}
	for (int i=1;i<=(1<<n)-1;i++)
	{
		f[i]=g[i];
		for (int j=i-1;j;j=(j-1)&i)
			f[i]=(f[i]-g[j]*f[i^j]%mo)%mo;
	}
	printf("%lld\n",(f[(1<<n)-1]+mo)%mo);
	return 0;
}
