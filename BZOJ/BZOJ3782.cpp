#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
ll n,m,f[1000005][4],inv[1000005][4],G[4],INV[4],Ans[250];
int T,P,num,p[4];
struct node{ll x,y;}a[250];
ll C(int n,int m,int mo,int i) { return f[m][i]*inv[n][i]%mo*inv[m-n][i]%mo;}
ll lucas(ll n,ll m,int mo,int i)
{
	if (n>m) return 0;
	if (m<mo) return C(n,m,mo,i);
	return C(n%mo,m%mo,mo,i)*lucas(n/mo,m/mo,mo,i);
}
ll mi(ll x,int y,int mo)
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
ll Get_C(ll n,ll m)
{
	if (num==1) return lucas(n,m,p[0],0);
	ll ans=0;
	for (int i=0;i<num;i++)
		(ans+=lucas(n,m,p[i],i)*G[i]%P*INV[i]%P)%=P;
	return ans;
}
bool cmp(node a,node b) { return (a.x==b.x)?a.y<b.y:a.x<b.x;}
int main()
{
	scanf("%lld%lld%d%d",&n,&m,&T,&P);
	if (P==1000003) num=1,p[0]=P;
	else
	{
		num=4;
		p[0]=3;p[1]=5;p[2]=6793;p[3]=10007;
		for (int i=0;i<4;i++) G[i]=P/p[i],INV[i]=mi(G[i],p[i]-2,p[i]);
	}
	for (int i=0;i<num;i++)
	{
		f[0][i]=inv[0][i]=inv[1][i]=1;
		for (int j=1;j<=p[i];j++) f[j][i]=f[j-1][i]*j%p[i];
		for (int j=2;j<=p[i];j++) inv[j][i]=(ll)(p[i]-p[i]/j)*inv[p[i]%j][i]%p[i];
		for (int j=2;j<=p[i];j++) (inv[j][i]*=inv[j-1][i])%=p[i];
	}
	for (int i=1;i<=T;i++) scanf("%lld%lld",&a[i].x,&a[i].y);
	ll ans=Get_C(n,n+m);
	sort(a+1,a+T+1,cmp);
	for (int i=1;i<=T;i++)
	{
		Ans[i]=Get_C(a[i].x,a[i].x+a[i].y);
		for (int j=1;j<i;j++)
			(Ans[i]-=Get_C(a[i].x-a[j].x,a[i].x-a[j].x+a[i].y-a[j].y)*Ans[j]%P)%=P;
		(ans-=Ans[i]*Get_C(n-a[i].x,n+m-a[i].x-a[i].y))%=P;
	}
	printf("%lld\n",(ans+P)%P);
	return 0;
}
