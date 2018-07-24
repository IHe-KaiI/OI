#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
#define mo 51061
#define uint unsigned int
const int N=500100;
using namespace std;
int n,q,tot,Next[N*2],head[N],tree[N*2];
namespace LCT
{
	int size[N],fa[N],son[N][2],top,Stack[N],rev[N];
	uint Tree[N],Sum[N],lazy_plus[N],lazy_mul[N];
	bool isRoot(int x) { return son[fa[x]][0]!=x&&son[fa[x]][1]!=x;}
	void update(int x)
	{
		int l=son[x][0],r=son[x][1];
		size[x]=size[l]+size[r]+1;
		Sum[x]=(Sum[l]+Sum[r]+Tree[x])%mo;
	}
	void pushdown(int x)
	{
		int l=son[x][0],r=son[x][1];
		if (rev[x])
		{
			if (l) rev[l]^=1;
			if (r) rev[r]^=1;
			swap(son[x][0],son[x][1]);
			rev[x]=0;
		}
		if (lazy_mul[x]!=1)
		{
			if (l)
			{
				(Tree[l]*=lazy_mul[x])%=mo;(Sum[l]*=lazy_mul[x])%=mo;
				(lazy_mul[l]*=lazy_mul[x])%=mo;
				(lazy_plus[l]*=lazy_mul[x])%=mo;
			}
			if (r) 
			{
				(Tree[r]*=lazy_mul[x])%=mo,(Sum[r]*=lazy_mul[x])%=mo;
				(lazy_mul[r]*=lazy_mul[x])%=mo;
				(lazy_plus[r]*=lazy_mul[x])%=mo;
			}
			lazy_mul[x]=1;
		}
		if (lazy_plus[x]!=0)
		{
			if (l)
			{
				(Tree[l]+=lazy_plus[x])%=mo;(Sum[l]+=lazy_plus[x]*size[l])%=mo;
				(lazy_plus[l]+=lazy_plus[x])%=mo;
			}
			if (r)
			{
				(Tree[r]+=lazy_plus[x])%=mo;(Sum[r]+=lazy_plus[x]*size[r])%=mo;
				(lazy_plus[r]+=lazy_plus[x])%=mo;
			}
			lazy_plus[x]=0;
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
		top=0;Stack[++top]=x;
		for (int i=x;!isRoot(i);i=fa[i]) Stack[++top]=fa[i];
		for (;top;top--) pushdown(Stack[top]);
		while (!isRoot(x)) 
		{
			int y=fa[x],z=fa[y];
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
	int compuse(int x,int y)
	{
		MakeRoot(x);
		access(y);
		splay(y);
		return y;
	}
	void Plus(int x,int y,int z)
	{
		int id=compuse(x,y);
		(Tree[id]+=z)%=mo;
		(Sum[id]+=(uint)size[id]*z)%=mo;
		(lazy_plus[id]+=z)%=mo;
	}
	void Mul(int x,int y,int z)
	{
		int id=compuse(x,y);
		(Tree[id]*=z)%=mo;
		(Sum[id]*=z)%=mo;
		(lazy_mul[id]*=z)%=mo;
		(lazy_plus[id]*=z)%=mo;
	}
	void cut(int x,int y)
	{
		MakeRoot(x);
		access(y);
		splay(y);
		son[y][0]=fa[x]=0;
		update(y);
	}
	void link(int x,int y)
	{
		MakeRoot(x);
		fa[x]=y;
	}
	int query(int x,int y)
	{
		int id=compuse(x,y);
		return Sum[id];
	}
}
int main()
{
	using namespace LCT;
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;i++) Tree[i]=Sum[i]=lazy_mul[i]=size[i]=1;
	for (int i=1;i<=n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		link(x,y);
	}
	while (q--)
	{
		char s[5];int x,y,z,X,Y;
		scanf("%s",s);
		switch (s[0])
		{
			case '+':
			{
				scanf("%d%d%d",&x,&y,&z);
				Plus(x,y,z);
				break;
			}
			case '-':
			{
				scanf("%d%d%d%d",&x,&y,&X,&Y);
				cut(x,y);
				link(X,Y);
				break;
			}
			case '*':
			{
				scanf("%d%d%d",&x,&y,&z);
				Mul(x,y,z);
				break;
			}
			case '/':
			{
				scanf("%d%d",&x,&y);
				printf("%d\n",query(x,y));
				break;
			}
		}
	}
	return 0;
}
