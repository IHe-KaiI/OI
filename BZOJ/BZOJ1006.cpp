#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#define mp make_pair
using namespace std;
const int N=10010;
int n,m,A[N],vis[N],p[N],label[N];
vector<int>E[N];
priority_queue<pair<int,int> >Q;
void Build()
{
	for (int i=1;i<=n;i++) Q.push(mp(0,i));
	for (int i=n;i>=1;i--)
	{
		int id=Q.top().second;
		Q.pop();
		if (vis[id]) continue;
		A[i]=id;
		vis[id]=1;
		for (int j=0;j<E[id].size();j++)
		{
			int k=E[id][j];
			if (!vis[k])
			{
				p[k]++;
				Q.push(mp(p[k],k));
			}
		}
		i--;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		E[x].push_back(y);
		E[y].push_back(x);
	}
	Build();
	memset(vis,0,sizeof(vis));
	for (int i=n;i>=1;i--)
	{
		int u=A[i];
		for (int j=0;j<E[u].size();j++)
		{
			int k=E[u][j];
			vis[label[k]]=u;
		}
		for (int j=1;!label[u];j++)
			if (vis[j]!=u) label[u]=j;
	}
	int ans=0;
	for (int i=1;i<=n;i++) ans=max(ans,label[i]);
	printf("%d\n",ans);
	return 0;
}
