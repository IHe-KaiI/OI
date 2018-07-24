#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<map>
#define ll long long
using namespace std;
ll A,B,P;
map<int,int>M;
ll gcd(ll a,ll b) { return (!b)?a:gcd(b,a%b);}
ll BSGS(ll A,ll X,ll B,ll P)
{
	ll m=ceil(sqrt(P)),y=1;
	M.clear();
	for (int i=0;i<=m;i++)
	{
		M[y*B%P]=i;
		if (i!=m) y=y*A%P;
	}
	ll x=y;
	for (int i=1;i<=m;i++)
	{
		if (M[y*X%P]) return i*m-M[y*X%P];
		y=y*x%P;
	}
	return -1;
}
ll EXBSGS(ll A,ll B,ll P)
{
	if (B==1) return 0;
	ll t=B;int cnt=0;
	while (1)
	{
		ll GCD=gcd(A,P);
		if (GCD==1) break;
		if (t%GCD) return -1;
		t/=GCD;P/=GCD;
		cnt++;
	}
	ll x=1;
	for (int i=1;i<=cnt;i++)
	{
		if (x%P==B) return i;
		x=x*A%P;
	}
	ll ans=BSGS(A,x,B,P);
	if (ans==-1) return -1;
	return ans+cnt;
}
int main()
{
	while (1)
	{
		scanf("%lld%lld%lld",&A,&P,&B);
		if (!A&&!B&&!P) break;
		ll ans=EXBSGS(A%P,B%P,P);
		if (ans==-1) puts("No Solution");
			else printf("%lld\n",ans);
	}
	return 0;
}
