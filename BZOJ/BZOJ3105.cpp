#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,w[105],a[35];
long long ans=0;
bool cmp(int a,int b) { return a>b;}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&w[i]);
	sort(w+1,w+n+1,cmp);
	long long sum=0;
	for (int i=1;i<=n;i++)
	{
		int X=w[i];
		sum+=w[i];
		for (int j=30;j>=0;j--)
		if (X&(1<<j-1))
		{
			if (!a[j]) { a[j]=X;ans+=w[i];break;}
				else X^=a[j];
		}
	}
	if (!ans) puts("-1");
		else printf("%lld\n",sum-ans);
	return 0;
}
