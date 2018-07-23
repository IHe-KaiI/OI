#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,a[200010],p[200010];
int main()
{
	scanf("%d",&n);
	ll ans=0;
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
	{
		if (a[i]>i-1||i!=n&&a[i]<a[i+1]-1) { puts("-1");return 0;}
		p[i-a[i]]=a[i];
	}
	for (int i=1;i<=n;i++) ans+=p[i];
	printf("%lld\n",ans);
	return 0;
}
