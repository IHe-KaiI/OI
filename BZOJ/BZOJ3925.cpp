#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=11,M=55;
int n,m,P[N][N],X[2],Q[1<<N][N],p[1<<N][1<<N];
long long f[1<<N][M],g[M][M];
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		P[x][y]=P[y][x]=1;
	}
	X[0]=1;X[1]=-1;
	for (int i=0;i<(1<<n);i++)
		for (int j=1;j<=n;j++)
		{
			for (int k=1;k<=n;k++)
				if (i&(1<<k-1)&&P[j][k]) Q[i][j]++;
		}
	for (int i=0;i<(1<<n);i++)
	{
		for (int j=0;j<(1<<n);j++)
			for (int k=1;k<=n;k++)
			if (j&(1<<k-1))
			{
				p[i][j]=p[i][j-(1<<k-1)]+Q[i][k];
				break;
			}
	}
	X[0]=1;X[1]=-1;
	g[0][0]=1;
	for (int i=1;i<=m;i++)
	{
		for (int j=m;j>=0;j--)
			for (int k=1;k>=0;k--) g[i][j+k]+=g[i-1][j]*X[k];
	}
	for (int i=0;i<n;i++) f[1<<i][0]=1;
	for (int i=1;i<=(1<<n)-1;i++)
	if (!f[i][0])
	{
		int I=i^(i&-i);
		for (int j=(i-1)&I;j;j=(j-1)&I)
		{
			for (int k=m;k>=0;k--)
				for (int l=m-k;l>=0;l--)
					f[i][l+k]+=f[i-j][k]*g[p[i-j][j]][l];
		}
		for (int j=0;j<=m;j++) f[i][j]=-f[i][j];
		f[i][0]++;
	}
	__float128 ans=1.0;
	for (int i=0;i<=m;i++) ans-=(__float128)f[(1<<n)-1][i]/(i+1);
	printf("%.6lf\n",(double)ans);
	return 0;
}
