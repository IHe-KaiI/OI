#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,tot,cnt,root,Tree[100100],size[100100],son[100100][2],fa[100100],f[100100],g[100100],ans[100100];
void update(int x)
{
	size[x]=size[son[x][0]]+size[son[x][1]]+1;
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
			if ((son[y][0]==x)^(son[z][0]==y)) Rotate(x,root);
				else Rotate(y,root);
		}
		Rotate(x,root);
	}
}
int find(int x)
{
	int id=root;
	while (1)
	{
		if (size[son[id][0]]+1==x) return id;
		if (size[son[id][0]]>=x) id=son[id][0];
			else x-=size[son[id][0]]+1,id=son[id][1];
	}
}
int split(int x,int y)
{
	splay(x,root);
	splay(y,son[x][1]);
	return y;
}
void Insert(int p,int X)
{
	int x=find(p),y=find(p+1);
	int id=split(x,y);
	son[id][0]=++tot;
	fa[tot]=id;
	Tree[tot]=X;
	size[tot]=1;
	update(id);
	update(root);
}
void dfs(int x)
{
	if (!x) return;
	dfs(son[x][0]);
	f[++cnt]=Tree[x];
	dfs(son[x][1]);
}
int main()
{
	scanf("%d",&n);
	root=1;tot=2;cnt=0;
	son[1][1]=2;fa[2]=1;size[1]=2;size[2]=1;
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		x++;
		Insert(x,i);
	}
	int id=split(1,2);
	dfs(son[id][0]);
	int len=0;
	for (int i=1;i<=n;i++)
	if (f[i]>g[len]) ans[f[i]]=++len,g[len]=f[i];
	else
	{
		int x=lower_bound(g+1,g+len+1,f[i])-g;
		ans[f[i]]=x;
		g[x]=f[i];
	}
	for (int i=1;i<=n;i++)
	{
		ans[i]=max(ans[i],ans[i-1]);
		printf("%d\n",ans[i]);
	}
	return 0;
}
