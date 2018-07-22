#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
ll ex_gcd(ll a,ll b,ll &x,ll &y)
{
	if (!b) { x=1;y=0;return a;}
	ll gcd=ex_gcd(b,a%b,x,y),t;
	t=x;x=y;y=t-a/b*y;
	return gcd;
}
pair<ll,ll> AX_equalBmodP(ll a,ll b,ll p)//return (d,k) -> X=d+k*t
{
	a=(a%p+p)%p;b=(b%p+p)%p;
	ll gcd=ex_gcd(a,b,X,Y),P=p;
	if (b%gcd!=0) return -1;
	a/=gcd;p/=gcd;b/=gcd;
	ex_gcd(a,b,X,Y);
	return make_pair(b*X,b*p%P);
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%lld%lld%lld",&a[i],&b[i],&p[i]);

	return 0;
}
