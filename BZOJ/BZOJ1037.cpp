#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 12345678
using namespace std;
int n,m,K,f[305][155][25][25];
void add(int &x,int y) { x+=y;if (x>=mo) x-=mo;}
int main()
{
	scanf("%d%d%d",&n,&m,&K);
	f[0][0][0][0]=1;
	for (int i=0;i<=n+m;i++)
		for (int j=0;j<=n;j++)
			for (int k=0;k<=K;k++)
				for (int l=0;l<=K;l++)
				{
					if (k+1<=K) add(f[i+1][j+1][k+1][max(0,l-1)],f[i][j][k][l]);
					if (l+1<=K) add(f[i+1][j][max(0,k-1)][l+1],f[i][j][k][l]);
				}
	int ans=0;
	for (int i=0;i<=K;i++)
		for (int j=0;j<=K;j++) add(ans,f[n+m][n][i][j]);
	printf("%d\n",ans);
	return 0;
}
