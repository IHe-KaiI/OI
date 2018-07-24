#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;
int n,B,top,tot,Stack[1010],belong[1010],root[1010];
vector<int>E[1010];
void dfs(int u,int fa)
{
	int now=top;
	for (int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if (v==fa) continue;
		dfs(v,u);
		if (top-now>=B)
		{
			tot++;
			root[tot]=u;
			while (top>now) belong[Stack[top--]]=tot;
		}
	}
	Stack[++top]=u;
}
int main()
{
	scanf("%d%d",&n,&B);
	for (int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		E[x].push_back(y);
		E[y].push_back(x);
	}
	dfs(1,0);
	while (top) belong[Stack[top--]]=tot;
	printf("%d\n",tot);
	for (int i=1;i<=n;i++) printf("%d%c",belong[i]," \n"[i==n]);
	for (int i=1;i<=tot;i++) printf("%d%c",root[i]," \n"[i==tot]);
	return 0;
}
