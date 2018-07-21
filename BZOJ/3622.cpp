#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 1000000009
using namespace std;
const int N=2010;
int n,k,a[N],b[N],pos[N];
ll f[N][N],F[N],g[N],C[N][N];
int main()
{
	scanf("%d%d",&n,&k);
	k=(n+k)>>1;
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++) scanf("%d",&b[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for (int i=1;i<=n;i++) pos[i]=lower_bound(b+1,b+n+1,a[i])-b-1;
	f[0][0]=1;
	for (int i=1;i<=n;i++)
	{
		f[i][0]=1;
		for (int j=1;j<=i;j++) f[i][j]=(f[i-1][j]+f[i-1][j-1]*max(0,pos[i]-j+1))%mo;
	}
	F[0]=1;
	for (int i=1;i<=n;i++) F[i]=F[i-1]*i%mo;
	for (int i=k;i<=n;i++) g[i]=f[n][i]*F[n-i]%mo;
	C[0][0]=1;
	for (int i=1;i<=n;i++)
	{
		C[i][0]=1;
		for (int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mo;
	}
	ll ans=0;
	for (int i=k;i<=n;i++) (ans+=(ll)((i-k&1)?-1:1)*g[i]*C[i][k]%mo)%=mo;
	printf("%lld\n",(ans+mo)%mo);
	return 0;
}
