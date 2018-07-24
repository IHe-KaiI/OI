#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int prime[8]={2,3,5,7,11,13,17,19};
int n,mo,f[260][260],g[2][260][260];
struct node{int x,y;}a[510];
bool cmp(node a,node b) { return a.y<b.y;}
void Add(int &x,int y) { x+=y;if (x>=mo) x-=mo;}
int main()
{
	scanf("%d%d",&n,&mo);
	for (int i=2;i<=n;i++)
	{
		int x=i,j=0;
		while (x!=1&&j<8)
		{
			if (x%prime[j]==0)
			{
				while (x%prime[j]==0) x/=prime[j];
				a[i].x|=1<<j;
			}
			j++;
		}
		a[i].y=x;
	}
	sort(a+1,a+n+1,cmp);
	f[0][0]=g[0][0][0]=g[1][0][0]=1;
	for (int i=2;i<=n+1;i++)
	{
		if (i==2||i==n+1||a[i].y!=a[i-1].y||a[i].y==1)
		{
			for (int j=(1<<8)-1;j>=0;j--)
				for (int k=(1<<8)-1;k>=0;k--)
				if (!(j&k)) f[j][k]=((g[0][j][k]+g[1][j][k]-f[j][k])%mo+mo)%mo;
			if (i==n+1) break;
			memcpy(g[0],f,sizeof(f));
			memcpy(g[1],f,sizeof(f));
		}
		for (int j=(1<<8)-1;j>=0;j--)
			for (int k=(1<<8)-1;k>=0;k--)
			if (!(j&k))
			{
				Add(g[0][j|a[i].x][k],g[0][j][k]);
				Add(g[1][j][k|a[i].x],g[1][j][k]);
			}
	}
	int ans=0;
	for (int i=(1<<8)-1;i>=0;i--)
		for (int j=(1<<8)-1;j>=0;j--) if (!(i&j)) Add(ans,f[i][j]);
	printf("%d\n",ans);
	return 0;
}
