#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=101000;
int n,tot,root;
struct SPLAY
{
	int Tree[N],son[N][2],fa[N],Size[N],Num[N];
	void Clear(int x) { fa[x]=son[x][0]=son[x][1]=0;}
	void update(int x)
	{
		if (x)
		{
			Size[x]=Num[x];
			if (son[x][0]) Size[x]+=Size[son[x][0]];
			if (son[x][1]) Size[x]+=Size[son[x][1]];
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
	void Insert(int x)
	{
		int now=root,father;
		if (!root)
		{ 
			Num[++tot]=1;
			Size[tot]=1;
			root=tot;
			son[tot][0]=son[tot][1]=0;
			Tree[tot]=x;
			fa[tot]=0;
			return;
		}
		while (1)
		{
			if (Tree[now]==x)
			{
				Num[now]++;
				update(now);
				if (now!=root) update(father);
				splay(now,root);
				return;
			}
			father=now;
			now=son[now][x>=Tree[now]];
			if (!now)
			{
				Num[++tot]=1;
				Size[tot]=1;
				son[father][x>=Tree[father]]=tot;
				Tree[tot]=x;
				son[tot][0]=son[tot][1]=0;
				fa[tot]=father;
				update(tot);
				update(father);
				splay(tot,root);
				return;
			}
		}
		
	}
	int find(int x)
	{
		int id=root;
		while (Tree[id]!=x)
		{
			if (x<Tree[id]) id=son[id][0];
				else id=son[id][1];	
		}
		return id;
	}
	int Get_Max(int x)
	{
		while (son[x][1]) x=son[x][1];
		return x;
	}
	int Get_Min(int x)
	{
		while (son[x][0]) x=son[x][0];
		return x;
	}
	void Del(int X)
	{	
		int x=find(X);
		splay(x,root);
		if (Num[x]>1) { Num[x]--;Size[x]--;return;}
		if (!son[x][0]&&!son[x][1]) { Clear(x);root=0;return;}
		if (!son[x][0])
		{
			root=son[x][1];
			fa[root]=0;
			Clear(x);
			return;
		}
		if (!son[x][1])
		{
			root=son[x][0];
			fa[root]=0;
			Clear(x);
			return;
		}
		int y=Get_Max(son[x][0]);
		splay(y,son[x][0]);
		root=y;
		fa[root]=0;
		son[y][1]=son[x][1];
		fa[son[x][1]]=y;
		update(y);
		Clear(x);
	}
	int Ask_rank(int x)
	{
		int now=root,Rank=1;
		while (Tree[now]!=x)
		{
			if (Tree[now]<=x)
			{
				Rank+=Num[now];
				now=son[now][1];
			}else now=son[now][0];
		}
		return Rank;
	}
	int Asknum_rank(int x)
	{
		int now=root;
		while (x!=1)
		{
			if (Size[son[now][0]]>=x) now=son[now][0];
				else x-=Size[son[now][0]],now=son[now][1];
		}
		return Tree[now];
	}
	int Ask_Prev(int X)
	{
		int x=find(X);
		splay(x,root);
		return Tree[Get_Max(son[x][0])];
	}
	int Ask_Next(int X)
	{
		int x=find(X);
		splay(x,root);
		return Tree[Get_Min(son[x][1])];
	}
}Splay;
int main()
{
	scanf("%d",&n);
	tot=root=0;
	for (int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if (x==1) Splay.Insert(y);
		if (x==2) Splay.Del(y);
		if (x==3) printf("%d\n",Splay.Ask_rank(y));
		if (x==4) printf("%d\n",Splay.Asknum_rank(y));
		if (x==5) Splay.Insert(y),printf("%d\n",Splay.Ask_Prev(y)),Splay.Del(y);
		if (x==6) Splay.Insert(y),printf("%d\n",Splay.Ask_Next(y)),Splay.Del(y);
	}
	return 0;
}
