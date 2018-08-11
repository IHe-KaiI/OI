#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,H,a,b,K;
int Abs(int x) { return (x>0)?x:-x;}
int main()
{
	scanf("%d%d%d%d%d",&n,&H,&a,&b,&K);
	for (int i=1;i<=K;i++)
	{
		int x,y,X,Y,ans=0;
		scanf("%d%d%d%d",&x,&y,&X,&Y);
		if (x==X) { printf("%d\n",Abs(y-Y));continue;}
		if (y>b) ans+=y-b,y=b;
		if (y<a) ans+=a-y,y=a;
		ans+=Abs(x-X);
		if (Y>b) ans+=Y-b,Y=b;
		if (Y<a) ans+=a-Y,Y=a;
		ans+=Abs(Y-y);
		printf("%d\n",ans);
	}
	return 0;
}
