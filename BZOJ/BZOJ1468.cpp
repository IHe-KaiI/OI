#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=40010;
int n,tot,Next[N*2],head[N],tree[N*2],val[N*2],k,root,sum,ans,f[N],son[N],d[N],num,a[N];
bool visit[N];
void add(int x,int y,int z)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
	val[tot]=z;
}
void getroot(int u,int fa)
{
	son[u]=1;f[u]=0;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v!=fa&&!visit[v])	
		{
			getroot(v,u);
			son[u]+=son[v];
			f[u]=max(f[u],son[v]);
		}
	}
	f[u]=max(f[u],sum-son[u]);
	if (f[u]<f[root]) root=u;
}
void getdeep(int u,int fa)
{
	a[++num]=d[u];
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v!=fa&&!visit[v])
		{
			d[v]=d[u]+val[i];
			getdeep(v,u);
		}
	}
}
int calc(int u,int x)
{
	d[u]=x;num=0;
	getdeep(u,0);
	sort(a+1,a+num+1);
	int ans=0;
	for (int l=1,r=num;l<r;)
		if (a[l]+a[r]<=k) ans+=r-l,l++;else r--;
	return ans;

}
void Work(int u)
{
	ans+=calc(u,0);
	visit[u]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (!visit[v])
		{
			ans-=calc(v,val[i]);
			root=0;
			sum=son[v];
			getroot(v,0);
			Work(root);
		}
	}
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n-1;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);add(y,x,z);
	}
	scanf("%d",&k);
	root=0;sum=n;ans=0;
	f[0]=1<<29;
	getroot(1,0);
	Work(root);
	printf("%d\n",ans);
	return 0;
}
