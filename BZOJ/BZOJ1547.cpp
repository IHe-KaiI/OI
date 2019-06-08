#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 100000007
#define ll long long
using namespace std;
const int N=2010;
int T,n,K,inv[N],prime[N],phi[N],tot,flag[N],f[N][N],g[N][N],sum[N][N],Mi[N];
void pre_phi(int n)
{
	inv[0]=inv[1]=Mi[0]=1;
	for (int i=2;i<=n;i++) inv[i]=(ll)(mo-mo/i)*inv[mo%i]%mo;
	for (int i=1;i<=n;i++) Mi[i]=Mi[i-1]*2%mo;
	phi[1]=1;
	for (int i=2;i<=n;i++)
	{
		if (!flag[i]) { prime[++tot]=i;phi[i]=i-1;}
		for (int j=1;j<=tot&&prime[j]*i<=n;j++)
		{
			flag[prime[j]*i]=1;
			if (i%prime[j]==0) { phi[i*prime[j]]=phi[i]*prime[j];break;}
				else phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
}
void pre_DP()
{
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	memset(sum,0,sizeof(sum));
	f[0][0]=1;
	for (int i=1;i<=n;i++)
		for (int j=0;j<=K;j++)
		{
			f[i][0]=(f[i][0]+f[i-1][j])%mo;
			if (j!=K) f[i][j+1]=(f[i][j+1]+f[i-1][j])%mo;
		}
	g[1][0]=1;
	for (int i=2;i<=n;i++)
	{
		for (int j=0;j<=K;j++)
		{
			g[i][0]=(g[i][0]+g[i-1][j])%mo;
			if (j!=K) g[i][j+1]=(g[i][j+1]+g[i-1][j])%mo;
		}
		for (int j=K;j>=0;j--) sum[i][j]=(sum[i][j+1]+g[i][j])%mo;
	}
}
int F(int X)
{
	if (n<=K) return Mi[X];
	if (X<=K) return (Mi[X]-1+mo)%mo;
	int ans=0;
	for (int i=0;i<=K;i++) ans=(ans+f[X][i])%mo;
	for (int i=1;i<min(K+1,X);i++) ans=(ans-sum[X-i][K-i+1]+mo)%mo;
	return ans;
}
int main()
{
	scanf("%d",&T);
	pre_phi(2000);
	while (T--)
	{
		scanf("%d%d",&n,&K);
		pre_DP();
		int ans=0;
		for (int i=1;i*i<=n;i++)
		if (n%i==0)
		{
			ans=(ans+(ll)F(i)*phi[n/i]%mo)%mo;
			if (i*i!=n)
			{
				ans=(ans+(ll)F(n/i)*phi[i]%mo)%mo;
			}
		}
		printf("%lld\n",(ll)ans*inv[n]%mo);
	}
	return 0;
}
