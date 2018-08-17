#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
ll n,K,ans;
int main()
{
	scanf("%lld%lld",&n,&K);
	ll x=max(1LL,K-n),y=min(n,K-1),ans=max(0LL,y-x+1);
	if (K%2==0&&K/2<=n) ans--;
	printf("%lld\n",ans>>1);
	return 0;
}

