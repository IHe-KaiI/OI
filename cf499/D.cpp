#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,son[1000010][2],a[1000010],b[1000010],ans[1000010];
char s[20];
void dfs(int u)
{
	if (!son[u][0]) return;
	dfs(son[u][0]);
	if (!son[u][1]) { a[u]=!a[son[u][0]];return;}
	dfs(son[u][1]);
	if (b[u]==1) a[u]=a[son[u][0]]&a[son[u][1]];
	if (b[u]==2) a[u]=a[son[u][0]]|a[son[u][1]];
	if (b[u]==3) a[u]=a[son[u][0]]^a[son[u][1]];
}
void dfs1(int u,bool x)
{
	if (!son[u][0])
	{
		if (x) ans[u]=a[1]^1;
			else ans[u]=a[1];
		return;
	}
	if (!son[u][1]) { dfs1(son[u][0],x&1);return;}
	if (b[u]==1)
	{
		if (a[son[u][1]]==1) dfs1(son[u][0],x&1);
			else dfs1(son[u][0],0);
		if (a[son[u][0]]==1) dfs1(son[u][1],x&1);
			else dfs1(son[u][1],0);
	}
	if (b[u]==2)
	{
		if (a[son[u][1]]==0) dfs1(son[u][0],x&1);
			else dfs1(son[u][0],0);
		if (a[son[u][0]]==0) dfs1(son[u][1],x&1);
			else dfs1(son[u][1],0);

	}
	if (b[u]==3)
	{
		dfs1(son[u][0],x&1);
		dfs1(son[u][1],x&1);
	}
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%s",s);
		if (s[0]=='A') { scanf("%d%d",&son[i][0],&son[i][1]);b[i]=1;}
		if (s[0]=='O') { scanf("%d%d",&son[i][0],&son[i][1]);b[i]=2;}
		if (s[0]=='X') { scanf("%d%d",&son[i][0],&son[i][1]);b[i]=3;}
		if (s[0]=='N') { scanf("%d",&son[i][0]);b[i]=4;}
		if (s[0]=='I') { scanf("%d",&a[i]);b[i]=5;}
	}
	dfs(1);
	dfs1(1,1);
	for (int i=1;i<=n;i++)
		if (!son[i][0]) printf("%d",ans[i]);
	return 0;
}
