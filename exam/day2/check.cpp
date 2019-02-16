#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int K,n,Max,ans;
vector<int>E[5010];
void dfs(int u,int fa,int dis)
{
	if (dis==Max) ans++;
	if (dis>Max) Max=dis,ans=1;
	for (int i=0;i<E[u].size();i++)
		if (E[u][i]!=fa) dfs(E[u][i],u,dis+1);
}
int main()
{
	freopen("diameter.in","r",stdin);
	scanf("%d",&K);
	freopen("diameter.out","r",stdin);
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		E[x].push_back(y);
		E[y].push_back(x);
	}
	for (int i=1;i<=n;i++)
	{
		dfs(i,0,0);
	}
	if (ans/2==K) puts("YES");
		else puts("NO");
	return 0;
}
