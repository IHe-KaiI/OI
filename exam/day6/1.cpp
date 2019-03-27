#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 1000000007
const int N=1000100;
int n,size[N];
ll F[N],inv[N],f[N];
void pre()
{
	F[0]=inv[0]=inv[1]=1;
	for (int i=1;i<=n;i++) F[i]=F[i-1]*i%mo;
	for (int i=2;i<=n;i++) inv[i]=(ll)(mo-mo/i)*inv[mo%i]%mo;
	for (int i=1;i<=n;i++) inv[i]=inv[i]*inv[i-1]%mo;
}
ll C(int x,int y) { return F[x]*inv[y]%mo*inv[x-y]%mo;}
void dfs(int u)
{
	f[u]=size[u]=1;
	if (u*2<=n) { dfs(u*2);size[u]+=size[u*2];}
	if (u*2+1<=n) { dfs(u*2+1);size[u]+=size[u*2+1];}
	if (u*2>n&&u*2+1>n) return;
	if (u*2>n||u*2+1>n) f[u]=f[u*2]+f[u*2+1];
	else
	{
		f[u]=f[u*2]*f[u*2+1]%mo*C(size[u]-1,size[u*2])%mo;
	}
}
int main()
{
	for (n=1;n<=100;n++)
	{//scanf("%d",&n);
	memset(size,0,sizeof(size));
	memset(f,0,sizeof(f));
	pre();
	dfs(1);
	printf("%d %lld\n",n,f[1]);
	}
	return 0;
}

