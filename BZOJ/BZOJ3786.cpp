#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=200100;
int n,tot,cnt,root,Q,a[N],b[N],Next[N],head[N],tree[N],A[N],In[N],Out[N],size[N],son[N][2],fa[N],Tree1[N],Tree2[N],Stack[N],Sum1[N],lazy[N];
ll Sum[N];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs(int u)
{
	A[++cnt]=1;b[cnt]=a[u];In[u]=cnt;
	for (int i=head[u];i;i=Next[i]) dfs(tree[i]);
	A[++cnt]=-1;b[cnt]=a[u];Out[u]=cnt;
}
inline void update(int x)
{
	if (x)
	{
		size[x]=size[son[x][0]]+size[son[x][1]]+1;
		Sum[x]=Sum[son[x][0]]+Sum[son[x][1]]+((Tree2[x]>0)?Tree1[x]:-Tree1[x]);
		Sum1[x]=Sum1[son[x][0]]+Sum1[son[x][1]]+Tree2[x];
	}
}
inline void pushdown(int x)
{
	if (lazy[x]!=0)
	{
		if (son[x][0]) { Sum[son[x][0]]+=(ll)lazy[x]*Sum1[son[x][0]];Tree1[son[x][0]]+=lazy[x];lazy[son[x][0]]+=lazy[x];}
		if (son[x][1]) { Sum[son[x][1]]+=(ll)lazy[x]*Sum1[son[x][1]];Tree1[son[x][1]]+=lazy[x];lazy[son[x][1]]+=lazy[x];}
		lazy[x]=0;
	}
}
inline void Rotate(int x,int &k)
{
	int y=fa[x],z=fa[y],l,r;
	if (x==son[y][0]) l=0;else l=1;
	r=l^1;	
	if (y==k) k=x;
	else
	{
		if (son[z][0]==y) son[z][0]=x;else son[z][1]=x;
	}
	fa[x]=z;fa[y]=x;fa[son[x][r]]=y;
	son[y][l]=son[x][r];son[x][r]=y;
	update(y);update(x);
}
void splay(int x,int &k)
{
	int top=0;
	for (int i=x;fa[i];i=fa[i]) Stack[++top]=i;
	for (int i=top;i;i--) pushdown(Stack[i]);
	while (x!=k)
	{
		int y=fa[x],z=fa[y];
		if (y!=k)
		{
			if ((son[z][0]==y)^(son[y][0]==x)) Rotate(x,k);
				else Rotate(y,k);
		}
		Rotate(x,k);
	}
}
void build(int l,int r,int father)
{
	if (l>r) return;
	int mid=(l+r)>>1;
	build(l,mid-1,mid);
	build(mid+1,r,mid);
	lazy[mid]=0;
	fa[mid]=father;
	son[father][father<mid]=mid;
	Tree1[mid]=b[mid];
	Tree2[mid]=Sum1[mid]=A[mid];
	Sum[mid]=(A[mid]>0)?b[mid]:-b[mid];
	size[mid]=1;
	update(mid);
}
inline int PRE(int x)
{
	splay(x,root);
	int id=son[x][0];
	while (son[id][1]) id=son[id][1];
	return id;
}
inline int NEXT(int x)
{
	splay(x,root);
	int id=son[x][1];
	while (son[id][0]) id=son[id][0];
	return id;
}
inline ll query(int x)
{
	splay(x,root);
	return Sum[son[x][0]]+Tree1[x];
}
inline void change(int x,int y)
{
	int i=PRE(In[x]),j=NEXT(Out[x]);
	splay(i,root);
	splay(j,son[i][1]);
	int id=son[j][0];
	son[j][0]=0;
	update(j);
	update(root);
	int k=In[y],k1=NEXT(k);
	splay(k,root);
	splay(k1,son[k][1]);
	son[k1][0]=id;
	fa[id]=k1;
	splay(id,root);
}
inline void Add(int x,int y)
{
	int i=PRE(In[x]),j=NEXT(Out[x]);
	splay(i,root);
	splay(j,son[i][1]);
	Sum[son[j][0]]+=(ll)Sum1[son[j][0]]*y;
	Tree1[son[j][0]]+=y;
	lazy[son[j][0]]+=y;
}
int main()
{
	scanf("%d",&n);
	tot=cnt=0;
	for (int i=2;i<=n;i++)
	{
		int x;
		x=read();
		add(x,i);
	}
	for (int i=1;i<=n;i++) a[i]=read();
	A[++cnt]=0;
	dfs(1);
	A[++cnt]=0;
	build(1,cnt,0);
	root=(cnt+1)>>1;
	scanf("%d",&Q);
	while (Q--)
	{
		char ch=getchar();int x,y;
		while (ch<'A'||ch>'Z') ch=getchar();
		x=read();
		if (ch=='Q') printf("%lld\n",query(In[x]));
			else if (ch=='C') { y=read();change(x,y);}
				else { y=read();Add(x,y);}
	}
	return 0;
}
