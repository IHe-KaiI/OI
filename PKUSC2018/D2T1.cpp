#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=300010;
int n,a[N],f[N][22],g[N][22],Q;
void pre()
{
	int Min=1<<29;
	for (int i=n;i>=1;i--)
	{
		Min=min(Min,a[i]);
		f[i][0]=i-Min;
		g[i][0]=Min;
	}
	for (int j=1;j<=20;j++)
		for (int i=1;i<=n;i++)
		{
			f[i][j]=f[i][j-1]+f[g[i][j-1]][j-1]+(g[i][j-1]-g[g[i][j-1]][j-1])*(1<<(j-1));
			g[i][j]=g[g[i][j-1]][j-1];
		}
}
int query(int x,int pos)
{
	if (x>pos) return 0;
	int ans=pos-max(x,a[pos]),tot=1;
	pos=a[pos];
	for (int i=20;i>=0;i--)
		if (g[pos][i]>x) ans+=f[pos][i]+(pos-g[pos][i])*tot,pos=g[pos][i],tot+=1<<i;
	return ans+max(0,(pos-x))*(tot+1);
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<n;i++) scanf("%d",&a[i+1]);
	pre();
	scanf("%d",&Q);
	while (Q--)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		int ansx=query(x,z)-query(y+1,z),ansy=y-x+1;
		int Gcd=__gcd(ansx,ansy);
		printf("%d/%d\n",ansx/Gcd,ansy/Gcd);
	}
	return 0;
}
