#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=50000;
int n,root,cnt,Tree[N],fa[N],son[N][2];
void Rotate(int x,int &k)
{
	int y=fa[x],z=fa[y],l,r;
	if (son[y][0]==x) l=0;else l=1;
	r=l^1;
	if (y==k) k=x;
	else
	{
		if (son[z][0]==y) son[z][0]=x;
			else son[z][1]=x;
	}
	fa[x]=z;fa[y]=x;fa[son[x][r]]=y;
	son[y][l]=son[x][r];son[x][r]=y;
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
void Insert(int x)
{
	Tree[++cnt]=x;
	if (!root) { root=cnt;return;}
	int id=root,lastid;
	while (id)
	{
		lastid=id;
		if (x<Tree[id]) id=son[id][0];
			else id=son[id][1];
	}
	if (x<Tree[lastid]) son[lastid][0]=cnt;
		else son[lastid][1]=cnt;
	fa[cnt]=lastid;
	splay(cnt,root);
}
int GetPrev(int x)
{
	splay(x,root);
	if (!son[x][0]) return -1<<29;
	int id=son[x][0];
	while (son[id][1]) id=son[id][1];
	return Tree[id];
}
int GetNext(int x)
{
	splay(x,root);
	if (!son[x][1]) return 1<<29;
	int id=son[x][1];
	while (son[id][0]) id=son[id][0];
	return Tree[id];
}
int main()
{
	scanf("%d",&n);
	root=0;
	int ans=0;
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		Insert(x);
		if (i!=1) ans+=min(x-GetPrev(cnt),GetNext(cnt)-x);
			else ans+=x;
	}
	printf("%d\n",ans);
	return 0;
}
