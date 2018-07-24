#include<cmath>
#include<cstdio>
#include<algorithm>
#define eps 1e-8
using namespace std;
int n,m,b[510];
struct node{int v;long double x[510];}a[510];
bool cmp(node a,node b) { return a.v<b.v;}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) scanf("%Lf",&a[i].x[j]);
	for (int i=1;i<=n;i++) scanf("%d",&a[i].v);
	sort(a+1,a+n+1,cmp);
	int ans=0,tot=0;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		if (fabs(a[i].x[j])>eps)
		{
			if (!b[j])
			{
				b[j]=i;
				tot++;
				ans+=a[i].v;
				break;
			}
			long double x=a[i].x[j]/a[b[j]].x[j];
			for (int k=j;k<=m;k++)
				a[i].x[k]-=a[b[j]].x[k]*x;
		}
	}
	printf("%d %d\n",tot,ans);
	return 0;
}
