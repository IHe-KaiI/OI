#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int m,n,p[100];
int main()
{
	scanf("%d%d",&m,&n);
	for (int i=1;i<=n;i++)
	{
		puts("1");
		fflush(stdout);
		int x;
		scanf("%d",&x);
		if (!x) return 0;
		if (x==-1) p[i]=0;
			else p[i]=1;
	}
	int l=1,r=m,now=1;
	while (l<r)
	{
		int mid=(l+r)>>1;
		printf("%d\n",mid);
		fflush(stdout);
		int x;
		scanf("%d",&x);
		if (!p[now]) x=-x;
		now++;
		if (now>n) now=1;
		if (x==0) return 0;
		if (x==1) l=mid+1;
			else r=mid-1;
	}
	printf("%d\n",l);
	return 0;
}
