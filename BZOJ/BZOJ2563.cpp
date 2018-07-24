#include<bits/stdc++.h>
using namespace std;
int n,m,a[10010];
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]<<=1;
	}
	for (int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		a[x]+=z;a[y]+=z;
	}
	sort(a+1,a+n+1);
	long long ans=0;
	for (int i=1;i<=n;i++)
		if (i&1) ans-=a[i];else ans+=a[i];
	printf("%lld\n",ans>>1);
	return 0;
}
