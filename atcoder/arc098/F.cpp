#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=100100;
int n,m,a[N],b[N],tot,Next[N<<1],head[N],tree[N<<1],f[N];
ll ans[N],g[N];
bool vis[N];
struct node{int x,y;}A[N];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
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
	{
		scanf("%d%d",&a[i],&b[i]);
		a[i]=max(0,a[i]-b[i]);
		A[i]=(node){a[i],i};
	}
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	sort(A+1,A+n+1,cmp);
	for (int i=1;i<=n;i++)
	{
		f[i]=i;
		ans[i]=a[i];
		g[i]=b[i];
	}
	for (int i=1;i<=n;i++)
	{
		int u=A[i].y;
		vis[u]=1;
		for (int j=head[u];j;j=Next[j])
		{
			int v=tree[j],x=get(v);
			if (x==u||!vis[x]) continue;
			f[x]=u;
			g[u]+=g[x];
			ans[u]=min(ans[u],max(ans[x],a[u]-g[x]));
		}
	}
	printf("%lld\n",ans[A[n].y]+g[A[n].y]);
	return 0;
}
