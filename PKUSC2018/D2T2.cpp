#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 998244353
#define G 3
using namespace std;
const int N=500010;
char s[N];
ll a[N*3],b[N*3];
int len,p[N];
namespace MUL
{
	int n,m,L,H;
	ll w[N*3],INV;
	ll mi(ll x,int y)
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
	void NTT(ll *a,int f)
	{
		for (int i=0,j=0;i<L;i++)
		{
			if (i>j) swap(a[i],a[j]);
			for (int k=L>>1;(j^=k)<k;k>>=1); 
		}
		for (int len=2;len<=L;len<<=1)
		{
			int l=len>>1;
			ll W=mi(G,(mo-1)/len);
			for (int i=1;i<l;i++) w[i]=w[i-1]*W%mo;
			for (int i=0;i<L;i+=len)
				for (int j=0;j<l;j++)
				{
					ll x=a[i+j],y=w[j]*a[i+j+l]%mo;
					a[i+j]=(x+y>=mo)?x+y-mo:x+y;a[i+j+l]=(x-y<0)?x-y+mo:x-y;
				}
		}
		if (f==-1)
		{
			for (int i=1;i<L/2;i++) swap(a[i],a[L-i]);
			for (int i=0;i<L;i++) a[i]=a[i]*INV%mo;
		}
	}
	void mul()
	{
		n++;m++;
		w[0]=1;
		L=1;H=0;
		while (L<n+m) L<<=1,H++;
		INV=mi(L,mo-2)%mo;
		NTT(a,1);NTT(b,1);
		for (int i=0;i<L;i++) a[i]=a[i]*b[i]%mo;
		NTT(a,-1);
	}
}
int main()
{
	scanf("%s",s+1);
	len=strlen(s+1);
	for (int i=0;i<len;i++)
	{
		a[i]=(s[i+1]=='0');
		b[len-i-1]=(s[i+1]=='1');
	}
	MUL::n=MUL::m=len;
	MUL::mul();
	for (int i=1;i<len+len;i++)
	if (a[i])
	{
		int x=abs(i-len+1);
		p[x]=1;
	}
	ll Ans=(ll)len*len;
	for (int i=1;i<len;i++)
	{
		bool flag=1;
		for (int j=len-i;j<=len;j+=len-i)
			if (p[j]) { flag=0;break;}
		if (flag) Ans=Ans^((ll)i*i);
	}
	printf("%lld\n",Ans);
	return 0;
}
