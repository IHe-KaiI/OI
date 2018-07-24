#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 10086
using namespace std;
int n,b[35],num[35],m;
int mi(int x,int y)
{
	int ans=1;
	while (y)
	{
		if (y&1) ans=ans*x%mo;
		x=x*x%mo;
		y>>=1;
	}
	return ans;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		for (int i=30;i>=0;i--)
		if (x&(1<<i))
		{
			if (!b[i]) { b[i]=x;break;}
				else x^=b[i];
		}
	}
	scanf("%d",&m);
	if (!m) { puts("1");return 0;}
	num[0]=(b[0]!=0);
	for (int i=1;i<=30;i++) num[i]=num[i-1]+(b[i]!=0);
	int ans=0;
	for (int i=30;i>=0;i--)
		if (m&(1<<i)&&b[i]) (ans+=mi(2,num[i]-1))%=mo;
	if (!m) ans=1;
	printf("%d\n",(ans*mi(2,n-num[30])+1)%mo);
	return 0;
}
