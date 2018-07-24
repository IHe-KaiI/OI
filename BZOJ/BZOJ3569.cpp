#include<cstdio>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<cstring>
using namespace std;
const int N=500100;
int n,m,tot,Next[N<<1],head[N],tree[N<<1],From[N<<1],a[N],A[N],b[31];
bool vis[N],visit[N];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
	From[tot]=x;
}
void dfs(int u,int fa)
{
	visit[u]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (vis[i>>1]||visit[v]) continue;
		vis[i>>1]=1;
		dfs(v,u);
	}
}
void dfs1(int u)
{
	visit[u]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (visit[v]) continue;
		dfs1(v);
		A[u]^=A[v];
		a[i>>1]=A[v];
	}
}
int main()
{
	srand(20020315);
	scanf("%d%d",&n,&m);
	tot=1;
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0);
	for (int i=2;i<=tot;i+=2)
	{
		if (!vis[i>>1])
		{
			int x=(long long)rand()%23333*rand()%((1LL<<31)-1)+1;
			A[From[i]]^=x;
			A[tree[i]]^=x;
			a[i>>1]=x;
		}
	}
	memset(visit,0,sizeof(visit));
	dfs1(1);
	int Q,K,ans=0;
	scanf("%d",&Q);
	while (Q--)
	{
		scanf("%d",&K);
		bool flag=1;
		memset(b,0,sizeof(b));
		for (int i=1;i<=K;i++)
		{
			int x;
			scanf("%d",&x);
			x^=ans;
			x=a[x];
			for (int i=30;i>=0;i--)
			if (x&(1<<i))
			{
				if (!b[i])
				{
					b[i]=x;
					break;
				}
				x^=b[i];
			}
			if (!x) flag=0;
		}
		if (flag) puts("Connected"),ans++;
			else puts("Disconnected");
	}
	return 0;
}
