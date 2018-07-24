#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,m,a[150][150],p[150][150],g[150][150],lazy[150][150];
bool judge(int x,int y)
{
	memset(g,0,sizeof(g));
	memset(lazy,0,sizeof(lazy));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			g[i][j]=g[i-1][j]+g[i][j-1]-g[i-1][j-1]+lazy[i][j];
			if (g[i][j]>a[i][j]) return 0;
			if (g[i][j]<a[i][j])
			{
				int X=i+x-1,Y=j+y-1;
				if (X>n||Y>m) return 0;
				int Z=a[i][j]-g[i][j];
				g[i][j]+=Z;
				lazy[i][j]+=Z;
				lazy[X+1][j]-=Z;
				lazy[i][Y+1]-=Z;
				lazy[X+1][Y+1]+=Z;
			}
		}
	return 1;
}
int main()
{
	scanf("%d%d",&n,&m);
	int sum=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			sum+=a[i][j];
		}
	int ans=1<<29;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		if (!p[i][j])
		{
			if (judge(i,j)) ans=min(ans,sum/(i*j));
			else
			{
				int x=i,y=j;
				while (x<=n&&y<=m) p[x][y]=1,x+=i,y+=j;
			}
		}
	printf("%d\n",ans);
	return 0;
}
