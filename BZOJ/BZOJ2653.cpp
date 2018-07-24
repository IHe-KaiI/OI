#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=20010;
int n,m,tot,A[N],Sum[N*20],MaxL[N*20],MaxR[N*20],son[N*20][2],fa[N*20],root[N];
struct node{int x,id;}B[N];
bool cmp(node a,node b) { return a.x<b.x;}
void up(int x)
{
	Sum[x]=Sum[son[x][0]]+Sum[son[x][1]];
	MaxL[x]=max(MaxL[son[x][0]],Sum[son[x][0]]+MaxL[son[x][1]]);
	MaxR[x]=max(MaxR[son[x][1]],Sum[son[x][1]]+MaxR[son[x][0]]);
}
void build(int &id,int l,int r)
{
	id=++tot;
	if (l==r) { Sum[tot]=MaxL[tot]=MaxR[tot]=1;return;}
	int mid=(l+r)>>1;
	build(son[id][0],l,mid);
	build(son[id][1],mid+1,r);
	up(id);
}
void Insert(int ID,int &id,int l,int r,int x,int d)
{
	id=++tot;
	son[id][0]=son[ID][0];
	son[id][1]=son[ID][1];
	Sum[id]=Sum[ID];
	MaxL[id]=MaxL[ID];
	MaxR[id]=MaxR[ID];
	if (l==r) { MaxL[id]=MaxR[id]=Sum[id]=d;return;}
	int mid=(l+r)>>1;
	if (x<=mid) Insert(son[ID][0],son[id][0],l,mid,x,d);
		else Insert(son[ID][1],son[id][1],mid+1,r,x,d);
	up(id);
}
int query_sum(int id,int l,int r,int x,int y)
{
	if (l>r) return 0;
	if (l>y||r<x) return 0;
	if (x<=l&&r<=y) return Sum[id];
	int mid=(l+r)>>1;
	return query_sum(son[id][0],l,mid,x,y)+query_sum(son[id][1],mid+1,r,x,y);
}
int query_R(int id,int l,int r,int x,int y)
{
	if (l>r) return 0;
	if (x==l&&r==y) return MaxR[id];
	int mid=(l+r)>>1;
	if (y<=mid) return query_R(son[id][0],l,mid,x,y);
	if (x>mid) return query_R(son[id][1],mid+1,r,x,y);
	return max(query_R(son[id][0],l,mid,x,mid)+query_sum(id,l,r,mid+1,y),query_R(son[id][1],mid+1,r,mid+1,y));
}
int query_L(int id,int l,int r,int x,int y)
{
	if (l>r) return 0;
	if (x==l&&r==y) return MaxL[id];
	int mid=(l+r)>>1;
	if (y<=mid) return query_L(son[id][0],l,mid,x,y);
	if (x>mid) return query_L(son[id][1],mid+1,r,x,y);
	return max(query_L(son[id][0],l,mid,x,mid),query_sum(id,l,r,x,mid)+query_L(son[id][1],mid+1,r,mid+1,y));
}
bool check(int x,int a,int b,int c,int d)
{
	return (query_sum(root[x],1,n,b+1,c-1)+query_R(root[x],1,n,a,b)+query_L(root[x],1,n,c,d)>=0);
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&A[i]);
		B[i]=(node){A[i],i};
	}
	sort(B+1,B+n+1,cmp);
	build(root[1],1,n);
	for (int i=2;i<=n;i++) Insert(root[i-1],root[i],1,n,B[i-1].id,-1);
	scanf("%d",&m);
	int ans=0;
	while (m--)
	{
		int a,b,c,d,q[4];
		scanf("%d%d%d%d",&a,&b,&c,&d);
		q[0]=(a+ans)%n;q[1]=(b+ans)%n;q[2]=(c+ans)%n;q[3]=(d+ans)%n;
		sort(q,q+4);
		a=q[0]+1;b=q[1]+1;c=q[2]+1;d=q[3]+1;
		int l=1,r=n;
		while (l<r)
		{
			int mid=(l+r+1)>>1;
			if (check(mid,a,b,c,d)) l=mid;
				else r=mid-1;
		}
		ans=B[l].x;
		printf("%d\n",ans);
	}
	return 0;
}
