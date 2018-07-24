#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,a[20010],A[20010],num,tot,q,Tree[4000010],son[4000010][2],Root[200010];
struct Segment_Tree
{
	void Insert(int &id,int l,int r,int x,int y)
	{
		if (!id) id=++tot;
		if (l==r) { Tree[id]+=y;return;}
		int mid=(l+r)>>1;
		if (x<=mid) Insert(son[id][0],l,mid,x,y);
			else Insert(son[id][1],mid+1,r,x,y);
		Tree[id]=Tree[son[id][0]]+Tree[son[id][1]];
	}
	int query(int id,int l,int r,int x,int y)
	{
		if (!id) return 0;
		if (l>y||r<x) return 0;
		if (x<=l&&r<=y) return Tree[id];
		int mid=(l+r)>>1;
		return query(son[id][0],l,mid,x,y)+query(son[id][1],mid+1,r,x,y);
	}
}TREE;
int lowbit(int x) { return x&(-x);}
void Insert(int x,int d,int X)
{
	for (int i=x;i<=n;i+=lowbit(i)) TREE.Insert(Root[i],1,num,d,X);
}
int query(int x,int d)
{
	int ans=0;
	for (int i=x;i>=1;i-=lowbit(i)) ans+=TREE.query(Root[i],1,num,1,d);
	return ans;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),A[i]=a[i];
	sort(A+1,A+n+1);
	num=unique(A+1,A+n+1)-A-1;
	for (int i=1;i<=n;i++) a[i]=lower_bound(A+1,A+num+1,a[i])-A,Insert(i,a[i],1);
	scanf("%d",&q);
	int ans=0;
	for (int i=2;i<=n;i++) ans+=i-query(i,a[i]);
	printf("%d\n",ans);
	while (q--)
	{
		int i,j;
		scanf("%d%d",&i,&j);
		if (i>j) swap(i,j);
		int x=a[i],y=a[j];
		Insert(i,x,-1);Insert(j,y,-1);
		Insert(j,x,1);Insert(i,y,1);
		if (a[i]>a[j]) ans--;
		if (a[i]<a[j]) ans++;
		ans+=j-1-query(j-1,x)-(i-query(i,x));
		ans-=query(j-1,x-1)-query(i,x-1);
		ans-=j-1-query(j-1,y)-(i-query(i,y));
		ans+=query(j-1,y-1)-query(i,y-1);
		swap(a[i],a[j]);
		printf("%d\n",ans);
	}
	return 0;
}
