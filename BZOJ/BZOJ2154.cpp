#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 20101009
using namespace std;
const int MAXN=10000005;
int n,m,tot,prime[MAXN],mu[MAXN];
bool flag[MAXN];
long long Sum[MAXN],sum[MAXN];
long long S(int x) { return ((long long)x*(x+1)/2)%mo;}
void add(int &x,int y) { x+=y;if (x>mo) x-=mo;}
void pre(int N)
{
	mu[1]=1;
	for (int i=2;i<=N;i++)
	{
		if (!flag[i]) { mu[i]=-1;prime[++tot]=i;}
		for (int j=1;j<=tot;j++)
		{
			if ((long long)prime[j]*i>N) break;
			int k=prime[j]*i;
			flag[k]=1;
			if (i%prime[j]==0) { mu[k]=0;break;}
				else mu[k]=-mu[i];
		}
	}
	for (int i=1;i<=N;i++) sum[i]=(sum[i-1]+(long long)mu[i]*i*i%mo+mo)%mo;
	for (int i=1;i<=N;i++) Sum[i]=(Sum[i-1]+i)%mo;
}
long long calc(int n,int m)
{
	int j;long long ans=0;
	for (int i=1;i<=n&&i<=m;i=j+1)
	{
		j=min(n/(n/i),m/(m/i));
		ans=(ans+(sum[j]-sum[i-1]+mo)%mo*S(n/i)%mo*S(m/i)%mo)%mo;
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	pre(min(n,m));
	int j;
	long long ans=0;
	for (int i=1;i<=n&&i<=m;i=j+1)
	{
		j=min(n/(n/i),m/(m/i));
		ans=(ans+(Sum[j]-Sum[i-1]+mo)%mo*calc(n/i,m/i)%mo)%mo;
	}
	printf("%lld\n",ans);
	return 0;
}
