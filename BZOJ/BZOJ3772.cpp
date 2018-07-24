#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#define ll long long
using namespace std;
const int N=100100,M=4000000;
int n,m,tot,cnt,NUM,Next[N<<1],head[N],tree[N<<1],In[N],Out[N],fa[N][18],dep[N],son[M][2],root[N],Tree[M];
vector<int>a[N];
struct node{int x,y;}Q[N];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs(int u,int father,int depth)
{
	In[u]=++cnt;fa[u][0]=father;dep[u]=depth;
	for (int i=head[u];i;i=Next[i])
		if (tree[i]!=father) dfs(tree[i],u,depth+1);
	Out[u]=++cnt;
}
void Insert(int &id,int l,int r,int x,int d)
{
	int i=id;
	id=++NUM;
	if (l==r) { Tree[id]=Tree[i]+d;return;}
	int mid=(l+r)>>1;
	son[id][0]=son[i][0];
	son[id][1]=son[i][1];
	if (x<=mid) Insert(son[id][0],l,mid,x,d);
		else Insert(son[id][1],mid+1,r,x,d);
	Tree[id]=Tree[son[id][0]]+Tree[son[id][1]];
}
int query(int id1,int id2,int id3,int id4,int l,int r,int x,int y)
{
	if (l>y||r<x) return 0;
	if (x<=l&&r<=y) return Tree[id1]+Tree[id2]-Tree[id3]-Tree[id4];
	int mid=(l+r)>>1;
	return query(son[id1][0],son[id2][0],son[id3][0],son[id4][0],l,mid,x,y)+query(son[id1][1],son[id2][1],son[id3][1],son[id4][1],mid+1,r,x,y);
}
void dfs1(int u)
{
	root[u]=root[fa[u][0]];
	for (int i=0;i<a[u].size();i++)
	{
		Insert(root[u],1,cnt,In[a[u][i]],1);
		Insert(root[u],1,cnt,Out[a[u][i]],-1);
	}
	for (int i=head[u];i;i=Next[i])
		if (tree[i]!=fa[u][0]) dfs1(tree[i]);
}
int lca(int x,int y)
{
	if (dep[x]<dep[y]) swap(x,y);
	int z=dep[x]-dep[y];
	for (int i=17;i>=0;i--)
		if ((1<<i)<=z) z-=1<<i,x=fa[x][i];
	if (x==y) return x;
	for (int i=17;i>=0;i--)
		if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
ll gcd(ll x,ll y) { return (!y)?x:gcd(y,x%y);}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0,1);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[x].push_back(y);
		Q[i]=(node){x,y};
	}
	dfs1(1);
	for (int i=1;i<=17;i++)
		for (int j=1;j<=n;j++) fa[j][i]=fa[fa[j][i-1]][i-1];
	ll Ansx=0,Ansy=(ll)m*(m-1)/2;
	for (int i=1;i<=m;i++)
	{
		int x=Q[i].x,y=Q[i].y,z=lca(x,y);
		Ansx+=query(root[x],root[y],root[z],root[fa[z][0]],1,cnt,In[z],In[x]);
		Ansx+=query(root[x],root[y],root[z],root[fa[z][0]],1,cnt,In[z],In[y]);
		Ansx-=query(root[x],root[y],root[z],root[fa[z][0]],1,cnt,In[z],In[z]);
		Ansx--;
	}
	ll GCD=gcd(Ansx,Ansy);
	printf("%lld/%lld",Ansx/GCD,Ansy/GCD);
	return 0;
}
