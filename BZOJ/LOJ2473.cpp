#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 64123
#define ll long long
using namespace std;
const int N=2000;
int n,K,W,a[N],tot,Next[N<<1],head[N],tree[N<<1],f[N][N],U,ans;
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs(int u,int fa,int *g)
{
	bool flag=(a[u]>a[U]||(a[u]==a[U]&&u>U));
	for (int i=1;i<=K;i++) f[u][i]=g[i-flag];
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa) continue;
		dfs(v,u,f[u]);
	}
	for (int i=1;i<=K;i++) (g[i]+=f[u][i])%=mo;
}
void solve(int u)
{
	int num=0;
	for (int i=1;i<=n;i++)
		if (a[i]>a[u]||(a[i]==a[u]&&i>=u)) num++;
	if (num<K) return;
	memset(f[u],0,sizeof(f[u]));
	f[u][1]=1;
	U=u;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		dfs(v,u,f[u]);
	}
	ans=((ll)a[u]*f[u][K]%mo+ans)%mo;
}
int main()
{
	scanf("%d%d%d",&n,&K,&W);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	ans=0;
	for (int i=1;i<=n;i++) solve(i);
	printf("%d\n",ans);
	return 0;
}
