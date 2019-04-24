#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#define ll long long
#define G 3
#define mo 998244353
using namespace std;
const int N=8010,M=5010;
int n,m,T,tot,Next[M*2],head[M],tree[M*2],f[2][N],fail[N],delta[N],ans[N],K,MOD[N];
vector<int>A,B;
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
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
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
void Add(int &x,int y) { x+=y;if (x>=mo) x-=mo;}
vector<int> BM(vector<int> &A)
{
	vector<int> B,S;
	int best=0,cnt=0;
	for (int i=0;i<(int)A.size();i++)
	{
		ll x=A[i];
		for (int j=0;j<(int)B.size();j++)
			x=(x-(ll)B[j]*A[i-j-1]%mo+mo)%mo;
		delta[i]=x;
		if (!x) continue;
		fail[cnt++]=i;
		if (B.empty())
		{
			B.resize(i+1);
			best=cnt-1;
			continue;
		}
		ll k=x*mi(delta[fail[best]],mo-2)%mo;
		vector<int> C;
		C.resize(i-fail[best]-1);
		C.push_back(k);
		for (int j=0;j<(int)S.size();j++)
			C.push_back((mo-k*S[j]%mo)%mo);
		if (C.size()<B.size()) C.resize(B.size());
		for (int j=0;j<(int)B.size();j++)
			C[j]=(C[j]+B[j])%mo;
		if (B.size()<=i-fail[best]+S.size()) best=cnt-1,S=B;
		B=C;
	}
	return B;
}
void DP()
{
	f[0][1]=1;
	int sum=1,now=0;
	for (int t=1;t<=n+n+5;t++)
	{
		now^=1;
		for (int i=1;i<=n;i++) f[now][i]=f[now^1][i];
		for (int i=1;i<=n;i++)
			for (int j=head[i];j;j=Next[j])
			{
				int v=tree[j];
				Add(f[now][v],f[now^1][i]);
			}
		for (int i=1;i<=n;i++) Add(sum,f[now][i]);
		A.push_back(sum);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	scanf("%d",&T);
	T--;
	DP();
	if (T<=n+n+5) { printf("%d\n",A[T]);return 0;}
	B=BM(A);
	K=B.size();
	for (int i=0;i<K;i++) MOD[i]=mo-B[K-1-i];
	poly::mi(ans,T);
	int Ans=0;
	for (int i=0;i<K;i++) Add(Ans,(ll)ans[i]*A[i]%mo);
	printf("%d\n",Ans);
	return 0;
}
