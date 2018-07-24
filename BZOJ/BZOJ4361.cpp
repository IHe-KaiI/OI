#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 1000000007
#define ll long long
using namespace std;
const int N=2010;
int n,tot;
ll a[N],A[N],f[N][N],g[N],F[N];
struct node
{
	ll f[N];
	inline int lowbit(int x) { return x&(-x);}
	ll query(int x)
	{
		ll ans=0;
		for (int i=x;i>=1;i-=lowbit(i)) (ans+=f[i])%=mo;
		return ans;
	}
	void add(int x,int y)
	{
		for (int i=x;i<=tot;i+=lowbit(i)) (f[i]+=y)%=mo;
	}
}BIT[N];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) { scanf("%lld",&a[i]);A[i]=a[i];}
	sort(A+1,A+n+1);
	tot=unique(A+1,A+n+1)-A-1;
	for (int i=1;i<=n;i++) a[i]=lower_bound(A+1,A+tot+1,a[i])-A+1;
	tot++;
	BIT[0].add(1,1);
	for (int i=1;i<=n;i++)
		for (int j=i;j>=1;j--)
		{
			f[i][j]=BIT[j-1].query(a[i]);
			BIT[j].add(a[i],f[i][j]);
			(g[j]+=f[i][j])%=mo;
		}
	F[0]=1;
	for (int i=1;i<=n;i++) F[i]=F[i-1]*i%mo;
	ll ans=0;
	for (int i=1;i<=n;i++)
		(ans+=g[i]*F[n-i]%mo-((i!=n)?g[i+1]*F[n-i-1]%mo*(i+1)%mo:0))%=mo;
	printf("%lld\n",(ans+mo)%mo);
	return 0;
}
