#include<bits/stdc++.h>
using namespace std;
const int MN=1e5;
struct node{int l,r;vector<int> v;}t[MN*32+5];
int a[MN+5],rt,tn;long long ans;
void ins(int&k,int x,int d)
{
	if(!k)k=++tn;
	t[k].v.push_back(x);
	if(--d<0)return;
	ins(x&(1<<d)?t[k].r:t[k].l,x,d);
}
int query(int k,int x,int d)
{
	if(--d<0)return 0;
	int A=x&(1<<d)?t[k].r:t[k].l;
	return A?query(A,x,d):(1<<d)+query(t[k].l^t[k].r^A,x,d);
}
void solve(int k,int d)
{
	--d;
	if(t[k].l)solve(t[k].l,d);
	if(t[k].r)solve(t[k].r,d);
	if(t[k].l&&t[k].r)
	{
		int x=1<<30,i;
		for(i=0;i<t[t[k].l].v.size();++i)
			x=min(x,query(t[k].r,t[t[k].l].v[i],d));
		ans+=x+(1<<d);
	}
}
int main()
{
	freopen("secret.in","r",stdin);
	freopen("secret.out","w",stdout);
	int n,i;
	scanf("%d",&n);
	for(i=1;i<=n;++i)scanf("%d",&a[i]),a[i]^=a[i-1];
	for(i=0;i<=n;++i)ins(rt,a[i],30);
	solve(rt,30);
	printf("%lld",ans);
}
