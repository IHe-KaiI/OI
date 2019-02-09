#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
const int N=100010;
int n,m,K,a[N];
priority_queue<int>Q;
int main()
{
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	long long ans=n;
	for (int i=2;i<=n;i++) Q.push(-(a[i]-a[i-1]-1));
	while (n>K)
	{
		int x=Q.top();
		Q.pop();
		ans+=-x;
		n--;
	}
	printf("%lld\n",ans);
	return 0;
}

