#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int Sr,Sb,Sg,m,mo,n,a[65],S[65],f[22][22][22];
bool vis[65];
int calc()
{
	memset(vis,0,sizeof(vis));
	memset(f,0,sizeof(f));
	memset(S,0,sizeof(S));
	int cnt=0;
	for (int i=1;i<=n;i++)
	if (!vis[i])
	{
		cnt++;
		for (int j=i;!vis[j];j=a[j]) S[cnt]++,vis[j]=1;
	}
	f[0][0][0]=1;
	for (int i=1;i<=cnt;i++)
		for (int r=Sr;r>=0;r--)
			for (int b=Sb;b>=0;b--)
				for (int g=Sg;g>=0;g--)
				{
					if (r>=S[i]) (f[r][b][g]+=f[r-S[i]][b][g])%=mo;
					if (b>=S[i]) (f[r][b][g]+=f[r][b-S[i]][g])%=mo;
					if (g>=S[i]) (f[r][b][g]+=f[r][b][g-S[i]])%=mo;
				}
	return f[Sr][Sb][Sg];
}
int mi(int x,int y)
{
	int ans=1;
	while (y)
	{
		if (y&1) ans=ans*x%mo;
		x=x*x%mo;
		y>>=1;
	}
	return ans;
}
int main()
{
	scanf("%d%d%d%d%d",&Sr,&Sb,&Sg,&m,&mo);
	n=Sr+Sb+Sg;
	int ans=0;
	for (int i=1;i<=m;i++)
	{
		for (int j=1;j<=n;j++) scanf("%d",&a[j]);
		(ans+=calc())%=mo;
	}
	for (int i=1;i<=n;i++) a[i]=i;
	(ans+=calc())%=mo;
	ans=ans*mi(m+1,mo-2)%mo;
	printf("%d\n",ans);
	return 0; 
}
