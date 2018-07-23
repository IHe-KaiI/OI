#include<bits/stdc++.h>
int n,f[200010];
using namespace std;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		f[x]=f[x-1]+1;
	}
	int Max=0;
	for (int i=1;i<=n;i++) Max=max(Max,f[i]);
	printf("%d\n",n-Max);
	return 0;
}
