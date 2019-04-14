#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 998244353
#define ll long long
#define G 3
using namespace std;
const int N=4010;
int n,K,a[N],h[N],MOD[N],f[N],ans[N],c[N];
inline void Add(int &a,int b) { a+=b;if (a>=mo) a-=mo;}
namespace poly
{
	int n,m,a[N],b[N],w[N],L,INV;
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
	void NTT(int *A,int f)
	{
		for (int i=0,j=0;i<L;i++)
		{
			if (i>j) swap(A[i],A[j]);
			for (int k=L>>1;(j^=k)<k;k>>=1);
		}
		for (int len=2;len<=L;len<<=1)
		{
			int l=len>>1;
			int W=mi(G,(mo-1)/len);
			for (int i=1;i<l;i++) w[i]=(ll)w[i-1]*W%mo;
			for (int i=0;i<L;i+=len)
				for (int j=0;j<l;j++)
				{
					int x=A[i+j],y=(ll)A[i+j+l]*w[j]%mo;
					A[i+j]=(x+y)%mo;
					A[i+j+l]=(x-y+mo)%mo;
				}
		}
		if (f==-1)
		{
			for (int i=1;i<L/2;i++) swap(A[i],A[L-i]);
			for (int i=0;i<L;i++) A[i]=(ll)A[i]*INV%mo;
		}
	}
	void pre(int l)
	{
		L=1;
		while (L<l) L<<=1;
		INV=mi(L,mo-2);
		w[0]=1;
	}
	void Get_INV(int *A,int n,int *B)
	{
		if (n==1) { B[0]=mi(A[0],mo-2);return;}
		Get_INV(A,n>>1,B);
		pre(n*2);
		static int C[N];
		for (int i=0;i<L;i++) C[i]=0;
		for (int i=0;i<n;i++) C[i]=A[i];
		NTT(C,1);NTT(B,1);
		for (int i=0;i<L;i++) B[i]=((B[i]+B[i])%mo-(ll)C[i]*B[i]%mo*B[i]%mo+mo)%mo;
		NTT(B,-1);
		for (int i=n;i<L;i++) B[i]=0;
	}
	void Calc_INV(int *A,int n,int *B)
	{
		ll X=1;
		while (X<=n) X<<=1;
		Get_INV(A,X,B);
	}
	void mul(int *A,int *B,int *C,int l)
	{
		pre(l);
		NTT(A,1);NTT(B,1);
		for (int i=0;i<L;i++) C[i]=(ll)A[i]*B[i]%mo;
		NTT(B,-1);NTT(C,-1);
	}
	void division(int *A,int *B,int n,int m,int *Ans)
	{
		reverse(A,A+n);
		reverse(B,B+m);
		static int C[N];
		Calc_INV(B,n-m+1,C);
		mul(C,A,C,n+n);
		for (int i=n-m+1;i<L;i++) C[i]=0;
		reverse(C,C+n-m+1);
		pre(n+n);
		reverse(A,A+n);
		reverse(B,B+m);
		NTT(B,1);NTT(C,1);
		for (int i=0;i<L;i++) B[i]=(ll)B[i]*C[i]%mo;
		NTT(B,-1);
		for (int i=0;i<m-1;i++) Ans[i]=(A[i]-B[i]+mo)%mo;
		for (int i=0;i<L;i++) A[i]=B[i]=C[i]=0;
	}
	void mul(int *A,int *B)
	{
		static int a[N],b[N],Mod[N];
		for (int i=0;i<=K;i++) a[i]=A[i],b[i]=B[i],Mod[i]=MOD[i]; 
		mul(a,b,a,K+K+1);
		division(a,Mod,K+K+1,K+1,A);
	}
	void mi(int *ans,int y)
	{
		static int f[N];
		ans[0]=1;f[1]=1;
		while (y)
		{
			if (y&1) mul(ans,f);
			mul(f,f);
			y>>=1;
		}
	}
}
int main()
{
    scanf("%d%d",&n,&K);
    for (int i=1;i<=K;i++) scanf("%d",&a[i]),a[i]=(a[i]%mo+mo)%mo;
    for (int i=0;i<K;i++) scanf("%d",&h[i]),h[i]=(h[i]%mo+mo)%mo;
    if (n<K) { printf("%d\n",h[n]);return 0;}
    for (int i=0;i<K;i++) MOD[i]=(-a[K-i]%mo+mo)%mo;
    MOD[K]=1;
    f[1]=1;ans[0]=1;
    poly::mi(ans,n);
    int Ans=0;
    for (int i=0;i<K;i++) Add(Ans,(ll)ans[i]*h[i]%mo);
    printf("%d\n",Ans);
    return 0;
}
