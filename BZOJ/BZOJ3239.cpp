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
	for (int i=1;i<=m+1;i++)
	{
		if (M[y*X%P]) return i*m-M[y*X%P];
		y=y*x%P;
	}
	return -1;
}
int main()
{
	while (scanf("%lld%lld%lld",&P,&A,&B)!=EOF)
	{
		ll ans=BSGS(A,1,B,P);
		if (ans==-1) puts("no solution");
			else printf("%lld\n",ans);
	}
	return 0;
}
