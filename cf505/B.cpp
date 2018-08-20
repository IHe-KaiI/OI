#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
int n,x[200010],y[200010],cnt,A[200010];
void check(int i)
{
	if (i==1) return;
	bool flag=1;
	for (int j=2;j<=n;j++)
		if (x[j]%i!=0&&y[j]%i!=0) { flag=0;break;}
	if (flag) { printf("%d\n",i);exit(0);}
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
	int Max=max(x[1],y[1]);
	for (int i=2;i*i<=Max;i++)
	{
		if (x[1]%i==0)
		{
			while (x[1]%i==0) x[1]/=i;
			A[++cnt]=i;
		}
		if (y[1]%i==0)
		{
			while (y[1]%i==0) y[1]/=i;
			if (A[cnt]!=i) A[++cnt]=i;
		}
	}
	if (x[1]>=2) A[++cnt]=x[1];
	if (y[1]>=2&&A[cnt]!=y[1]) A[++cnt]=y[1];
	for (int i=1;i<=cnt;i++) check(A[i]);
	puts("-1");
	return 0;
}

