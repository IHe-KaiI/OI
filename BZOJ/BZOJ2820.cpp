#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=10000000;
int T,mu[N+7],tot,prime[N+7];
bool flag[N+7];
ll sum[N+7];
void pre()
{
	mu[1]=1;
	for (int i=2;i<=N;i++)
	{
		if (!flag[i]) { mu[i]=-1;prime[++tot]=i;}
		for (int j=1;j<=tot;j++)
		{
			if ((ll)i*prime[j]>N) break;
			int k=i*prime[j];
			flag[k]=1;
			if (i%prime[j]==0) { mu[k]=0;break;}
				else mu[k]=-mu[i];
		}
	}
	for (int i=1;i<=tot;i++)
	{
		for (int j=1;(ll)j*prime[i]<=N;j++) sum[j*prime[i]]+=mu[j];
	}
	for (int i=1;i<=N;i++) sum[i]+=sum[i-1];
}
int main()
{
	scanf("%d",&T);
	pre();
	while (T--)
	{
		int n,m,j;
		scanf("%d%d",&n,&m);
		ll ans=0;
		for (int i=1;i<=n&&i<=m;i=j+1)
		{
			j=min(n/(n/i),m/(m/i));
			ans+=(ll)(n/i)*(m/i)*(sum[j]-sum[i-1]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
