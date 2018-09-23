#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
int n,p[2],a[300010],A[300010];
int main()
{
	scanf("%d",&n);
	ll ans=0;
	for (int i=1;i<=n;i++)
	{
		ll x;
		scanf("%I64d",&x);
		for (int j=0;j<=60;j++) if ((x>>j)&1) a[i]++;
		int Max=a[i],sum=a[i];
		A[i]=a[i];
		for (int j=i-1;j>=max(1,i-65);j--)
		{
			Max=max(Max,a[j]);
			sum+=a[j];
			if (Max+Max<=sum&&sum%2==0) ans++;
			A[j]+=a[i];
		}
		if (a[i]&1) swap(p[0],p[1]);
		ans+=p[0];
		if (i>65) p[A[i-65]&1]++;
	}
	printf("%I64d\n",ans);
	return 0;
}
