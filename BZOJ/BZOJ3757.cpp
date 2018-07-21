#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mp make_pair
#define ll long long
using namespace std;
const int N=100010;
int n,m,Q_tot,cnt,Time,v[N],a[N],tot,Next[N*2],head[N],tree[N*2],w[N],In[N],Out[N],IN[N],p[N*2],Log[N*4],blo[N],num[N];
struct node{int t,x,y,id,TAG;}C[N],Q[N];
ll Ans[N],ans;
pair<int,int>ST[N*4][35];
bool vis[N];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs(int u,int fa,int depth)
{
	ST[++Time][0]=mp(depth,u);
	IN[u]=Time;
	In[u]=++cnt;p[cnt]=u;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa) continue;
		dfs(v,u,depth+1);
		ST[++Time][0]=mp(depth,u);
	}
	Out[u]=++cnt;p[cnt]=u;
}
void pre_ST()
{
	Log[1]=0;
	for (int i=2;i<=Time;i++) Log[i]=Log[i>>1]+1;
	for (int i=1;i<=Log[Time];i++)
		for (int j=1;j<=Time;j++) ST[j][i]=min(ST[j][i-1],ST[j+(1<<(i-1))][i-1]);
}
int LCA(int x,int y)
{
	x=IN[x];y=IN[y];
	if (x>y) swap(x,y);
	int len=Log[y-x+1];
	return (min(ST[x][len],ST[y-(1<<len)+1][len])).second;
}
bool cmp(node a,node b)
{
	if (blo[a.x]==blo[b.x]&&blo[a.y]==blo[b.y]) return a.t<b.t;
	return (blo[a.x]==blo[b.x])?blo[a.y]<blo[b.y]:blo[a.x]<blo[b.x];
}
void change(int x)
{
	if (vis[x]) ans-=(ll)v[a[x]]*w[num[a[x]]--];
		else ans+=(ll)v[a[x]]*w[++num[a[x]]];
	vis[x]^=1;
}
void Change(node &A)
{
	if (vis[A.x]) { change(A.x);swap(a[A.x],A.y);change(A.x);}
		else swap(a[A.x],A.y);
}
int main()
{
	scanf("%d%d%d",&n,&m,&Q_tot);
	for (int i=1;i<=m;i++) scanf("%d",&v[i]);
	for (int i=1;i<=n;i++) scanf("%d",&w[i]);
	for (int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	dfs(1,0,1);
	pre_ST();
	int c=0,q=0;
	for (int i=1;i<=Q_tot;i++)
	{
		int id,x,y;
		scanf("%d%d%d",&id,&x,&y);
		if (!id) C[++c]=(node){i,x,y,0,0};
		else
		{
			if (In[x]>In[y]) swap(x,y);
			q++;
			Q[q]=(node){c,(LCA(x,y)==x)?In[x]:Out[x],In[y],q,(LCA(x,y)==x)?0:LCA(x,y)};
		}
	}
	int block=(int)(pow(cnt,2.0/3.0));
	for (int i=1;i<=cnt;i++) blo[i]=(i-1)/block+1;
	sort(Q+1,Q+q+1,cmp);
	int l=1,r=0,now=0;
	ans=0;
	for (int i=1;i<=q;i++)
	{
		while (l>Q[i].x) change(p[--l]);
		while (r<Q[i].y) change(p[++r]);
		while (l<Q[i].x) change(p[l++]);
		while (r>Q[i].y) change(p[r--]);
		while (Q[i].t>now) Change(C[++now]);
		while (Q[i].t<now) Change(C[now--]);
		if (!Q[i].TAG) Ans[Q[i].id]=ans;
			else { change(Q[i].TAG);Ans[Q[i].id]=ans;change(Q[i].TAG);}
	}
	for (int i=1;i<=q;i++) printf("%lld\n",Ans[i]);
	return 0;
}
