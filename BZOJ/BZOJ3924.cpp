#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mp make_pair
using namespace std;
const int N=100010;
int n,m,tot,Next[N*2],head[N],tree[N*2],dep[N],First[N],Log[N*6],size[N],root,Time,fa[N];
int tot_TDC,Next_TDC[N*2],head_TDC[N*2],tree_TDC[N*2],num_TDC[N*2];
bool visit[N];
ll sum[N],dis1[N],dis2[N],val[N*2],SUM[N];
pair<int,int>ST[N*6][35];
int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void add(int x,int y,int z)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
	val[tot]=z;
}
void add_TDC(int x,int y,int z)
{
	tot_TDC++;
	Next_TDC[tot_TDC]=head_TDC[x];
	head_TDC[x]=tot_TDC;
	tree_TDC[tot_TDC]=y;
	num_TDC[tot_TDC]=z;
}
void pre_LCA(int u,int father,int depth,ll Sum)
{
	ST[++Time][0]=mp(depth,u);dep[u]=depth;
	First[u]=Time;SUM[u]=Sum;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==father) continue;
		pre_LCA(v,u,depth+1,Sum+val[i]);
		ST[++Time][0]=mp(dep[u],u);
	}
}
void pre_ST()
{
	Log[1]=0;
	for (int i=2;i<=Time;i++) Log[i]=Log[i>>1]+1;
	for (int i=1;i<=Log[Time];i++)
		for (int j=1;j<=Time;j++) ST[j][i]=min(ST[j][i-1],ST[j+(1<<(i-1))][i-1]);
}
pair<int,int> Get_ST(int x,int y)
{
	x=First[x];y=First[y];
	if (x>y) swap(x,y);
	int len=Log[y-x+1];
	return min(ST[x][len],ST[y-(1<<len)+1][len]);
}
int Get_dis(int x,int y) { return SUM[x]+SUM[y]-SUM[Get_ST(x,y).second]*2;}
void Get_Size(int u,int father)
{
	size[u]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (visit[v]||v==father) continue;
		Get_Size(v,u);
		size[u]+=size[v];
	}
}
int Get_CG(int u,int father,int MaxSize)
{
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (visit[v]||v==father) continue;
		if (size[v]+size[v]>MaxSize) return Get_CG(v,u,MaxSize);
	}
	return u;
}
int TDC(int u)
{
	Get_Size(u,0);
	int t=Get_CG(u,0,size[u]);
	visit[t]=1;
	if (!root) root=t;
	for (int i=head[t];i;i=Next[i])
	{
		int v=tree[i];
		if (visit[v]) continue;
		int CG=TDC(v);
		fa[CG]=t;
		add_TDC(t,CG,v);
	}
	return t;
}
void change(int u,int x)
{
	sum[u]+=x;
	for (int i=u;fa[i];i=fa[i])
	{
		int dis=Get_dis(u,fa[i]);
		dis1[fa[i]]+=(ll)x*dis;
		dis2[i]+=(ll)x*dis;
		sum[fa[i]]+=x;
	}
}
ll calc(int u)
{
	ll ans=dis1[u];
	for (int i=u;fa[i];i=fa[i])
	{
		int dis=Get_dis(u,fa[i]);
		ans+=dis1[fa[i]]-dis2[i];
		ans+=(sum[fa[i]]-sum[i])*dis;
	}
	return ans;
}
ll query(int u)
{
	ll now=calc(u);
	for (int i=head_TDC[u];i;i=Next_TDC[i])
	{
		ll X=calc(num_TDC[i]);
		if (X<now) return query(tree_TDC[i]);
	}
	return now;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n-1;i++)
	{
		int x=read(),y=read(),z=read();
		add(x,y,z);add(y,x,z);
	}
	pre_LCA(1,0,1,0);
	pre_ST();
	TDC(1);
	for (int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		change(x,y);
		printf("%lld\n",query(root));
	}
	return 0;
}
