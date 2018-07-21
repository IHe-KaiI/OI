#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
int n,a[200010];
ll sum[200010];
ll GetAns(ll x1,ll x2,ll x3,ll x4)
{
	ll Max=max(x1,max(x2,max(x3,x4))),Min=min(x1,min(x2,min(x3,x4)));
	return Max-Min;
}
ll abs(ll x,ll y) { return abs(x-y);}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	int l=1,r=3;
	ll ans=1LL<<60;
	for (int i=2;i<=n-1;i++)
	{
		while (l<i-1&&abs(sum[l],sum[i]-sum[l])>abs(sum[l+1],sum[i]-sum[l+1])) l++;
		while (r<n-1&&abs(sum[r]-sum[i],sum[n]-sum[r])>abs(sum[r+1]-sum[i],sum[n]-sum[r+1])) r++;
		ans=min(ans,GetAns(sum[l],sum[i]-sum[l],sum[r]-sum[i],sum[n]-sum[r]));
	}
	printf("%lld\n",ans);
	return 0;
}
