#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,X,Y;
int Get(int x)
{
	printf("? %d\n",x);
	fflush(stdout);
	scanf("%d",&x);
	return x;
}
void erfen(int l,int r)
{
	while (l<=r)
	{
		int mid=(l+r)>>1;
		int x=Get(mid),y=Get(mid+n/2);
		if (x==y) { printf("! %d\n",mid);fflush(stdout);exit(0);}
		if ((X<Y&&x<y)||(X>Y&&x>y)) l=mid+1;
			else r=mid-1;
	}
}
int main()
{
	scanf("%d",&n);
	if ((n/2)&1) { puts("! -1");fflush(stdout);return 0;}
	X=Get(1);Y=Get(n/2+1);
	if (X==Y) { puts("! 1");fflush(stdout);return 0;}
	erfen(1,n/2);
	puts("! -1");
	fflush(stdout);
	return 0;
}
