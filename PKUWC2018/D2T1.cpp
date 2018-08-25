#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 998244353
#define ll long long
using namespace std;
const int N=23;
int n,m,p[N][N],num[1<<N],P[N],f[1<<N],ans[1<<N],C[N][N],F[N];
ll mi(ll x,int y)
{
	ll ans=1;
	while (y)
	{
		if (y&1) ans=ans*x%mo;
		x=x*x%mo;
		y>>=1;
	}
	return ans;
}
void pre()
{
	C[0][0]=1;
	for (int i=1;i<=n;i++)
	{
		C[i][0]=1;
		for (int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mo;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		p[x][y]=p[y][x]=1;
	}
	pre();
	for (int i=1;i<=(1<<n)-1;i++) num[i]=num[i>>1]+(i&1);
	for (int i=1;i<=n;i++)
	{
		P[i]=1<<i-1;
		for (int j=1;j<=n;j++)
			if (p[i][j]) P[i]+=1<<j-1;
	}
	for (int i=0;i<(1<<n)-1;i++)
		for (int j=1;j<=n;j++)
			if (!(i&(1<<j-1))) f[i|P[j]]=max(f[i|P[j]],f[i]+1);
	F[0]=1;
	for (int i=1;i<=n;i++) F[i]=(ll)F[i-1]*i%mo;
	ans[0]=1;
	for (int i=0;i<(1<<n)-1;i++)
	if (ans[i])
	{
		for (int j=1;j<=n;j++)
		if (!(i&(1<<j-1)))
		{
			int x=P[j],y=num[i|x]-num[i]-1;
			if (f[i]+1==f[i|x])
				ans[i|x]=((ll)ans[i]*C[n-num[i]-1][y]%mo*F[y]+ans[i|x])%mo;
		}
	}
	ll Ans=F[n];
	printf("%lld\n",mi(Ans,mo-2)*ans[(1<<n)-1]%mo);
	return 0;
}
