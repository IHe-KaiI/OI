#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=200010;
int n,m,root[N],son[N*30][2],cnt,Tree[N*30],size[N*30];
void build(int l,int r,int &id)
{
	id=++cnt;
	if (l==r) { Tree[id]=l;size[id]=1;return;}
	int mid=(l+r)>>1;
	build(l,mid,son[id][0]);
	build(mid+1,r,son[id][1]);
}
void Insert(int &id,int ID,int l,int r,int x,int y,int SIZE)
{
	id=++cnt;
	son[id][0]=son[ID][0];
	son[id][1]=son[ID][1];
	if (l==r) { Tree[id]=y;size[id]=size[ID]+SIZE;return;}
	int mid=(l+r)>>1;
	if (x<=mid) Insert(son[id][0],son[ID][0],l,mid,x,y,SIZE);
		else Insert(son[id][1],son[ID][1],mid+1,r,x,y,SIZE);
}
int query(int id,int l,int r,int x)
{
	if (l==r) return id;
	int mid=(l+r)>>1;
	if (x<=mid) return query(son[id][0],l,mid,x);
		else return query(son[id][1],mid+1,r,x);
}
int get(int x,int now)
{
	int fa=query(root[now],1,n,x);
	if (x==Tree[fa]) return fa;
		else return get(Tree[fa],now);
}
void Union(int x,int y,int now)
{
	if (size[x]>size[y]) swap(x,y);
	Insert(root[now],root[now-1],1,n,Tree[x],Tree[y],size[x]);
	if (size[x]==size[y]) Insert(root[now],root[now],1,n,Tree[y],Tree[y],size[x]+1);
}
int main()
{
	scanf("%d%d",&n,&m);
	build(1,n,root[0]);
	int ans=0;
	for (int i=1;i<=m;i++)
	{
		int id,x,y;
		scanf("%d",&id);
		if (id==1)
		{
			scanf("%d%d",&x,&y);
			x^=ans;y^=ans;
			x=get(x,i-1);y=get(y,i-1);
			Union(x,y,i);
		}
		if (id==2)
		{
			scanf("%d",&x);
			x^=ans;
			root[i]=root[x];
		}
		if (id==3)
		{
			scanf("%d%d",&x,&y);
			root[i]=root[i-1];
			x^=ans;y^=ans;
			if (get(x,i-1)==get(y,i-1)) ans=1;
				else ans=0;
			printf("%d\n",ans);
		}
	}
	return 0;
}
