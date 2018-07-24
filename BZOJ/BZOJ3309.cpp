#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=10000007;
int T,tot,Min[N],Max[N],Num[N],a[N],b[N],c[N],prime[N],ans[N],sum[N];
void pre()
{
	ans[1]=0;
	for (int i=2;i<=10000000;i++)
	{
		if (!Min[i])
		{
			Min[i]=min(Min[c[i]],b[i]);
			Max[i]=max(Max[c[i]],b[i]);
			Num[i]=Num[c[i]]+1;
		}
		if (!a[i])
		{
			prime[++tot]=i;
			a[i]=tot;
			b[i]=1;
			c[i]=1;
			long long t=i;int s=0;
			while (t<=10000000)
			{
				s++;
				Max[t]=Min[t]=s;
				Num[t]=1;
				t*=i;
			}
		}
		for (int j=1;j<=tot&&i*prime[j]<=10000000&&j<=a[i];j++)
		{
			a[i*prime[j]]=j;
			if (a[i]==j)
			{
				b[i*prime[j]]=b[i]+1;
				c[i*prime[j]]=c[i];
			}else
			{
				b[i*prime[j]]=1;
				c[i*prime[j]]=i;
			}
		}
	}
	for (int i=2;i<=10000000;i++)
	if (Max[i]==Min[i])
	{
		if (Num[i]&1) ans[i]=1;else ans[i]=-1;
	}
	for (int i=1;i<=10000000;i++) sum[i]=sum[i-1]+ans[i];
}
ll calc(int x,int y)
{
	ll ans=0;int j;
	for (int i=1;i<=x&&i<=y;i=j+1)
	{
		j=min(x/(x/i),y/(y/i));
		ans+=(ll)(sum[j]-sum[i-1])*(x/i)*(y/i);
	}
	return ans;
}
int main()
{
	scanf("%d",&T);
	pre();
	for (int i=1;i<=T;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%lld\n",calc(x,y));
	}
	return 0;
}
