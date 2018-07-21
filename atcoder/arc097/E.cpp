#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=4010;
int n,a[N],posa[N],b[N],posb[N],p1[N][N],p2[N][N],f[N][N];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n+n;i++)
	{
		char s[2];int x;
		scanf("%s%d",s,&x);
		if (s[0]=='B') a[i]=x,posa[x]=i;
			else b[i]=x,posb[x]=i;
	}
	for (int i=1;i<=n+n;i++)
		for (int j=0;j<=n;j++)
		{
			p1[i][j]=p1[i-1][j]+(a[i]>j);
			p2[i][j]=p2[i-1][j]+(b[i]>j);
		}
	for (int i=0;i<=n;i++)
		for (int j=0;j<=n;j++)
		if (i||j)
		{
			int x=posa[i],y=posb[j];
			if (!i) { f[i][j]=f[i][j-1]+p1[y][i]+p2[y][j];continue;}
			if (!j) { f[i][j]=f[i-1][j]+p1[x][i]+p2[x][j];continue;}
			f[i][j]=min(f[i-1][j]+p1[x][i]+p2[x][j],f[i][j-1]+p1[y][i]+p2[y][j]);
		}
	printf("%d\n",f[n][n]);
	return 0;
}
