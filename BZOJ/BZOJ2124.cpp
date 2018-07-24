#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const int base=2333,mo=998244353;
int T,n;
ll bin[10020];
inline int lowbit(int x) { return x&(-x);}
struct BIT
{
	ll f[10020];
	void clear() { memset(f,0,sizeof(f));}
	void add(int x)
	{
		for (int i=x;i<=n;i+=lowbit(i)) f[i]=(f[i]+bin[i-x])%mo;
	}
	ll get(int x)
	{
		ll ans=0;
		for (int i=x;i>=1;i-=lowbit(i)) ans=(ans+f[i]*bin[x-i]%mo)%mo;
		return ans;
	}
	ll query(int x,int y)
	{
		ll X=get(x-1),Y=get(y);
		return (Y-X*bin[y-x+1]%mo+mo)%mo;
	}
}A,B;
int main()
{
	scanf("%d",&T);	
	bin[0]=1;	
	for (int i=1;i<=10000;i++) bin[i]=bin[i-1]*base%mo;
	while (T--)
	{
		scanf("%d",&n);
		bool flag=0;
		A.clear();B.clear();
		for (int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			int Min=min(x,n-x+1);
			A.add(x);
			B.add(n-x+1);
			if (Min&&A.query(x-Min+1,x)!=B.query(n-x-Min+2,n-x+1)) flag=1;
		}
		if (flag) puts("Y");else puts("N");
	}
	return 0;
}
