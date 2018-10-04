#include<iostream>
#include<cstdio> 
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=200100;
int n,tot,Next[N*2],head[N],tree[N*2],size[N];
ll A[2],B[2],sum[2],num[2],ans;
bool vis[N];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void Get_Size(int u,int fa)
{
	size[u]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa||vis[v]) continue;
		Get_Size(v,u);
		size[u]+=size[v];
	}
}
int Get_Root(int u,int fa,int All)
{
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa||vis[v]) continue;
		if (size[v]+size[v]>All) return Get_Root(v,u,All);
	}
	return u;
}
void dfs(int u,int fa,int dep)
{
	A[dep&1]++;B[dep&1]+=dep;
	ans+=(dep+1)>>1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (vis[v]||v==fa) continue;
		dfs(v,u,dep+1);	
	}
}
void TDC(int t)
{
	Get_Size(t,0);
	int u=Get_Root(t,0,size[t]);
	vis[u]=1;
	num[0]=num[1]=sum[0]=sum[1]=0;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (vis[v]) continue;
		A[0]=A[1]=B[0]=B[1]=0;
		dfs(v,u,1);
		ans+=B[0]/2*(num[0]+num[1])+sum[0]/2*(A[0]+A[1]);
		ans+=(B[1]+A[1])/2*num[0]+(B[1]-A[1])/2*num[1]+(sum[1]+num[1])/2*A[0]+(sum[1]-num[1])/2*A[1]+A[1]*num[1];
		num[0]+=A[0];num[1]+=A[1];
		sum[0]+=B[0];sum[1]+=B[1];
	}
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (!vis[v]) TDC(v);
	}
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	ans=0;
	TDC(1);
	printf("%lld\n",ans);
	return 0;
}
