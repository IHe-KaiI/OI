#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
int n;
ll ans;
int main()
{
	scanf("%d",&n);
	bool flag=0;
	int X=1<<30;
	for (int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if (x!=y) flag=1;
		ans+=x;
		if (x>y) X=min(X,y);
	}
	if (X!=1<<30) ans-=X;
	if (!flag) ans=0;
	printf("%lld\n",ans);
	return 0;
}
