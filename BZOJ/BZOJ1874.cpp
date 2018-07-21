#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,a[15],m,b[15],sg[1010];
bool p[2010][1010];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	scanf("%d",&m);
	for (int i=1;i<=m;i++) scanf("%d",&b[i]);
	for (int i=0;i<=1000;i++)
	{
		for (int j=0;j<=1000;j++)
			if (!p[i][j]) { sg[i]=j;break;}
		for (int j=1;j<=m;j++) p[i+b[j]][sg[i]]=1;
	}
	int ans=0;
	for (int i=1;i<=n;i++) ans^=sg[a[i]];
	if (!ans) { puts("NO");return 0;}
	puts("YES");
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if ((ans^sg[a[i]]^sg[a[i]-b[j]])==0) { printf("%d %d\n",i,b[j]);return 0;}
	return 0;
}
