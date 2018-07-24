#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 1000000007
using namespace std;
int T,K,A,B,a[100],b[100],f[100][2][2];
ll n,m;
ll solve(int len,bool flag1,bool flag2)
{
	if (!len) return 1;
	if (f[len][flag1][flag2]!=-1) return f[len][flag1][flag2];
	int up1=(flag1)?a[len]:K-1,up2=(flag2)?b[len]:K-1;
	ll ans=0;
	for (int i=0;i<=up1;i++)
	{
		if (flag2)
		{
			ans=(ans+solve(len-1,flag1&&(i==up1),0)*min(i+1,up2)%mo)%mo;
			if (up2<=i) ans=(ans+solve(len-1,flag1&&(i==up1),1)%mo)%mo;
		}else
		{
			ans=(ans+solve(len-1,flag1&&(i==up1),0)*min(i+1,up2+1)%mo)%mo;
		}
	}
	f[len][flag1][flag2]=ans;
	return ans;
}
ll calc(ll x,ll y)
{
	x++;y++;
	x%=mo;y%=mo;
	return (x*(x+1)/2%mo-(x-y)*(x-y+1)/2%mo+mo)%mo;
}
int main()
{
	scanf("%d%d",&T,&K);
	while (T--)
	{
		A=B=0;
		scanf("%lld%lld",&n,&m);
		if (m>n) m=n;
		ll Ans=calc(n,m);
		while (n) a[++A]=n%K,n/=K;
		memset(b,0,sizeof(b));
		while (m) b[++B]=m%K,m/=K;
		memset(f,-1,sizeof(f));
		printf("%lld\n",(Ans-solve(A,1,1)+mo)%mo);
	}
	return 0;
}
