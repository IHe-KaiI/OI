#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 1000000007
#define inv 500000004
using namespace std;
bool flag[50010];
int prime[50010],tot,n,m,L,a[300010],ans[300010];
void pre()
{
	for (int i=2;i<=50000;i++)
	{
		if (!flag[i]) prime[++tot]=i;
		for (int j=1;j<=tot;j++)
		{
			if (i*prime[j]>50000) break;
			flag[i*prime[j]]=1;
			if (i%prime[j]==0) break;
		}
	}
}
void FWT(int *a)
{
	for (int len=2;len<=L;len<<=1)
		for (int j=0,l=len>>1;j<L;j+=len)
			for (int k=0;k<l;k++)
			{
				int x=a[j+k],y=a[j+k+l];
				a[j+k]=(x+y)%mo;
				a[j+k+l]=(x-y+mo)%mo;
			}
}
void UFWT(int *a)
{
	for (int len=2;len<=L;len<<=1)
		for (int j=0,l=len>>1;j<L;j+=len)
			for (int k=0;k<l;k++)
			{
				int x=a[j+k],y=a[j+k+l];
				a[j+k]=(ll)(x+y)*inv%mo;
				a[j+k+l]=(ll)(x-y+mo)*inv%mo;
			}
}
void mi(int *x,int y)
{
	memset(ans,0,sizeof(ans));
	ans[0]=1;
	FWT(x);FWT(ans);
	while (y)
	{
		if (y&1)
		{
			for (int i=0;i<L;i++) ans[i]=(ll)ans[i]*x[i]%mo;
		}
		for (int i=0;i<L;i++) x[i]=(ll)x[i]*x[i]%mo;
		y>>=1;
	}
	UFWT(ans);
}
int main()
{
	pre();
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		L=1;
		while (L<=m) L<<=1;
		memset(a,0,sizeof(a));
		for (int i=1;i<=tot&&prime[i]<=m;i++) a[prime[i]]=1;
		mi(a,n);
		printf("%d\n",ans[0]);
	}
	return 0;
}
