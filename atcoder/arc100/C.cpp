#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
int n,a[200010];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++) a[i]=a[i]-i;
	sort(a+1,a+n+1);
	int x=a[(n+1)>>1];
	ll ans=0;
	for (int i=1;i<=n;i++) ans+=abs(a[i]-x);
	printf("%lld\n",ans);
	return 0;
}
