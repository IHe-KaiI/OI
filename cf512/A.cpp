#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
ll n,m,K;
ll GCD(ll x,ll y) { return (!y)?x:GCD(y,x%y);}
int main()
{
	scanf("%I64d%I64d%I64d",&n,&m,&K);
	ll gcd=GCD(n*m,K),lastn=n;
	if (K>gcd*2) { puts("NO");return 0;}
	puts("YES");
	gcd=GCD(n,K);
	n/=gcd;K/=gcd;
	gcd=GCD(m,K);
	m/=gcd;K/=gcd;
	puts("0 0");
	if (K==1)
	{
		if (n*2<=lastn) printf("%I64d 0\n",n*2),printf("0 %I64d\n",m);
			else printf("%I64d 0\n",n),printf("0 %I64d\n",m*2);
		return 0;
	}
	printf("%I64d 0\n",n);
	printf("0 %I64d\n",m);
	return 0;
}
