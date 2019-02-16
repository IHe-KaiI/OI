#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<set>
#include<map>
#define mo 1000000007
#define ll long long
using namespace std;
int n,m,Q;
multiset<int>S;
map<int,int>M;
int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
ll mi(ll x,ll y)
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
int main()
{
	freopen("price.in","r",stdin);
	freopen("price.out","w",stdout);
	scanf("%d%d%d",&n,&m,&Q);
	while (Q--)
	{
		int op=read();
		if (op==1)
		{
			int x=read(),y=read();
			y=m-y;
			M[y]^=1;
			if (M[y]) S.insert(y);
				else S.erase(y);
		}else
		{
			if (S.empty()) puts("-1");
				else printf("%lld\n",mi(2,(*S.begin())));
		}
	}
	return 0;
}
