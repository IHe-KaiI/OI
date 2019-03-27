#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#define ll long long
#define mo 998244353
using namespace std;
const int N=25;
const int prime[15]={101,103,107,109,113,127,131,137,139,149,151,157,161,167,173};
int n,m,p[N],ans,num,root;
vector<int>E[N],M[N];
ll f[N],A[N];
bool cmp(int x,int y) { return f[x]<f[y];}
void dfs(int u,int fa)
{
	f[u]=prime[0];
	for (int i=0;i<M[u].size();i++)
	{
		int v=M[u][i];
		if (v==fa) continue;
		dfs(v,u);
	}
	sort(M[u].begin(),M[u].end(),cmp);
	int cnt=0;
	for (int i=0;i<M[u].size();i++)
	{
		int v=M[u][i];
		if (v==fa) continue;
		f[u]=(f[u]+f[v]*prime[++cnt]%mo)%mo;
	}
}
void dfs1(int u,int fa)
{
	f[u]=prime[0];
	num++;
	for (int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if (v==fa||!p[v]) continue;
		dfs1(v,u);
	}
	sort(E[u].begin(),E[u].end(),cmp);
	int cnt=0;
	for (int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if (v==fa||!p[v]) continue;
		f[u]=(f[u]+f[v]*prime[++cnt]%mo)%mo;
	}
}
void DFS(int t,int s)
{
	if (t>n)
	{
		if (s==m)
		{
			root=0;
			for (int i=1;i<=n;i++)
			if (p[i])
			{
				if (!root) root=i;
				f[i]=0;
			}
			num=0;
			dfs1(root,0);
			if (num!=m) return;
			for (int i=1;i<=m;i++)
				if (A[i]==f[root]) { ans++;break;}
		}
		return;
	}
	if (s<m)
	{
		p[t]=1;
		DFS(t+1,s+1);
	}
	p[t]=0;
	DFS(t+1,s);
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		E[x].push_back(y);
		E[y].push_back(x);
	}
	scanf("%d",&m);
	for (int i=1;i<m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		M[x].push_back(y);
		M[y].push_back(x);
	}
	for (int i=1;i<=m;i++)
	{
		for (int j=1;j<=m;j++) f[j]=0;
		dfs(i,0);
		A[i]=f[i];
	}
	ans=0;
	DFS(1,0);
	printf("%d\n",ans);
	return 0;
}
