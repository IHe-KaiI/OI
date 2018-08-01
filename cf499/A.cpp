#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n;
double m,a[1010],b[1010];
int main()
{
	scanf("%d%lf",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lf",&a[i]);
	for (int i=1;i<=n;i++) scanf("%lf",&b[i]);
	for (int i=1;i<=n;i++)
		if (a[i]==1||b[i]==1) { puts("-1");return 0;}
	double ans=m/(b[1]-1),M=m;
	m+=ans;
	for (int i=n;i>=2;i--)
	{
		ans=m/(a[i]-1);
		m+=ans;
		ans=m/(b[i]-1);
		m+=ans;
	}
	ans=m/(a[1]-1);
	printf("%.6lf\n",m+ans-M);
	return 0;
}
