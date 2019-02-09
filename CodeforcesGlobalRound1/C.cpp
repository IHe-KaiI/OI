#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n;
int Get(int x)
{
	for (int i=2;(long long)i*i<=x;i++)
	if (x%i==0)
	{
		return i;
	}
	return x;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		int ans=1;
		while (ans<=x) ans<<=1;
		if (ans==x+1)
		{
			printf("%d\n",x/Get(x));
		}else printf("%d\n",ans-1);
	}
	return 0;
}

