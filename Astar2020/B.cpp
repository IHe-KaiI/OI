#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int T,n,a[100];
double b[100],ans;
void dfs(int s,int t,double X)
{
	if (t>4||s<60)
	{
		ans=max(ans,X);
		return;
	}
	for (int i=10;i>=1;i--)
		if (s>=a[i]) dfs(s-a[i],t+1,X+b[i]);else break;
}
int main()
{
	scanf("%d",&T);
	a[1]=95;b[1]=4.3;
	a[2]=90;b[2]=4.0;
	a[3]=85;b[3]=3.7;
	a[4]=80;b[4]=3.3;
	a[5]=75;b[5]=3.0;
	a[6]=70;b[6]=2.7;
	a[7]=67;b[7]=2.3;
	a[8]=65;b[8]=2.0;
	a[9]=62;b[9]=1.7;
	a[10]=60;b[10]=1.0;
	while (T--)
	{
		scanf("%d",&n);
		ans=0;
		dfs(n,1,0);
		printf("%.1lf\n",ans);
	}
	return 0;
}

