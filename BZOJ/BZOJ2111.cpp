#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
int n,mo,num[2000100];
ll f[1000100],inv[1000100];
ll C(int n,int m) { return f[m]*inv[n]%mo*inv[m-n]%mo;}
ll lucas(int n,int m)
{
	if (n>m) return 0;
	if (m<mo) return C(n,m);
	return lucas(n/mo,m/mo)*lucas(n%mo,m%mo)%mo;
}
ll dfs(int u)
{
	if (u>n) return 1;
	num[u]=1;
	ll ans=dfs(u<<1)*dfs(u<<1|1)%mo;
	num[u]+=(((u<<1)>n)?0:num[u<<1])+(((u<<1|1)>n)?0:num[u<<1|1]);
	return ans*lucas(num[u<<1],num[u]-1)%mo;
}
int main()
{
	scanf("%d%d",&n,&mo);
	f[0]=inv[0]=inv[1]=1;
	for (int i=1;i<=min(n,mo);i++) f[i]=f[i-1]*i%mo;
	for (int i=2;i<=min(n,mo);i++) inv[i]=(ll)(mo-mo/i)*inv[mo%i]%mo;
	for (int i=2;i<=min(n,mo);i++) inv[i]=inv[i]*inv[i-1]%mo;	
	printf("%lld\n",dfs(1));
	return 0;
}
