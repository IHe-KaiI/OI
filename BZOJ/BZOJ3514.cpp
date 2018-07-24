#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=500100,M=4000100;
int n,m,k,Type,Tree[N],son[N][2],fa[N],Min[N],rev[N],Stack[N],ls[M],rs[M],Size[M],Root[200100],R[200100],tot;
struct node{int x,y;}Edge[400100];
bool isRoot(int x) { return (son[fa[x]][0]!=x)&&(son[fa[x]][1]!=x);}
void update(int x)
{
	int l=son[x][0],r=son[x][1];
	Min[x]=min(Min[l],min(Min[r],Tree[x]));
}
void pushdown(int x)
{
	if (rev[x])
	{
		if (son[x][0]) rev[son[x][0]]^=1;
		if (son[x][1]) rev[son[x][1]]^=1;
		swap(son[x][0],son[x][1]);
		rev[x]=0;
	}
}
void Rotate(int x)
{
	int y=fa[x],z=fa[y],l,r;
	if (son[y][0]==x) l=0;else l=1;
	r=l^1;
	if (!isRoot(y))
	{
		if (son[z][0]==y) son[z][0]=x;else son[z][1]=x;
	}
	fa[x]=z;fa[y]=x;fa[son[x][r]]=y;
	son[y][l]=son[x][r];son[x][r]=y;
	update(y);update(x);
}
void splay(int x)
{
	int top=0;Stack[++top]=x;
	for (int i=x;!isRoot(i);i=fa[i]) Stack[++top]=fa[i];
	for (;top;top--) pushdown(Stack[top]);
	while (!isRoot(x))
	{
		int y=fa[x],z=fa[y];
		if (!isRoot(y))
		{
			if ((son[y][0]==x)^(son[z][0]==y)) Rotate(x);
				else Rotate(y);
		}
		Rotate(x);
	}
}
void access(int x)
{
	for (int i=0;x;i=x,x=fa[x])
	{
		splay(x);
		son[x][1]=i;
		update(x);
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
	access(x);
	splay(x);
	while (son[x][0]) x=son[x][0];
	return x;
}
int compuse(int x,int y)
{
	MakeRoot(x);
	access(y);
	splay(y);
	return y;
}
void link(int x,int y)
{
	MakeRoot(x);
	fa[x]=y;
}
void cut(int x,int y)
{
	MakeRoot(x);
	access(y);
	splay(y);
	son[y][0]=fa[x]=0;
	update(y);
}
void Insert(int l,int r,int ID,int &id,int x)
{
	id=++tot;
	Size[id]=Size[ID]+1;
	if (l==r) return;
	int mid=(l+r)>>1;
	ls[id]=ls[ID];rs[id]=rs[ID];
	if (x<=mid) Insert(l,mid,ls[ID],ls[id],x);
		else Insert(mid+1,r,rs[ID],rs[id],x);
}
int query(int l,int r,int idx,int idy,int x)
{
	if (r==x) return Size[idy]-Size[idx];
	int mid=(l+r)>>1;
	if (x<=mid) return query(l,mid,ls[idx],ls[idy],x);
		else return Size[ls[idy]]-Size[ls[idx]]+query(mid+1,r,rs[idx],rs[idy],x);
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&Type);
	Min[0]=1<<29;
	for (int i=1;i<=n;i++) Tree[i]=Min[i]=1<<29;
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		R[i]=m+1;
		if (x==y) { R[i]=i;continue;}
		Tree[n+i]=Min[n+i]=i;
		Edge[n+i]=(node){x,y};
		if (GetRoot(x)==GetRoot(y))
		{
			int ID=compuse(x,y);
			R[Min[ID]]=i;
			int j=Min[ID]+n;
			cut(j,Edge[j].x);cut(j,Edge[j].y);
			link(x,n+i);link(n+i,y);
		}else link(x,n+i),link(n+i,y);
	}
	for (int i=1;i<=m;i++) Insert(1,m+1,Root[i-1],Root[i],R[i]);
	int lastans=0;
	while (k--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if (Type) x^=lastans,y^=lastans;
		lastans=n-(y-x+1-query(1,m+1,Root[x-1],Root[y],y));
		printf("%d\n",lastans);
	}
	return 0;
}

