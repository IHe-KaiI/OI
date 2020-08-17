#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int T,n,m,f[1005][1005];
int gcd(int x,int y) { return !y?x:gcd(y,x%y);}
int main()
{
	scanf("%d",&T);
	for (int i=1;i<=1000;i++) f[i][1]=f[1][i]=i;
	for (int i=2;i<=1000;i++)
		for (int j=2;j<=1000;j++)
		{
			f[i][j]=max(f[i][j-1],f[i-1][j]);
			if (gcd(i,j)==1) f[i][j]++;
		}
	while (T--)
	{
		scanf("%d%d",&n,&m);
		printf("%d\n",f[n][m]);
	}
	return 0;
}


