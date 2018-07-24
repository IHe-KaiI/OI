#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=70010;
int n,L,a[N],tot,Next[N<<1],head[N],tree[N<<1],In[N],cnt,m,root,id[N],Out[N],sum1[N],sum2[N],fa[N],son[N][2],Tree[N];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs(int u,int father)
{
	In[u]=++cnt;id[cnt]=u;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==father) continue;
		dfs(v,u);
	}
	Out[u]=++cnt;
}
void debug()
{
	cout<<"ROOT="<<root<<endl;
	for (int i=1;i<=cnt;i++) cout<<"ID="<<i<<"  left son="<<son[i][0]<<"  right son="<<son[i][1]<<"  father="<<fa[i]<<" sum1="<<sum1[i]<<" sum2="<<sum2[i]<<" value="<<Tree[i]<<endl;
	cout<<endl;
}
void update(int x)
{
	sum1[x]=Tree[x];sum2[x]=0;
	if (son[x][0]) sum1[x]^=sum2[son[x][0]],sum2[x]^=sum1[son[x][0]];
	if (son[x][1]) sum1[x]^=sum2[son[x][1]],sum2[x]^=sum1[son[x][1]];
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
			if (son[z][0]==y^son[y][0]==x) Rotate(x,k);
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
	fa[mid]=father;
	Tree[mid]=a[id[mid]];
	son[father][mid>=father]=mid;
	update(mid);
}
int PREV(int x)
{
	splay(x,root);
	int id=son[x][0];
	while (son[id][1]) id=son[id][1];
	return id;
}
int NEXT(int x)
{
	splay(x,root);
	int id=son[x][1];
	while (son[id][0]) id=son[id][0];
	return id;
}
int query(int x)
{
//	debug();
//	cout<<"In id="<<In[x]<<" Out id="<<Out[x]<<endl;
	int pre=PREV(In[x]),nex=NEXT(Out[x]);
//	cout<<"prev="<<pre<<" next="<<nex<<endl;
	splay(pre,root);
	splay(nex,son[root][1]);
	splay(In[x],son[nex][0]);
	debug();
	return sum2[In[x]];
}
void Insert(int x,int y)
{
	splay(y,root);
	if (!son[y][1]) { fa[x]=y;son[y][1]=x;return;}
	int id=NEXT(x);
	splay(id,son[y][1]);
	fa[x]=id;
	son[id][0]=x;
	splay(x,root);
}
void ADD_SON(int father,int x,int d)
{
	a[++n]=x;
	In[n]=++cnt;
	Tree[cnt]=d;
	Out[n]=++cnt;
	Insert(In[n],In[father]);
	Insert(Out[n],In[n]);
}
void change(int x,int y)
{
	splay(In[x],root);
	Tree[In[x]]^=a[x]^y;
	a[x]=y;
}
int main()
{
	scanf("%d%d",&n,&L);
	for (int i=1;i<=n;i++) { scanf("%d",&a[i]);a[i]%=(L+1);}
	for (int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	cnt=1;
	dfs(1,0);
	cnt++;
	build(1,cnt,0);
	root=(cnt+1)>>1;
	scanf("%d",&m);
	int ans=0;
	for (int i=1;i<=m;i++)
	{
		int id,x,y,z;
		scanf("%d",&id);
		if (id==1)
		{
			scanf("%d",&x);
			x^=ans;
			if (!query(x)) puts("GTY");
				else puts("MeiZ"),ans++;
		}
		if (id==2)
		{
			scanf("%d%d",&x,&y);
			x^=ans;y^=ans;
			change(x,y);
		}
		if (id==3)
		{
			scanf("%d%d%d",&x,&y,&z);
			x^=ans;y^=ans;z^=ans;
			z%=(L+1);
			ADD_SON(x,y,z);
		}
	}
	return 0;
}
