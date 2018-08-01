#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[5010],f[5010][2600][2][2];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	a[0]=1<<29;
	for (int i=0;i<=n;i++)
		for (int j=0;j<=(n+1)/2;j++)
			for (int k=0;k<2;k++) f[i][j][k][0]=f[i][j][k][1]=1<<29;
	f[1][0][0][0]=f[1][1][1][0]=0;
	for (int i=2;i<=n;i++)
		for (int j=0;j<=(n+1)/2;j++)
		{
			f[i][j][0][0]=min(f[i-1][j][0][0],f[i-1][j][0][1]);
			f[i][j][0][1]=f[i-1][j][1][0]+max(a[i]-a[i-1]+1,0);
			f[i][j][1][0]=f[i-1][j-1][0][1]+max(0,min(a[i-2]-1,a[i-1])-a[i]+1);
			f[i][j][1][0]=min(f[i][j][1][0],f[i-1][j-1][0][0]+max(0,a[i-1]-a[i]+1));
		}
	for (int i=1;i<=(n+1)/2;i++) printf("%d ",min(f[n][i][0][0],min(f[n][i][0][1],min(f[n][i][1][0],f[n][i][1][1]))));
	return 0;
}
