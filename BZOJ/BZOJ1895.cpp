#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=210000;
int n,a[N],root,tot,m;
char s[20];
struct SPLAY
{
	int fa[N],son[N][2],size[N],Min[N],lazy_add[N],rev[N],Tree[N];
	void update(int x)
	{
		if (!x) return;
		int l=son[x][0],r=son[x][1];
		size[x]=size[l]+size[r]+1;
		Min[x]=Tree[x];
		if (l) Min[x]=min(Min[x],Min[l]);
		if (r) Min[x]=min(Min[x],Min[r]);
	}
	void downdate(int x)
	{
		if (!x) return;
		int l=son[x][0],r=son[x][1];
		if (lazy_add[x]!=0)
		{
			if (l) Tree[l]+=lazy_add[x],Min[l]+=lazy_add[x],lazy_add[l]+=lazy_add[x];
			if (r) Tree[r]+=lazy_add[x],Min[r]+=lazy_add[x],lazy_add[r]+=lazy_add[x];
			lazy_add[x]=0;
		}
		if (rev[x])
		{
			swap(son[x][0],son[x][1]);
			if (l) rev[l]^=1;
			if (r) rev[r]^=1;
			rev[x]=0;
		}
	}
	void Rotate(int x,int &k)
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
		if (l==r)
		{
			fa[l]=father;
			if (l<father) son[father][0]=l;
				else son[father][1]=l;
			Tree[l]=a[l];
			rev[l]=0;
			lazy_add[l]=0;
			size[l]=1;
			Min[l]=a[l];
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid-1,mid);
		build(mid+1,r,mid);
		fa[mid]=father;
		if (mid<father) son[father][0]=mid;
			else son[father][1]=mid;
		Tree[mid]=a[mid];
		Min[mid]=a[mid];
		rev[mid]=0;
		lazy_add[mid]=0;
		size[mid]=1;
		update(mid);
	}
	int find(int x)
	{
		int i=root;
		while (i)
		{
			downdate(i);
			if (size[son[i][0]]+1==x) return i;
			if (size[son[i][0]]>=x) i=son[i][0];
				else x-=size[son[i][0]]+1,i=son[i][1];
		}
	}
	int split(int x,int y)
	{
		int i=find(x),j=find(y);
		splay(i,root);
		splay(j,son[i][1]);
		return son[j][0];
	}
	void Add(int x,int y,int z)
	{
		int i=split(x-1,y+1);
		Min[i]+=z;
		Tree[i]+=z;
		lazy_add[i]+=z;
		update(fa[i]);
		update(fa[fa[i]]);
	}
	void Reverse(int x,int y)
	{
		int i=split(x-1,y+1);
		rev[i]^=1;
	}
	void Insert(int x,int y)
	{
		int i=find(x),j=find(x+1);
		splay(i,root);
		splay(j,son[i][1]);
		son[j][0]=++tot;
		fa[tot]=j;
		Min[tot]=y;
		Tree[tot]=y;
		lazy_add[tot]=0;
		rev[tot]=0;
		size[tot]=1;
		update(j);
		update(i);
	}
	void Del(int x)
	{
		int i=split(x-1,x+1);
		son[fa[i]][0]=0;
		update(fa[i]);
		update(fa[fa[i]]);
		fa[i]=0;
		Tree[i]=Min[i]=lazy_add[i]=rev[i]=size[i]=0;
		if (i==root) root=0;
	}
	int Min_Ans(int x,int y)
	{
		int i=split(x-1,y+1);
		return Min[i];
	}
}Splay;
int main()
{
	scanf("%d",&n);
	a[1]=a[n+2]=(1LL<<31)-1;
	for (int i=2;i<=n+1;i++) scanf("%d",&a[i]);
	Splay.build(1,n+2,0);
	root=(n+3)>>1;
	tot=n+2;
	scanf("%d",&m);
	while (m--)
	{
		int x,y,z;
		scanf("%s",s+1);
		if (s[1]=='A') scanf("%d%d%d",&x,&y,&z),Splay.Add(++x,++y,z);
		if (s[1]=='R'&&s[4]=='E') scanf("%d%d",&x,&y),Splay.Reverse(++x,++y);
		if (s[1]=='R'&&s[4]=='O')
		{
			scanf("%d%d%d",&x,&y,&z);
			x++;y++;
			int len=(z%(y-x+1)+(y-x+1))%(y-x+1);
			if (len==0) continue;
			Splay.Reverse(x,y);
			Splay.Reverse(x,x+len-1);
			Splay.Reverse(x+len,y);
		}
		if (s[1]=='I') scanf("%d%d",&x,&y),Splay.Insert(++x,y);
		if (s[1]=='D') scanf("%d",&x),Splay.Del(++x);
		if (s[1]=='M') scanf("%d%d",&x,&y),printf("%d\n",Splay.Min_Ans(++x,++y));
		
	}
	return 0;
}
