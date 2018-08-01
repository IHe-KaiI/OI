#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,x,a[100010],p[100010],q[500010];
int main()
{
	scanf("%d%d",&n,&x);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		p[a[i]]++;
	}
	for (int i=1;i<=n;i++)
		if (p[a[i]]>1) { puts("0");return 0;}
	for (int i=1;i<=n;i++)
	{
		int y=a[i]&x;
		if (y!=a[i]&&p[y]>0) { puts("1");return 0;}
		q[y]++;
	}
	for (int i=1;i<=n;i++)
		if (q[a[i]&x]>1) { puts("2");return 0;}
	puts("-1");
	return 0;
}

