#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=50010,NlgN=2000010;
int n,m,cnt,tot,a[N],Tree[NlgN],son[NlgN][2],num[NlgN],Root[N*4],fa[NlgN],size[NlgN];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') { x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
struct SPLAY
{
	int root;
	inline void update(int x)
	{
		if (x)
		{
			size[x]=num[x];
			if (son[x][0]) size[x]+=size[son[x][0]];
			if (son[x][1]) size[x]+=size[son[x][1]];
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
				if ((son[y][0]==x)^(son[z][0]==y)) Rotate(x,k);
					else Rotate(y,k);
			}
			Rotate(x,k);
		}
	}
	inline void newnode(int x,int y)
	{
		son[x][0]=son[x][1]=0;
		num[x]=size[x]=1;
		Tree[x]=y;
	}
	void insert(int x)
	{
		int i=root,id;
		if (!root) { id=++tot;root=id;fa[id]=0;newnode(id,x);return;}
		while (i)
		{
			int j=i;
			if (Tree[i]==x) { splay(i,root);num[i]++;size[i]++;return;}
			i=son[i][x>Tree[i]];
			if (!i)
			{
				id=++tot;
				newnode(id,x);
				fa[id]=j;
				son[j][x>Tree[j]]=id;
				splay(id,root);
				return;
			}
		}
	}
	int rank(int x)
	{
		int i=root,ans=0;
		while (i)
		{
			if (Tree[i]>x) i=son[i][0];
			else
			{
				ans+=size[son[i][0]];
				if (Tree[i]==x) return ans+1;
				ans+=num[i];
				i=son[i][1];
			}
		}
		return ans+1;
	}
	int Kth(int x)
	{
		int i=root;
		while (i)
		{
			if (size[son[i][0]]>=x) i=son[i][0];
			else
			{
				x-=size[son[i][0]];
				if (x<=num[i]) return i;
				x-=num[i];
				i=son[i][1];
			}
		}
	}
	int find(int x)
	{
		int i=root;
		while (Tree[i]!=x)
		{
			if (Tree[i]>x) i=son[i][0];
				else i=son[i][1];
		}
		return i;
	}
	void del(int x)
	{
		int i=find(x);
		if (num[i]>1) { splay(i,root);num[i]--;size[i]--;return;}
		if (size[root]==1) { root=0;return;}
		splay(i,root);
		if (!son[i][0]||!son[i][1])
		{
			root=son[i][0]^son[i][1];
			return;
		}
		int j=son[i][0];
		while (son[j][1]) j=son[j][1];
		splay(j,son[i][0]);
		son[j][1]=son[i][1];
		fa[son[i][1]]=j;
		fa[j]=0;
		root=j;
	}
	int Get_Pre(int x)
	{
		int i=root,ans=-1;
		while (i)
		{
			if (Tree[i]>=x) i=son[i][0];
			else 
			{
				ans=Tree[i];
				i=son[i][1];
			}
		}
		return ans;
	}
	int Get_Next(int x)
	{
		int i=root,ans=1<<29;
		while (i)
		{
			if (Tree[i]<=x) i=son[i][1];
			else
			{
				ans=Tree[i];
				i=son[i][0];
			}
		}
		return ans;
	}
}Splay[N*4];
void Insert(int l,int r,int id,int x,int y)
{
	if (!Root[id]) Root[id]=++cnt;
	Splay[Root[id]].insert(y);
	if (l==r) return;
	int mid=(l+r)>>1;
	if (x<=mid) Insert(l,mid,id<<1,x,y);
		else Insert(mid+1,r,id<<1|1,x,y);
}
void Del(int l,int r,int id,int x,int y)
{
	Splay[Root[id]].del(y);
	if (l==r) return;
	int mid=(l+r)>>1;
	if (x<=mid) Del(l,mid,id<<1,x,y);
		else Del(mid+1,r,id<<1|1,x,y);
}
int Ask_Rank(int l,int r,int id,int x,int y,int z)
{
	if (l>y||r<x) return 0;
	if (x<=l&&r<=y) return (Root[id])?Splay[Root[id]].rank(z)-1:0;
	int mid=(l+r)>>1;
	return Ask_Rank(l,mid,id<<1,x,y,z)+Ask_Rank(mid+1,r,id<<1|1,x,y,z);
}
int Ask_Kth(int L,int R,int K)
{
	int l=0,r=100000000,Ans;
	while (l<r)
	{
		int mid=(l+r)>>1;
		if (Ask_Rank(1,n,1,L,R,mid)<K) l=mid+1,Ans=mid;
			else r=mid;
	}
	return Ans;
}
int Ask_Pre(int l,int r,int id,int x,int y,int z)
{
	if (l>y||r<x) return -1;
	if (x<=l&&r<=y) return (Root[id])?Splay[Root[id]].Get_Pre(z):-1;
	int mid=(l+r)>>1;
	return max(Ask_Pre(l,mid,id<<1,x,y,z),Ask_Pre(mid+1,r,id<<1|1,x,y,z));
}
int Ask_Next(int l,int r,int id,int x,int y,int z)
{
	if (l>y||r<x) return 1<<29;
	if (x<=l&&r<=y) return (Root[id])?Splay[Root[id]].Get_Next(z):-1;
	int mid=(l+r)>>1;
	return min(Ask_Next(l,mid,id<<1,x,y,z),Ask_Next(mid+1,r,id<<1|1,x,y,z));
}
int main()
{
	n=read();m=read();
	cnt=tot=0;
	for (int i=1;i<=n;i++)
	{
		a[i]=read();
		Insert(1,n,1,i,a[i]);
	}
	while (m--)
	{
		int opt,x,y,z;
		opt=read();x=read();y=read();
		switch (opt)
		{
			case 1:z=read();printf("%d\n",Ask_Rank(1,n,1,x,y,z)+1);break;
			case 2:z=read();printf("%d\n",Ask_Kth(x,y,z));break;
			case 3:
			{
				Del(1,n,1,x,a[x]);
				Insert(1,n,1,x,y);
				a[x]=y;
				break;
			}
			case 4:z=read();printf("%d\n",Ask_Pre(1,n,1,x,y,z));break;
			case 5:z=read();printf("%d\n",Ask_Next(1,n,1,x,y,z));break;
		}
	}
	return 0;
}
