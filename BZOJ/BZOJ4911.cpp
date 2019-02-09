#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 10007
using namespace std;
int n,m,a[N],Q,tot,Next[N*2],head[N],tree[N*2],val[N*2],.
struct Int
{
	int x,f;
	friend Int operator * (Int A,int y) { if (!y) A.f++;else A.x=A.x*y%mo;}
	friend Int operator / (Int A,int y) { if (!y) A.f--;else A.x=A.x*inv[y]%mo;}
	int val() { return (f)?0:x;}
}
void FWT(int *A,int f)
{
	for (int len=2;len<=L;len<<=1)
		for (int i=0,l=len>>1;i<L;i+=len)
			for (int j=0;j<l;j++)
			{
				int x=f[i+j],y=f[i+j+l];
				f[i+j]=(x+y)%mo;f[i+j+l]=(x-y+mo)%mo;
				if (f==-1) f[i+j]=f[i+j]*inv[2]%mo,f[i+j+l]=f[i+j+l]*inv[2]%mo;
			}
}
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
	val[tot]=z;
}
void calc(int x,int *A)
{
	for (int i=0;i<L;i++) A[i]=0;
	A[x]=1;
	FWT(A,1);
}
void mul(int *A,int *B,int *C)
{
	for (int i=0;i<L;i++) C[i]=A[i]*B[i]%mo;
}
void dfs(int u,int father,int depth)
{
	fa[u]=father;dep[u]=depth;size[u]=1;
	int MaxSize=0,A[130];
	for (int i=0;i<L;i++) A[i]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==father) continue;
		dfs(v,u,depth+1);
		size[u]+=size[v];
		if (size[v]>MaxSize) MaxSize=size[v],son[u]=v;
		for (int j=0;j<L;j++) f[v][j]=(f[v][j]+1)%mo;
		mul(A,f[v],A);
		for (int j=0;j<L;j++) f[v][j]=(f[v][j]-1+mo)%mo;
	}
	mul(f[u],A,f[u]);
	for (int i=0;i<L;i++) X[u][i]=A[i],A[i]=f[u][i];
	FWT(A,-1);
	for (int i=0;i<L;i++) ans[i]=(ans[i]+A[i])%mo;
}
void dfs1(int u,int ancestor)
{
	tid[u]=++label;top[u]=ancestor;num[label]=u;
	if (son[u]) dfs1(son[u],ancestor);
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v!=fa[u]&&v!=son[u]) dfs1(v,v);
	}
}
void up(int id)
{
	for (int i=0;i<L;i++) Tree[id][i]=(Tree[id<<1][i]+Tree[id<<1|1][i])%mo;
}
void build(int l,int r,int id)
{
	if (l==r)
	{
		memcpy(Tree[id],f[num[l]],sizeof(f[num[l]]));
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,id<<1);
	build(mid+1,r,id<<1|1);
	up(id);
}
void Change(int l,int r,int id,int x,int y)
{
	if (l>y||r<x) return;
	if (x<=l&&r<=y)
	{
		for (int i=0;i<L;i++)
		for (int i=0;i<L;i++) Tree[id][i]=Tree[id][i]/Last[i],Tree[id][i]=Tree[id][i]*New[i];
		return;
	}
	int mid=(l+r)>>1;
	Change(l,mid,id<<1,x,y);
	Change(mid+1,r,id<<1|1,x,y);
	up(id);
}
void change(int x)
{
	while (top[x]!=1)
	{
		Change(1,n,1,tid[top[x]],tid[x]);
		x=fa[top[x]];
	}
	Change(1,n,1,tid[1],tid[x]);
}
void pre()
{
	L=1;
	while (L<Max) L<<=1;
	for (int i=2;i<mo;i++) inv[i]=(mo-mo/i)*inv[mo%i]%mo;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	pre();
	for (int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	scanf("%d",&Q);
	for (int i=1;i<=n;i++)
	{
		calc(a[i],f[i]);
	}
	dfs(1,0,1);
	dfs1(1,0);
	build(1,n,1);
	while (Q--)
	{
		char s[10];int x,y;
		scanf("%s%d",s,&x);
		if (s[0]=='Q')
		{
			printf("%d\n",ans[x]);
		}else
		{
			scanf("%d",&y);
			a[x]=y;
			for (int i=0;i<L;i++) Last[i]=f[x][i],A[i]=f[x][i];
			for (int i=0;i<L;i++) X[fa[x]][i]=X[fa[x]][i]/(f[x][i]+1)%mo;
			FWT(A,-1);
			for (int i=0;i<L;i++) ans[i]=(ans[i]-A[i]+mo)%mo
			calc(a[x],f[x]);
			mul(f[x],X[x],f[x]);
			for (int i=0;i<L;i++) A[i]=New[i]=f[x][i];
			FWT(A,-1);
			for (int i=0;i<L;i++) ans[i]=(ans[i]+A[i])%mo;
			for (int i=0;i<L;i++) A[i]=(f[x][i]+1)%mo;
			change(fa[x]);
		}
	}
	return 0;
}
