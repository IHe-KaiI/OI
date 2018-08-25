#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 998244353
using namespace std;
const int N=6010;
int T,n,m,K;
ll a[N],b[N],f[N][N],g[N][N],F[N],C[N][N],sumf[N][N];
void pre()
{
	C[0][0]=1;
	for (int i=1;i<=6000;i++)
	{
		C[i][0]=1;
		for (int j=1;j<=min(3000,i);j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mo;
	}
}
int main()
{
	scanf("%d",&T);
	pre();
	while (T--)
	{
		scanf("%d%d%d",&n,&m,&K);
		for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
		sort(a+1,a+n+1);
		for (int i=1;i<=n;i++) scanf("%lld",&b[i]);
		sort(b+1,b+n+1);
		if (K==1)
		{
			ll ans=0;
			for (int i=1;i<=n;i++) ans=(ans+b[i]*C[n+i-1][m-1]%mo)%mo;
			printf("%lld\n",ans);
			continue;
		}
		for (int i=0;i<=n+1;i++)
		{
			F[i]=0;
			for (int j=0;j<=n+1;j++) f[i][j]=g[i][j]=0;
		}
		for (int i=0;i<=n+1;i++) f[i][0]=1;
		for (int i=n;i>=1;i--)
			for (int j=1;j<=min(m,n-i+1);j++)
			{
				f[i][j]=(f[i+1][j]+f[i+1][j-1]*a[i]%mo)%mo;
				g[i][j]=(g[i+1][j]+g[i+1][j-1]+b[i]*C[n-i][j-1]%mo)%mo;
			}
		for (int i=1;i<=n;i++)
			for (int j=min(m,n-i+1);j>=1;j--)
			{
				f[i][j]=a[i]*f[i+1][j-1]%mo;
				g[i][j]=(g[i+1][j-1]+b[i]*C[n-i][j-1]%mo)%mo;
			}
		for (int i=K-1;i<=n;i++)
			for (int j=1;j<=n-K+2;j++) F[i]=(F[i]+f[j][K-1]*C[j-1][i-K+1]%mo)%mo;
		ll ans=0;
		for (int i=1;i<=n;i++)
		{
			ll sum=0;
			for (int j=K-1;j<=min(n,m-1);j++) sum=(sum+F[j]*C[i-1][m-j-1]%mo)%mo;
			ans=(ans+b[i]*sum%mo)%mo;
		}
		for (int i=0;i<=K-2;i++) sumf[n+1][i]=0;
		for (int i=n;i>=1;i--)
		{
			sumf[i][0]=1;
			for (int j=1;j<=K-2;j++) sumf[i][j]=(sumf[i+1][j]+f[i][j])%mo;
		}
		for (int i=0;i<=min(n,K-2);i++)
		{
			ll sum=0;
			for (int j=m-K+1;j<=min(n,n-K+i+1);j++) sum=(sum+g[j][K-i]*C[j-1][m-K]%mo)%mo;
			ans=(ans+sumf[1][i]*sum%mo)%mo;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
