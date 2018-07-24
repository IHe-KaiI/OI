#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#define ll long long
#define mo 1000000007
using namespace std;
const int N=500100;
int n,tot,top,Next[N<<6],head[N<<2],tree[N<<6],pos[N],dfn[N<<2],low[N<<2],cnt,Stack[N<<2],number,belong[N<<2],IN[N<<2],Q[N<<2];
ll a[N],r[N],Min[N<<2],Max[N<<2],L[N<<2],R[N<<2];
bool In[N<<2];
vector<int>E[N<<2];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void build(int l,int r,int id)
{
	Min[id]=1LL<<62;Max[id]=-1LL<<62;
	if (l==r)
	{
		pos[l]=id;
		return;
	}
	int mid=(l+r)>>1;
	add(id,id<<1);
	add(id,id<<1|1);
	build(l,mid,id<<1);
	build(mid+1,r,id<<1|1);
}
void update(int l,int r,int id,int pos,int x,int y)
{
	if (l>y||r<x) return;
	if (x<=l&&r<=y)
	{
		add(pos,id);
		return;
	}
	int mid=(l+r)>>1;
	update(l,mid,id<<1,pos,x,y);
	update(mid+1,r,id<<1|1,pos,x,y);
}
void Tarjan(int u)
{
	dfn[u]=low[u]=++cnt;
	In[u]=1;Stack[++top]=u;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (!dfn[v]) Tarjan(v),low[u]=min(low[u],low[v]);
			else if (In[v]) low[u]=min(low[u],dfn[v]);
	}
	if (low[u]==dfn[u])
	{
		number++;
		L[number]=1LL<<62;R[number]=-1LL<<62;
		int i;
		do
		{
			i=Stack[top--];
			belong[i]=number;
			In[i]=0;
			L[number]=min(L[number],Min[i]);
			R[number]=max(R[number],Max[i]);
		}while (i!=u);
	}
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld%lld",&a[i],&r[i]);
	build(1,n,1);
	for (int i=1;i<=n;i++) Min[pos[i]]=Max[pos[i]]=i;
	a[n+1]=1LL<<60;
	for (int i=1;i<=n;i++)
		update(1,n,1,pos[i],lower_bound(a+1,a+n+2,a[i]-r[i])-a,upper_bound(a+1,a+n+2,a[i]+r[i])-a-1);
	for (int i=1;i<=n<<2;i++)
		if (!dfn[i]) Tarjan(i);
	for (int i=1;i<=n<<2;i++)
		for (int j=head[i];j;j=Next[j])
		{
			int k=tree[j];
			if (belong[i]!=belong[k]) E[belong[k]].push_back(belong[i]),IN[belong[i]]++;
		}
	int t=0,w=0;
	for (int i=1;i<=number;i++)
		if (!IN[i]) Q[++w]=i;
	while (t<w)
	{
		int u=Q[++t];
		for (int i=0;i<E[u].size();i++)
		{
			int v=E[u][i];
			L[v]=min(L[v],L[u]);
			R[v]=max(R[v],R[u]);
			IN[v]--;
			if (!IN[v]) Q[++w]=v;
		}
	}
	int ans=0;
	for (int i=1;i<=n;i++)
		(ans+=(ll)i*(R[belong[pos[i]]]-L[belong[pos[i]]]+1)%mo)%=mo;
	printf("%d\n",ans);
	return 0;
}
