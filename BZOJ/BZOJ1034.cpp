#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,a[100010],b[100010];
int solve(int *a,int *b)
{
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	int l=1,r=n,L=1,R=n,ans=0;
	for (int i=1;i<=n;i++)
	{
		if (a[l]>b[L]) { l++;L++;ans+=2;continue;}
		if (a[r]>b[R]) { r--;R--;ans+=2;continue;}
		if (a[l]==b[R]) ans++;
		l++;R--;
	}
	return ans;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++) scanf("%d",&b[i]);
	printf("%d %d\n",solve(a,b),n+n-solve(b,a));
	return 0;
}
