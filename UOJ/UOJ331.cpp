#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
const int N=100010,M=200010;
int T,n,m,K,mo,tot,Next[M],head[N],tree[M],val[M],dis[N],vis[N];
int tot1,f[N*55],q[N*55],cnt,In[N*55];
struct node{int dis,u;};
struct cmp
{
	bool operator () (node a,node b) { return a.dis>b.dis;}
};
priority_queue<node,vector<node>,cmp>Q;
void add(int x,int y,int z)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
	val[tot]=z;
}
int ID(int x,int y) { return (x-1)*(K+1)+y+1;}
void Dijkstra()
{
	for (int i=1;i<=n;i++) dis[i]=1<<29,vis[i]=0;
	dis[1]=0;
	Q.push((node){0,1});
	while (!Q.empty())
	{
		node t=Q.top();
		Q.pop();
		int u=t.u;
		if (vis[u]) continue;
		vis[u]=1;
		for (int i=head[u];i;i=Next[i])
		{
			int v=tree[i];
			if (dis[v]>dis[u]+val[i])
			{
				dis[v]=dis[u]+val[i];
				Q.push((node){dis[v],v});
			}
		}
	}
}
inline void ADD(int &x,int y) { x+=y;if (x>=mo) x-=mo;}
void solve()
{
	int t=0,w=0;
	for (int i=1;i<=cnt;i++)
		if (!In[i]) q[++w]=i;
	for (int i=1;i<=cnt;i++) f[i]=0;
	f[1]=1;
	while (t<w)
	{
		t++;
		int u=(q[t]-1)/(K+1)+1,k=(q[t]-1)%(K+1);
		for (int i=head[u];i;i=Next[i])
		{
			int v=tree[i];
			if (dis[u]+k+val[i]<=dis[v]+K)
			{
				int id=ID(v,val[i]+k+dis[u]-dis[v]);
				ADD(f[id],f[q[t]]);
				In[id]--;
				if (!In[id]) q[++w]=id;
			}
		}
	}
	int ans=0;
	for (int i=0;i<=K;i++)
	{
		int x=ID(n,i);
		if (In[x]) { puts("-1");return;}
		ADD(ans,f[x]);
	}
	printf("%d\n",ans);
}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d%d%d",&n,&m,&K,&mo);
		tot=tot1=0;
		memset(head,0,sizeof(head));
		for (int i=1;i<=m;i++)
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			add(x,y,z);
		}
		Dijkstra();
		cnt=n*(K+1);
		for (int i=1;i<=cnt;i++) In[i]=0;
		for (int i=1;i<=n;i++)
			for (int j=0;j<=K;j++)
			{
				for (int k=head[i];k;k=Next[k])
				{
					int v=tree[k];
					if (dis[i]+j+val[k]<=dis[v]+K) In[ID(v,dis[i]+j+val[k]-dis[v])]++;
				}
			}
		solve();
	}
	return 0;
}
