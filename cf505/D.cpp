#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,a[800],p[800][800],f[800][800],g[800][800],ans[800][800];
int gcd(int x,int y) { return (!y)?x:gcd(y,x%y);}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			if (i==j) p[i][j]=1;
				else p[i][j]=(gcd(a[i],a[j])>1);
		}
	for (int i=1;i<=n;i++) f[i][i]=g[i][i]=ans[i][i]=1;
	for (int l=0;l<n;l++)
		for (int i=1;i<=n;i++)
		{
			int j=i+l;
			if (j>n) break;
			for (int k=i;k<=j;k++)
			{
				if (f[i][k]&&g[k][j])
				{
					ans[i][j]=1;
					if (p[i-1][k]) g[i-1][j]=1;
					if (p[k][j+1]) f[i][j+1]=1;
				}
			}
		}
	if (ans[1][n]) puts("Yes");
		else puts("No");
	return 0;
}

