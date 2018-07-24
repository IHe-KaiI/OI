#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,cnt,f[200100],p[200100];
struct node{int u,v,x;}E[100010];
bool cmp(node a,node b) { return a.x<b.x;}
int get(int x)
{
	if (f[x]==x) return x;else f[x]=get(f[x]);
	return f[x];
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			int x;
			scanf("%d",&x);
			E[++cnt]=(node){i,n+j,x};
		}
	sort(E+1,E+cnt+1,cmp);
	for (int i=1;i<=n+m;i++) f[i]=i;
	long long ans=0;
	for (int i=1;i<=cnt;i++)
	{
		int x=get(E[i].u),y=get(E[i].v);
		if (p[x]&&p[y]) continue;
		if (x!=y)
		{
			f[x]=y;
			p[y]|=p[x];
			ans+=E[i].x;
		}else
		{
			p[x]=1;
			ans+=E[i].x;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
