#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=100010;
int T,n,f[N],p[N];
struct node{int x,id;}a[N];
bool cmp(node a,node b) { return a.x>b.x;}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		for (int i=2;i<=n;i++)
			scanf("%d",&f[i]);
		for (int i=1;i<=n;i++) { scanf("%d",&a[i].x);a[i].id=i;}
		sort(a+1,a+n+1,cmp);
		ll Max=0;
		bool flag=0;
		for (int i=0;i<=n;i++) p[i]=0;
		for (int i=1;i<=n;i++)
		{
			int u=a[i].id;
			if (a[i].x<=0) break;
			if (!p[f[u]])
			{
				Max+=a[i].x;
				p[f[u]]++;
			}else
			{
				if (p[f[u]]==1&&!flag)
				{
					Max+=a[i].x;
					p[f[u]]++;
					flag=1;
				}
			}
		}
		ll Min=0;
		flag=0;
		for (int i=0;i<=n;i++) p[i]=0;
		for (int i=n;i>=1;i--)
		{
			int u=a[i].id;
			if (a[i].x>=0) break;
			if (!p[f[u]])
			{
				Min+=a[i].x;
				p[f[u]]++;
			}else
			{
				if (p[f[u]]==1&&!flag)
				{
					Min+=a[i].x;
					p[f[u]]++;
					flag=1;
				}
			}
		}
		printf("%I64d %I64d\n",Max,Min);
	}
	return 0;
}
