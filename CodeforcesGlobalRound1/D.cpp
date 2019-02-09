#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=1000100;
int n,m,p[N],a[N],f[N][5][5];
void pre()
{
	for (int i=0;i<=m;i++)
		for (int j=0;j<=4;j++)
			for (int k=0;k<=4;k++) f[i][j][k]=-(1<<29);
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&p[i]);
		a[p[i]]++;
	}
	pre();
	f[0][0][0]=0;
	for (int i=1;i<=m;i++)
		for (int j=0;j<=4;j++)
			for (int k=0;k<=4;k++)
				for (int x=0;x<=min(a[i],8);x++)
				{
					int y=(a[i]-x)/3;
					f[i][k][min(4,x)]=max(f[i][k][min(4,x)],f[i-1][j][k]+y);
					if (x&&j&&k)
					{
						f[i][k-1][min(4,x-1)]=max(f[i][k-1][min(4,x-1)],f[i-1][j][k]+y+1);
					}
					if (x>1&&j>1&&k>1)
					{
						f[i][k-2][min(4,x-2)]=max(f[i][k-2][min(4,x-2)],f[i-1][j][k]+y+2);
					}
				}
	int ans=0;
	for (int i=0;i<=4;i++)
		for (int j=0;j<=4;j++) ans=max(ans,f[m][i][j]);
	printf("%d\n",ans);
	return 0;
}
