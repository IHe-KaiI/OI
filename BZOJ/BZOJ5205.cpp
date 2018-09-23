#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 1000000007
using namespace std;
const int N=17;
int n,m,p[N][N],f[2][N][N][1<<N],rev[1<<N];
inline void Add(int &x,int y) { x+=y;if (x>=mo) x-=mo;}
void dp(int o)
{
	int X=(1<<m)-1;
	f[o][0][0][X]=1;
	f[o][0][0][X-1]=!p[0][0];
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			if (i==0&&j==0) continue;
			int x=(!j)?i-1:i,y=(!j)?m-1:j-1;
			for (int sta=0;sta<(1<<m);sta++)
			if (f[o][x][y][sta])
			{
				if (p[i][j])
				{
					if (sta&(1<<(m-1)))
					{
						Add(f[o][i][j][((sta<<1)&X)|1],f[o][x][y][sta]);
					}
				}else
				{
					Add(f[o][i][j][((sta<<1)&X)|1],f[o][x][y][sta]);
					if (sta&(1<<(m-1)))
					{
						Add(f[o][i][j][(sta<<1)&X],f[o][x][y][sta]);
						if (j&&!(sta&1))
							Add(f[o][i][j][((sta<<1)&X)|3],f[o][x][y][sta]);
					}
				}
			}
		}
}
inline void reserve()
{
	for (int i=0;i<n/2;i++)
		for (int j=0;j<m;j++) swap(p[i][j],p[n-i-1][j]);
	for (int i=0;i<n;i++)
		for (int j=0;j<m/2;j++) swap(p[i][j],p[i][m-j-1]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++) scanf("%d",&p[i][j]);
	dp(0);
	reserve();
	dp(1);
	reserve();
	for (int i=0;i<(1<<m)-1;i++) rev[i]=rev[i>>1]>>1|((i&1)*(1<<(m-1)));
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			if (!p[i][j])
			{
				int ans=0;
				for (int sta=0;sta<(1<<m)-1;sta+=2)
					Add(ans,(long long)f[0][i][j][sta]*f[1][n-i-1][m-j-1][rev[sta]<<1]%mo);
				printf("%d",ans);
			}else printf("0");
			if (j==m-1) puts("");
				else printf(" ");
		}
	return 0;
}
