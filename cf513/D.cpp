#include<iostream>
#include<cstdio> 
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
int n,l[100010],r[100010];
int main()
{
	scanf("%d",&n);
	ll ans=0;
	for (int i=1;i<=n;i++) { scanf("%d%d",&l[i],&r[i]);ans+=l[i]+r[i];}
	sort(l+1,l+n+1);
	sort(r+1,r+n+1);
	for (int i=1;i<=n;i++)
		ans-=min(l[i],r[i]);
	printf("%lld\n",ans+n);
	return 0;
}



