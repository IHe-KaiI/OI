#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=100010;
int n,tot,Next[N<<1],head[N],tree[N<<1],In[N],color[N],Q[N],sum,Max,a[N],f[N],g[N];
char s[N];
bool vis[N];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
int calc(int id,int x) { return (!color[id])^(x&1);}
void dfs(int u,int fa)
{
	bool flag=0;
	int Max1=0,Max2=0;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa||vis[v]) continue;
		flag=1;
		dfs(v,u);
		Max=max(Max,max(Max1+g[v]+a[u],Max2+f[v]+a[u]));
		Max1=max(Max1,f[v]);
		Max2=max(Max2,g[v]);
	}
	f[u]=Max1+a[u];
	if (!flag) g[u]=-(1<<29);
		else g[u]=Max2+a[u];
}
void pre()
{
	int t=0,w=0;
	for (int i=1;i<=n;i++)
		if (In[i]==1&&color[i]) Q[++w]=i;
	while (t<w)
	{
		int u=Q[++t];
		vis[u]=1;
		for (int i=head[u];i;i=Next[i])
		{
			int v=tree[i];
			In[v]--;
			if (In[v]==1&&color[v]) Q[++w]=v;
		}
	}
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
		In[x]++;In[y]++;
	}
	scanf("%s",s+1);
	for (int i=1;i<=n;i++) color[i]=(s[i]=='B');
	pre();
	int root=0;
	sum=Max=0;
	for (int i=1;i<=n;i++)
	if (!vis[i])
	{
		if (!root) root=i;
		if (calc(i,In[i])) sum++,a[i]=2;
		sum+=In[i];
	}
	if (!root) { puts("0");return 0;}
	dfs(root,0);
	printf("%d\n",sum-Max);
	return 0;
}
