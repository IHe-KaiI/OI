#include<bits/stdc++.h>
using namespace std;
int n,a[110];
int main()
{
	scanf("%d",&n);
	int ans=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if (a[i]==a[i-1]) a[i]=0,ans++;
	}
	printf("%d\n",ans);
	return 0;
}
