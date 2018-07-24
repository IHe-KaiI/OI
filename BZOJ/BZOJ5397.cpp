#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
bool cmp(node a,node b) { return a.x<b.x;}

int main()
{
	scanf("%d%d",&m,&n);
	int cnt=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		A[++cnt]=a[i].x;A[++cnt]=a[i].y;
	}
	sort(A+1,A+cnt+1);
	cnt=unique(A+1,A+cnt+1)-A-1;
	for (int i=1;i<=n;i++)
	{
		a[i].x=lower_bound(A+1,A+cnt+1,a[i].x)-A;
		a[i].y=lower_bound(A+1,A+cnt+1,a[i].y)-A;
		if (a[i].y<a[i].x) a[i].y+=cnt;
	}
	sort(a+1,a+n+1,cmp);
	int MIN=1<<29;
	for (int i=n,j=n;i>=1;i=j-1)
	{
		while (a[j].x==a[j-1].x) j--;
		for (int k=j;k<=i;k++) Min[k]=MIN;
	}
	return 0;
}
