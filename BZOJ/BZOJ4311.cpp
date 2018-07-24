#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#define ll long long
using namespace std;
const int N=200100;
int n;
ll ans[N];
struct node{int x,y,s,e;}q[N],Q[N];
vector<node>A;
bool cmp(node a,node b) { return (a.x!=b.x)?a.x<b.x:a.y>b.y;}
int erfen(int l,int r,int A,int B)
{
	while (l<r)
	{
		int mid=(l+r+1)>>1;
		if ((ll)(q[mid-1].y-q[mid].y)*B<(ll)(q[mid].x-q[mid-1].x)*A) l=mid;
			else r=mid-1;
	}
	return l;
}
void solve(int l,int r,vector<node> &A)
{
	int top=0,mid=(l+r)>>1;
	vector<node>B,C;
	for (int i=0;i<A.size();i++)
	if (A[i].s==l&&A[i].e==r)
	{
		while (top>1&&(ll)(q[top].y-A[i].y)*(q[top].x-q[top-1].x)<=(ll)(q[top-1].y-q[top].y)*(A[i].x-q[top].x)) top--;
		q[++top]=A[i];
	}else
	{
		if (A[i].s<=mid) B.push_back((node){A[i].x,A[i].y,A[i].s,min(mid,A[i].e)});
		if (A[i].e>mid) C.push_back((node){A[i].x,A[i].y,max(mid+1,A[i].s),A[i].e});
	}
	for (int i=l;i<=r;i++)
	if (Q[i].x)
	{
		int pos=(top)?erfen(1,top,Q[i].x,Q[i].y):0;
		ans[i]=max(ans[i],(ll)Q[i].x*q[pos].x+(ll)Q[i].y*q[pos].y);
	}
	if (l==r) return;
	solve(l,mid,B);
	solve(mid+1,r,C);
}
int main()
{
	scanf("%d",&n);
	int tot=0;
	for (int i=1;i<=n;i++)
	{
		int opt,x,y;
		scanf("%d",&opt);
		ans[i]=-1;
		if (opt==1)
		{
			scanf("%d%d",&x,&y);
			A.push_back((node){x,y,i,n});
			tot++;
		}
		if (opt==2)
		{
			scanf("%d",&x);
			A[x-1].e=i;
		}
		if (opt==3)
		{
			scanf("%d%d",&x,&y);
			Q[i]=(node){x,y,0,0};
			ans[i]=0;
		}
	}
	sort(A.begin(),A.end(),cmp);
	solve(1,n,A);
	for (int i=1;i<=n;i++) 
		if (ans[i]!=-1) printf("%lld\n",ans[i]);
	return 0;
}
