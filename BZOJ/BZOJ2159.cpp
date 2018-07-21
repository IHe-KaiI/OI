#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 10007
using namespace std;
int n,K,L,now,A,B,Q,tot,Next[100010],head[50010],tree[100010],f[50010][160],S[160][160],fac[160];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs(int u,int fa)
{
	f[u][0]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa) continue;
		dfs(v,u);
		f[u][0]+=f[v][0];
		for (int j=1;j<=K;j++) (f[u][j]+=(f[v][j]+f[v][j-1])%mo)%=mo;
	}
}
void dfs1(int u,int fa)
{
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa) continue;
		for (int j=K;j>=1;j--)
		{
			(f[v][j]+=(f[u][j]+f[u][j-1]-f[v][j]-f[v][j-1]-f[v][j-1]-((j>1)?f[v][j-2]:0))%mo+mo)%=mo;
		}
		(f[v][0]+=f[u][0]-f[v][0]+mo)%=mo;
		dfs1(v,u);
	}
}
void pre()
{
	S[0][0]=1;fac[0]=1;
	for (int i=1;i<=K;i++)
	{
		fac[i]=fac[i-1]*i%mo;
		for (int j=1;j<=i;j++) S[i][j]=(S[i-1][j-1]+S[i-1][j]*j%mo)%mo;
	}
}
int main()
{
	scanf("%d%d%d%d%d%d%d",&n,&K,&L,&now,&A,&B,&Q);
	for (int i=1;i<=n-1;i++)
	{
		now=(now*A+B)%Q;
		int x=i-now%min(i,L),y=i+1;
		add(x,y);add(y,x);
	}
	pre();
	dfs(1,0);
	dfs1(1,0);
	for (int i=1;i<=n;i++)
	{
		int ans=0;
		for (int j=0;j<=K;j++)
			(ans+=f[i][j]*S[K][j]%mo*fac[j]%mo)%=mo;
		printf("%d\n",ans);
	}
	return 0;
}
