#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,a[300000];
int main()
{
	scanf("%d",&n);
	for (int i=0;i<(1<<n);i++) scanf("%d",&a[i]);
	int ans=0;
	for (int i=0;i<(1<<n);i++)
	{
		int Max=a[0],Max1=0;
		for (int s=i;s;s=(s-1)&i)
		{
			if (a[s]>Max) Max1=Max,Max=a[s];
				else Max1=max(Max1,a[s]);
		}
		ans=max(ans,Max+Max1);
		if (i) printf("%d\n",ans);
	}
	return 0;
}
