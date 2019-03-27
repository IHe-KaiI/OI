#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
bool cmp(node a,node b) { return a.z<b.z;}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
	}
	sort(a+1,a+m+1,cmp);
	for (int i=1;i<=n;i++) f[i]=i;
	for (int i=1;i<=m;i++)
	{

	}
	return 0;
}
