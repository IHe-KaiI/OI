#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=310;
int n,K,mo,C[N][N],f[N][N],sum[N][N];
int main()
{
	scanf("%d%d%d",&n,&K,&mo);
	C[0][0]=1;
	for (int i=1;i<=n;i++)
	{
		C[i][0]=1;
		for (int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mo;
	}
	for (int i=0;i<=K;i++) f[1][i]=1,sum[1][i]=i+1;
	for (int i=2;i<=n+1;i++)
		for (int j=0;j<=K;j++)
		{
			for (int k=1;k<=i-1;k++)
				f[i][j]=(f[i][j]+(ll)f[i-k][j]*C[i-2][k-1]%mo*(sum[k][K]-sum[k][j])%mo)%mo;
			sum[i][j]=(sum[i][j-1]+f[i][j])%mo;
		}
	printf("%d\n",(f[n+1][0]+mo)%mo);
	return 0;
}
