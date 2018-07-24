#include<cstdio>
#include<algorithm>
using namespace std;
const int N=300010;
int n,m,a[N],Xor[N],son[N][2],fa[N],Stack[N],rev[N];
bool isRoot(int x) { return (son[fa[x]][0]!=x&&son[fa[x]][1]!=x);}
void update(int x)
{
	Xor[x]=Xor[son[x][0]]^Xor[son[x][1]]^a[x];
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
	if (x==son[y][0]) l=0;else l=1;
	r=l^1;
	if (!isRoot(y))
	{
		if (son[z][0]==y) son[z][0]=x;
			else son[z][1]=x;
	}
	fa[x]=z;fa[y]=x;fa[son[x][r]]=y;
	son[y][l]=son[x][r];son[x][r]=y;
	update(y);update(x);
}
void splay(int x)
{
	int top=0;Stack[++top]=x;
	for (int i=x;!isRoot(i);i=fa[i]) Stack[++top]=fa[i];
	while (top) pushdown(Stack[top--]);
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
}
void change(int x,int y)
{
	splay(x);
	a[x]=y;
	update(x);
}
int query(int x,int y)
{
	MakeRoot(x);
	access(y);
	splay(y);
	return Xor[y];
}
int GetRoot(int x)
{
	access(x);
	splay(x);
	while (son[x][0]) x=son[x][0];
	return x;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	while (m--)
	{
		int id,x,y;
		scanf("%d%d%d",&id,&x,&y);
		if (id==0) printf("%d\n",query(x,y));
		if (id==1)
		{
			if (GetRoot(x)!=GetRoot(y)) link(x,y);
		}
		if (id==2)
		{
			if (GetRoot(x)==GetRoot(y)) cut(x,y);
		}
		if (id==3) change(x,y);
	}
	return 0;
}
