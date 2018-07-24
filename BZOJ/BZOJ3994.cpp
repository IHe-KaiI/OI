#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=50000;
int T,mu[N+5],tot,prime[N+5],sum[N+5];
bool flag[N];
long long g[N+5];
void pre()
{
	mu[1]=1;
	for (int i=2;i<=N;i++)
	{
		if (!flag[i]) { mu[i]=-1;prime[++tot]=i;}
		for (int j=1;j<=tot;j++)
		{
			int k=prime[j]*i;
			if (k>N) break;
			flag[k]=1;
			if (i%prime[j]==0) { mu[k]=0;break;}
				else mu[k]=-mu[i];
		}
	}
	for (int i=1;i<=N;i++) sum[i]=sum[i-1]+mu[i];
	for (int i=1;i<=N;i++)
	{
		int k;
		for (int j=1;j<=i;j=k+1)
		{
			k=i/(i/j);
			g[i]+=(long long)(i/j)*(k-j+1);
		}
	}
}
void solve(int x,int y)
{
	int j;long long ans=0;
	for (int i=1;i<=x&&i<=y;i=j+1)
	{
		j=min(x/(x/i),y/(y/i));
		ans+=(long long)(sum[j]-sum[i-1])*g[x/i]*g[y/i];
	}
	printf("%lld\n",ans);
}
int main()
{
	scanf("%d",&T);
	pre();
	while (T--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		solve(x,y);
	}
	return 0;
}
