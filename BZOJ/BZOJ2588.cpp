#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=100100;
int n,m,a[N],A[N],tot,Next[N*2],head[N],tree[N*2],num,cnt,Tree[N*20],f[N][20],dep[N],son[N*20][2],root[N];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void Insert(int l,int r,int x,int &y,int X)
{
	y=++cnt;
	Tree[y]=Tree[x]+1;
	if (l==r) return;
	int mid=(l+r)>>1;
	son[y][0]=son[x][0];son[y][1]=son[x][1];
	if (X<=mid) Insert(l,mid,son[x][0],son[y][0],X);
		else Insert(mid+1,r,son[x][1],son[y][1],X);
}
void dfs(int u,int fa,int depth)
{
	f[u][0]=fa;dep[u]=depth;
	Insert(1,num,root[fa],root[u],a[u]);
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa) continue;
		dfs(v,u,depth+1);
	}
}
int lca(int x,int y)
{
	if (dep[x]<dep[y]) swap(x,y);
	int z=dep[x]-dep[y];
	for (int i=18;z>0&&i>=0;i--)
		if ((1<<i)<=z) z-=1<<i,x=f[x][i];
	if (x==y) return x;
	for (int i=18;i>=0;i--)
		if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
int query(int x,int y,int z,int X)
{
	int L=1,R=num,i=root[x],j=root[y],k=root[z],l=root[f[z][0]];
	while (L<R)
	{
		int mid=(L+R)>>1;
		int p=Tree[son[i][0]]+Tree[son[j][0]]-Tree[son[k][0]]-Tree[son[l][0]];
		if (p>=X) i=son[i][0],j=son[j][0],k=son[k][0],l=son[l][0],R=mid;
			else i=son[i][1],j=son[j][1],k=son[k][1],l=son[l][1],X-=p,L=mid+1;
	}
	return L;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),A[i]=a[i];
	sort(A+1,A+n+1);
	num=unique(A+1,A+n+1)-A-1;
	for (int i=1;i<=n;i++) a[i]=lower_bound(A+1,A+num+1,a[i])-A;
	for (int i=1;i<=n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0,1);
	for (int j=1;j<=18;j++)
		for (int i=1;i<=n;i++) f[i][j]=f[f[i][j-1]][j-1];
	int ans=0;
	while (m--)
	{
		int u,v,k;
		scanf("%d%d%d",&u,&v,&k);
		u=u^ans;
		ans=A[query(u,v,lca(u,v),k)];
		printf("%d",ans);
		if (m!=0) puts("");
	}
	return 0;
}
