#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#define ll long long
const int N=1000100;
using namespace std;
int n,a[N],b[N],A[N],Max[N];
ll f[N],g[N];
priority_queue<pair<int,int> >Q;
inline int lowbit(int x) { return x&(-x);}
void add(int x,ll y)
{
	for (int i=x;i<=n;i+=lowbit(i)) g[i]=max(g[i],y);
}
ll query(int x)
{
	ll ans=0;
	for (int i=x;i>=1;i-=lowbit(i)) ans=max(ans,g[i]);
	return ans;
}
int main()
{
	freopen("fc.in","r",stdin);
	freopen("fc.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) { scanf("%d",&a[i]);A[i]=i+a[i];}
	for (int i=1;i<=n;i++) scanf("%d",&b[i]);
	for (int i=1;i<=n;i++)
	{
		while (!Q.empty()&&Q.top().first>=-i)
		{
			int u=Q.top().second;
			Q.pop();
			add(u,f[u]);
		}
		f[i]=max((ll)a[i]*b[i],query(i-a[i])+(ll)a[i]*b[i]);
		Q.push(make_pair(-i-a[i],i));
	}
	ll ans=0;
	for (int i=1;i<=n;i++) ans=max(ans,f[i]);
	printf("%lld\n",ans);
	return 0;
}
