#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=1010;
int n,a[N],ans[N];
bool vis[N];
void dfs(int u,int S)
{
	if (vis[u]) { ans[S]=u;return;}
	vis[u]=1;
	dfs(a[u],S);
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		dfs(i,i);
	}
	for (int i=1;i<=n;i++) printf("%d%c",ans[i]," \n"[i==n]);
	return 0;
}

