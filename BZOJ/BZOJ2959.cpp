#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=200010;
int n,m,A[N],a[N],f[N],son[N][2],rev[N],sum[N],Stack[N],top,fa[N],R[N];
int get(int x)
{
	if (f[x]==x) return x;else f[x]=get(f[x]);
	return f[x];
}
bool isRoot(int x) { return son[get(fa[x])][0]!=x&&son[get(fa[x])][1]!=x;}
void up(int x)
{
	sum[x]=sum[son[x][0]]+sum[son[x][1]]+a[x];
}
void pushdown(int x)
{
	if (rev[x])
	{
		swap(son[x][0],son[x][1]);
		rev[son[x][0]]^=1;
		rev[son[x][1]]^=1;
		rev[x]=0;
	}
}
void Rotate(int x)
{
	fa[x]=get(fa[x]);
	int y=fa[x];
	fa[y]=get(fa[y]);
	int z=fa[y],l,r;
	if (son[y][0]==x) l=0;else l=1;
	r=l^1;
	if (!isRoot(y))
	{
		if (son[z][0]==y) son[z][0]=x;else son[z][1]=x;
	}
	fa[x]=z;fa[y]=x;fa[son[x][r]]=y;
	son[y][l]=son[x][r];son[x][r]=y;
	up(y);up(x);
}
void splay(int x)
{
	top=0;Stack[++top]=x;
	for (int i=x;!isRoot(i);i=fa[i]) fa[i]=get(fa[i]),Stack[++top]=fa[i];
	for (;top;top--) pushdown(Stack[top]);
	while (!isRoot(x))
	{
		fa[x]=get(fa[x]);
		int y=fa[x];
		fa[y]=get(fa[y]);
		int z=fa[y];
		if (!isRoot(y))
		{
			if ((son[z][0]==y)^(son[y][0]==x)) Rotate(x);
				else Rotate(y);
		}
		Rotate(x);
	}
}
void access(int x)
{
	for (int i=0;x;i=x,fa[x]=get(fa[x]),x=fa[x])
	{
		splay(x);
		son[x][1]=i;
		up(x);
	}
}
void MakeRoot(int x)
{
	access(x);
	splay(x);
	rev[x]^=1;
}
int GetRoot(int x)
{
	if (R[x]==x) return x;else R[x]=GetRoot(R[x]);
	return R[x];
}
void dfs(int x,int y)
{
	f[x]=y;
	if (x!=y) a[y]+=a[x];
	if (son[x][0]) dfs(son[x][0],y);
	if (son[x][1]) dfs(son[x][1],y);
	son[x][0]=son[x][1]=0;
}
void Link(int x,int y)
{
	x=get(x);y=get(y);
	if (x==y) return;
	if (GetRoot(x)==GetRoot(y))
	{
		MakeRoot(x);
		access(y);
		splay(y);
		dfs(y,y);
		up(y);
		return;
	}
	R[GetRoot(x)]=GetRoot(y);
	MakeRoot(x);
	fa[x]=y;
}
void Change(int x,int y)
{
	int last=x;
	x=get(x);
	splay(x);
	a[x]+=y-A[last];
	A[last]=y;
	up(x);
}
int query(int x,int y)
{
	x=get(x);y=get(y);
	if (GetRoot(x)!=GetRoot(y)) return -1;
	MakeRoot(x);
	access(y);
	splay(y);
	return sum[y];
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&A[i]),a[i]=A[i];
	for (int i=1;i<=n;i++) f[i]=R[i]=i;
	for (int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		if (x==1) Link(y,z);
		if (x==2) Change(y,z);
		if (x==3) printf("%d\n",query(y,z));
	}
	return 0;
}
