#include<cstdio>
#include<algorithm>
using namespace std;
int n,m;
double f[2][5010];
int main()
{
	scanf("%d%d",&n,&m);
	int now=0;
	f[1][0]=1.0;
	for (int i=1;i<=n;i++)
	{
		now=now^1;
		for (int j=0;j<=m;j++)
			f[now][j]=max(0.0,(double)i/(i+j)*(f[now^1][j]+1)+(double)j/(i+j)*(f[now][j-1]-1));
	}
	printf("%.6lf\n",f[now][m]-5e-7);
	return 0;
}
