#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=100100,NlgN=3000100,NlgN2=42000100;
int n,m,last[N],root[N],son[NlgN][2],Max[NlgN2],ID[NlgN],ls[NlgN2],rs[NlgN2],cnt,tot;
struct node{int val,NEXT,PREV,pos;}a[N];
bool cmp(node a,node b) { return a.PREV<b.PREV;}
void modify(int lastid,int &id,int l,int r,int x,int val)
{
	id=++tot;
	Max[id]=max(val,Max[lastid]);
	if (l==r) return;
	ls[id]=ls[lastid];
	rs[id]=rs[lastid];
	int mid=(l+r)>>1;
	if (x<=mid) modify(ls[lastid],ls[id],l,mid,x,val);
		else modify(rs[lastid],rs[id],mid+1,r,x,val);
}
void Insert(int lastid,int &id,int l,int r,int x,int nex,int val)
{
	id=++cnt;
	modify(ID[lastid],ID[id],1,n,nex,val);
	if (l==r) return;
	son[id][0]=son[lastid][0];
	son[id][1]=son[lastid][1];
	int mid=(l+r)>>1;
	if (x<=mid) Insert(son[lastid][0],son[id][0],l,mid,x,nex,val);
		else Insert(son[lastid][1],son[id][1],mid+1,r,x,nex,val);
}
int Query(int id,int l,int r,int x)
{
	if (x<=l) return Max[id];
	int mid=(l+r)>>1,ans=0;
	if (x<=mid) ans=Query(ls[id],l,mid,x);
	return max(ans,Query(rs[id],mid+1,r,x));
}
int query(int id,int l,int r,int x,int y)
{
	if (l>y||r<x) return 0;
	if (x<=l&&r<=y) return Query(ID[id],1,n,y);
	int mid=(l+r)>>1;
	return max(query(son[id][0],l,mid,x,y),query(son[id][1],mid+1,r,x,y));
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) { scanf("%d",&a[i].val);a[i].pos=i;}
	for (int i=1;i<=n;i++) a[i].PREV=last[a[i].val]+1,last[a[i].val]=i;
	for (int i=0;i<=n;i++) last[i]=n+1;
	for (int i=n;i>=1;i--) a[i].NEXT=last[a[i].val]-1,last[a[i].val]=i;
	sort(a+1,a+n+1,cmp);
	int now=1;
	for (int i=1;i<=n;i++)
	{
		root[i]=root[i-1];
		while (a[now].PREV<=i&&now<=n)
			Insert(root[i],root[i],1,n,a[now].pos,a[now].NEXT,a[now].val),now++;
	}
	int ans=0;
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		x=(x+ans)%n+1;y=(y+ans)%n+1;
		if (x>y) swap(x,y);
		ans=query(root[x],1,n,x,y);
		printf("%d\n",ans);
	}
	return 0;
}
