#include<bits/stdc++.h>
#define ll long long
#define mo 1000000007
using namespace std;
const int N=100100;
int T,n,m,a[N],tot,Next[N*2],head[N],tree[N*2],top,cnt,Stack[N],A[N];
bool vis[N];
ll ans;
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs(int u)
{
	vis[u]=1;
	Stack[++top]=u;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (!vis[v]) dfs(v);
	}
}
void Work()
{
	sort(A+1,A+cnt+1);
	for (int i=0;i<=30;i++)
	{
		int num=0;
		for (int j=1;j<=cnt;j++)
		if (A[j]&(1LL<<i))
		{
			(ans+=(ll)num*A[j]%mo*(1LL<<i)%mo)%=mo;
			num++;
		}
	}
}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		tot=0;
		for (int i=1;i<=n;i++) head[i]=0;
		for (int i=1;i<=m;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,y);add(y,x);
		}
		ans=top=0;
		for (int i=1;i<=n;i++) vis[i]=0;
		for (int i=1;i<=n;i++)
		if (!vis[i])
		{
			dfs(i);
			int j=0;
			cnt=0;
			do
			{
				j=Stack[top--];
				A[++cnt]=a[j];
			}while (j!=i);
			Work();
		}
		printf("%I64d\n",ans);
	}
	return 0;
}

