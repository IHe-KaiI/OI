#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
int n;
ll a[200100];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n+n;i++) scanf("%I64d",&a[i]);
	sort(a+1,a+n+n+1);
	ll ans=(a[n]-a[1])*(a[n+n]-a[n+1]);
	for (int i=2;i<=n;i++)
	{
		ans=min((a[n+n]-a[1])*(a[i+n-1]-a[i]),ans);
	}
	printf("%I64d\n",ans);
	return 0;
}
