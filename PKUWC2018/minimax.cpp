#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 998244353
#define INVmo 796898467
using namespace std;
const int N=300010;
int n,tot,Next[N<<1],head[N],tree[N<<1],a[N],A[N],p[N],cnt,num,son[N*20][2],Tree[N*20],lazy[N*20],root[N];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void down(int id)
{
	if (lazy[id]!=1)
	{
		int l=son[id][0],r=son[id][1];
		if (l)
		{
			lazy[l]=(ll)lazy[l]*lazy[id]%mo;
			Tree[l]=(ll)Tree[l]*lazy[id]%mo;
		}
		if (r)
		{
			lazy[r]=(ll)lazy[r]*lazy[id]%mo;
			Tree[r]=(ll)Tree[r]*lazy[id]%mo;
		}
		lazy[id]=1;
	}
}
void Insert(int &id,int l,int r,int x,int y)
{
	if (!id) { id=++num;lazy[id]=1;}
	down(id);
	if (l==r) { Tree[id]=y;return;}
	int mid=(l+r)>>1;
	if (x<=mid) Insert(son[id][0],l,mid,x,y);
		else Insert(son[id][1],mid+1,r,x,y);
	Tree[id]=(Tree[son[id][0]]+Tree[son[id][1]])%mo;
}
int merge(int x,int y,int l,int r,int p,int Lx,int Rx,int Ly,int Ry)
{
	down(x);
	down(y);
	if (!y)
	{
		ll X=((ll)Ly*p%mo+((ll)Ry*(1-p+mo)%mo))%mo;
		Tree[x]=(ll)Tree[x]*X%mo;
		lazy[x]=(ll)lazy[x]*X%mo;
		return x;
	}
	if (!x)
	{
		ll X=((ll)Lx*p%mo+((ll)Rx*(1-p+mo)%mo))%mo;
		Tree[y]=(ll)Tree[y]*X%mo;
		lazy[y]=(ll)lazy[y]*X%mo;
		return y;
	}
	int mid=(l+r)>>1,lx=Tree[son[x][0]],rx=Tree[son[x][1]],ly=Tree[son[y][0]],ry=Tree[son[y][1]];
	son[x][0]=merge(son[x][0],son[y][0],l,mid,p,Lx,(Rx+rx)%mo,Ly,(Ry+ry)%mo);
	son[x][1]=merge(son[x][1],son[y][1],mid+1,r,p,(Lx+lx)%mo,Rx,(Ly+ly)%mo,Ry);
	Tree[x]=(Tree[son[x][0]]+Tree[son[x][1]])%mo;
	return x;
}
int query(int id,int l,int r,int x)
{
	down(id);
	if (l==r) return Tree[id];
	int mid=(l+r)>>1;
	if (x<=mid) return query(son[id][0],l,mid,x);
		else return query(son[id][1],mid+1,r,x);
}
void dfs(int u)
{
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		dfs(v);
		if (!root[u]) root[u]=root[v];
			else root[u]=merge(root[u],root[v],1,cnt,p[u],0,0,0,0);
	}
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		if (x) add(x,i);
	}
	cnt=0;
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		if (head[i]) p[i]=(ll)x*INVmo%mo;
			else a[i]=x,A[++cnt]=x;
	}
	sort(A+1,A+cnt+1);
	cnt=unique(A+1,A+cnt+1)-A-1;
	for (int i=1;i<=n;i++)
	{
		int x=lower_bound(A+1,A+cnt+1,a[i])-A;
		if (a[i]) Insert(root[i],1,cnt,x,1);
	}
	dfs(1);
	ll ans=0;
	for (int i=1;i<=cnt;i++)
	{
		int x=query(root[1],1,cnt,i);
		ans=(ans+(ll)i*A[i]%mo*x%mo*x%mo)%mo;
	}
	printf("%lld\n",ans);
	return 0;
}
