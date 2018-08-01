#include<iostream>
#include<cstdio>
#define ll long long
#define mo 998244353
using namespace std;
const int N=10000010;
int L,R,n,f[N],Min[N],prime[N],num[N],Q[N];
ll K,sum[N];
bool flag[N];
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
ll calc(int x,int y)
{
	if (K%x==0) return (mi(y+1,n)-mi(y,n)+mo)%mo;
		else return mi(y+1,n);
}
int main()
{
	scanf("%d%d%d%lld",&L,&R,&n,&K);
	f[1]=1;
	int cnt=0;
	for (int i=2;i<=R;i++)
	{
		if (!flag[i])
		{
			prime[++cnt]=i;
			f[i]=calc(i,1);
			Min[i]=i;
			num[i]=1;
			Q[i]=i;
		}
		for (int j=1;j<=cnt;j++)
		{
			if (prime[j]*i>R) break;
			int k=i*prime[j];
			flag[k]=1;
			if (i%prime[j])
			{
				f[k]=f[i]*f[prime[j]];
				if (Min[i]<prime[j]) Min[k]=Min[i],num[k]=num[i],Q[k]=Q[i];
					else Min[k]=prime[j],num[k]=1,Q[k]=prime[j];	
			}
			else
			{
				Min[k]=Min[i];
				Q[k]=Q[i];
				num[k]=num[i];
				if (Min[i]==prime[j]) num[k]++,Q[k]*=prime[j];	
				f[k]=calc(Min[k],num[k])*f[k/Q[k]]%mo;
			}
		}
		sum[i]=(sum[i-1]+f[i])%mo;
	}
	printf("%lld\n",(sum[R]-sum[L-1]+mo)%mo);
	return 0;
}
