#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,x,a[30];
int main()
{
	scanf("%d",&n);
	int L=1;
	ll ans=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		int NewL=L;
		for (int j=0;j<=19;j++)
		if ((x>>j)&1)
		{
			NewL=max(NewL,a[j]+1);
			a[j]=i;
		}
		if (NewL!=L) L=NewL;
		ans+=i-L+1;
	}
	printf("%lld\n",ans);
	return 0;
}
