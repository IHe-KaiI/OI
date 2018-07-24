#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=100100;
int n,q[N];
ll S,T,g[N];
struct node{ll d,c,r,w,g;}a[N],b[N];
bool cmp(node a,node b) { return a.d<b.d;}
long double Calc(int j,int k)
{
	long double X=(long double)((a[j].d+1)*a[j].w-(a[k].d+1)*a[k].w-a[j].g-a[j].r+a[k].g+a[k].r);
	if (a[j].w==a[k].w) return (X<0)?1LL<<60:-(1LL<<60);
	return X/(long double)(a[j].w-a[k].w);
}
void CDQ(int l,int r)
{
	if (l==r) return;
	int mid=(l+r)/2;
	CDQ(l,mid);
	int top=0;
	for (int i=l;i<=mid;i++)
	if (a[i].g>=0)
	{
		while (top>1&&Calc(q[top-1],q[top])>=Calc(q[top],i)) top--;
		q[++top]=i;
	}
	int head=1;
	for (int i=mid+1;i<=r;i++)	
	{
		while (head<top&&Calc(q[head],q[head+1])<=a[i].d) head++;
		ll sum=(a[i].d-a[q[head]].d-1)*a[q[head]].w+a[q[head]].g+a[q[head]].r;
		if (sum>=a[i].c) a[i].g=max(a[i].g,sum-a[i].c);
	}
	CDQ(mid+1,r);
	int i=l,j=mid+1,cnt=0;
	while (i<=mid&&j<=r)
	{
		if (a[i].w<a[j].w) b[++cnt]=a[i++];
			else b[++cnt]=a[j++];
	}
	for (;i<=mid;i++) b[++cnt]=a[i];
	for (;j<=r;j++) b[++cnt]=a[j];
	for (int k=l;k<=r;k++) a[k]=b[k-l+1];
}
int main() 
{
	int CaseT=0; 	
	while (true)
	{
		scanf("%d%lld%lld",&n,&S,&T);
		if (n==0&&S==0&&T==0) break;
		for (int i=1;i<=n;i++)
		{
			scanf("%lld%lld%lld%lld",&a[i].d,&a[i].c,&a[i].r,&a[i].w);
			a[i].g=-1LL<<60;
		}
		a[++n]=(node){0,0,0,0,S};
		sort(a+1,a+n+1,cmp);
		CDQ(1,n);
		ll ans=0;
		for (int i=1;i<=n;i++)
			if (a[i].g>=0) ans=max(ans,a[i].g+(T-a[i].d)*a[i].w+a[i].r);
		printf("Case %d: %lld\n",++CaseT,ans);
	}
	return 0;
}
