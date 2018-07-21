#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,a[1010];
int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		a[0]=0;
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		int ans=0;
		for (int i=n;i>=1;i--)
			if (!(n-i&1)) ans^=a[i]-a[i-1];
		puts((ans>0)?"TAK":"NIE");
	}
	return 0;
}

