#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define M 2333
#define ull unsigned long long
using namespace std;
char s[100100],s1[100100];
int n,q,tot,root,a[100100],size[100100],son[100100][2],fa[100100];
ull F[100100],Sum[100100],Tree[100100];
void update(int x)
{
	if (x)
	{
		size[x]=size[son[x][0]]+size[son[x][1]]+1;
		Sum[x]=Sum[son[x][0]]*(F[size[son[x][1]]+1])+Tree[x]*F[size[son[x][1]]]+Sum[son[x][1]];
	}
}
void build(int l,int r,int father)
{
	if (l>r) return;
	int mid=(l+r)>>1;
	build(l,mid-1,mid);
	build(mid+1,r,mid);
	Tree[mid]=a[mid];
	Sum[mid]=a[mid];
	fa[mid]=father;
	size[mid]=1;
	son[father][father<mid]=mid;
	update(mid);
}
void Rotate(int x,int &k)
{
	int y=fa[x],z=fa[y],l,r;
	if (son[y][0]==x) l=0;else l=1;
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
int find(int x)
{
	int i=root;
	while (i)
	{
		if (size[son[i][0]]+1==x) return i;
		if (size[son[i][0]]>=x) i=son[i][0];	
			else x-=size[son[i][0]]+1,i=son[i][1];
	}
}
int split(int x,int y)
{
	x=find(x);y=find(y);
	splay(x,root);splay(y,son[x][1]);
	return y;
}
ull query(int x,int y)
{
	if (x>y) return 0;
	int id=split(x-1,y+1);
	return Sum[son[id][0]];
}
int LCQ(int x,int y)
{
	int l=0,r=min(size[root]-x-1,size[root]-y-1);
	x++;y++;
	while (l<r)
	{
		int mid=(l+r+1)>>1;
		if (query(x,x+mid-1)==query(y,y+mid-1)) l=mid;
			else r=mid-1;
	}
	return l;
}
void Add(int x,char ch)
{
	x++;
	int id=split(x,x+1);
	++tot;
	son[id][0]=tot;
	fa[tot]=id;
	Tree[tot]=Sum[tot]=ch-'a'+1;
	size[tot]=1;
	splay(tot,root);
}
void Change(int x,int ch)
{
	x++;
	int id=split(x-1,x+1);
	Tree[son[id][0]]=Sum[son[id][0]]=ch-'a'+1;
	splay(son[id][0],root);
}
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	F[0]=1;
	for (int i=1;i<=100005;i++) F[i]=F[i-1]*M;
	for (int i=2;i<=n+1;i++) a[i]=s[i-1]-'a'+1;
	a[1]=0;a[n+2]=0;
	build(1,n+2,0);
	tot=n+2;
	root=(n+3)>>1;
	scanf("%d",&q);
	while (q--)
	{
		scanf("%s",s);
		int x,y;
		if (s[0]=='Q') { scanf("%d%d",&x,&y);printf("%d\n",LCQ(x,y));}
		if (s[0]=='R') { scanf("%d%s",&x,s1);Change(x,s1[0]);}
		if (s[0]=='I') { scanf("%d%s",&x,s1);Add(x,s1[0]);}
	}
	return 0;
}
