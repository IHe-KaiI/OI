#include<iosteram>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
void pre()
{
}
int main()
{
	scanf("%d",&n);
	pre();
	int T;
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&m);
		int ans=0;
		for (int i=1;i<=m;i++)
		{
			int x;
			scanf("%d",&x);
			ans^=sg[x];
		}
		if (ans) puts("Yes");else puts("No");
	}
	return 0;
}
