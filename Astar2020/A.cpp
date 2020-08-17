#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=20000;
int T,n,m,a[N],b[N],f[N];
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d",&n,&m);
		int ans=1<<29;
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d",&a[i],&b[i]);
			ans=min(ans,((m-1)/a[i]+1)*b[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
