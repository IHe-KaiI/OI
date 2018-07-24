#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int T,mu[50010],tot,prime[50010],a,b,c,d,k,sum[50010];
bool flag[50010];
void pre()
{
	mu[1]=1;
	for (int i=2;i<=50000;i++)
	{
		if (!flag[i]) { mu[i]=-1;prime[++tot]=i;}
		for (int j=1;j<=tot;j++)
		{
			int k=prime[j]*i;
			if (k>50000) break;
			flag[k]=1;
			if (i%prime[j]==0) { mu[k]=0;break;}
				else mu[k]=-mu[i];
		}
	}
	for (int i=1;i<=50000;i++) sum[i]=sum[i-1]+mu[i];
}
long long query(int x,int y)
{
	x/=k;y/=k;
	int Min=min(x,y),j;
	long long ans=0;
	for (int i=1;i<=Min;i=j+1)
	{
		j=min(x/(x/i),y/(y/i));
		ans+=(long long)(sum[j]-sum[i-1])*(x/i)*(y/i);
	}
	return ans;
}
int main()
{
	scanf("%d",&T);
	pre();
	while (T--)
	{
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		printf("%lld\n",query(b,d)-query(a-1,d)-query(b,c-1)+query(a-1,c-1));
	}
	return 0;
}
