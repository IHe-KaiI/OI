#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#define ll long long
#define Pair pair<ll,int>
#define mp make_pair
using namespace std;
const int N=100010;
int n,K,a[N],A[N],last[N],cnt,root[N];
struct node{int i,l,r,p;ll x;};
struct TREE{int ls,rs;ll tag;Pair Max;}Tree[N*120];
struct cmp
{
	bool operator () (node a,node b) { return a.x<b.x;}
};
priority_queue<node,vector<node>,cmp>Q;
void build(int &id,int l,int r)
{
	id=++cnt;
	if (l==r) { Tree[id].Max=mp(0,l);return;}
	int mid=(l+r)>>1;
	build(Tree[id].ls,l,mid);
	build(Tree[id].rs,mid+1,r);
	Tree[id].Max=max(Tree[Tree[id].ls].Max,Tree[Tree[id].rs].Max);
}
void change(int &id,int ID,int l,int r,int x,int y,int d)
{
	id=++cnt;
	Tree[id]=Tree[ID];
	if (l>y||r<x) return;
	if (x<=l&&r<=y)
	{
		Tree[id].tag+=d;
		Tree[id].Max.first+=d;
		return;
	}
	int mid=(l+r)>>1;
	change(Tree[id].ls,Tree[ID].ls,l,mid,x,y,d);
	change(Tree[id].rs,Tree[ID].rs,mid+1,r,x,y,d);
	Tree[id].Max=max(Tree[Tree[id].ls].Max,Tree[Tree[id].rs].Max);
	Tree[id].Max.first+=Tree[id].tag;
}
Pair query(int id,int l,int r,int x,int y)
{
	if (!id||l>y||r<x) return mp(-(1LL<<60),0);
	if (x<=l&&r<=y) return Tree[id].Max;
	int mid=(l+r)>>1;
	Pair A=max(query(Tree[id].ls,l,mid,x,y),query(Tree[id].rs,mid+1,r,x,y));
	return mp(A.first+Tree[id].tag,A.second);
}
int main()
{
	freopen("data10.in","r",stdin);
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),A[i]=a[i];
	sort(A+1,A+n+1);
	int num=unique(A+1,A+n+1)-A-1;
	for (int i=1;i<=num;i++) last[i]=n+1;
	Tree[0].Max=mp(-(1LL<<60),0);
	build(root[n+1],1,n);
	for (int i=n;i>=1;i--)
	{
		int x=lower_bound(A+1,A+num+1,a[i])-A;
		change(root[i],root[i+1],1,n,i,last[x]-1,a[i]);
		Pair M=query(root[i],1,n,i,n);
		Q.push((node){i,i,n,M.second,M.first});
		last[x]=i;
	}
	K--;
	while (K--)
	{
		node t=Q.top();
		Q.pop();
		Pair ML,MR;
		if (t.p>1) ML=query(root[t.i],1,n,t.l,t.p-1),Q.push((node){t.i,t.l,t.p-1,ML.second,ML.first});
		if (t.p<n) MR=query(root[t.i],1,n,t.p+1,t.r),Q.push((node){t.i,t.p+1,t.r,MR.second,MR.first});
	}
	printf("%lld\n",Q.top().x);
	return 0;
}      
