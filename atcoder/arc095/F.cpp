#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,tot,Next[200010],head[100010],tree[200010],In[100010],a[100010],cnt,num[100010];
bool vis[100010];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs(int u,bool flag)
{
	vis[u]=1;
	a[++cnt]=u;
	int U=0,Son=0;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (vis[v]) continue;
		Son=v;
		if (In[v]!=1)
		{
			if (U) { puts("-1");exit(0);}
				else U=v;
		}else vis[v]=1,num[u]++;
	}
	if (flag&&!U) dfs(Son,0),num[u]--;
		else if (U) dfs(U,1);
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
	for (int i=1;i<=n;i++)
	if (In[i]==1)
	{
		int v=tree[head[i]],NUM=0;
		for (int j=head[v];j;j=Next[j])
			if (In[tree[j]]>=2) NUM++;
		if (NUM<2) { dfs(i,(n!=1));break;}
	}
	if (!cnt) { puts("-1");return 0;}
	bool flag=0;
	for (int i=1;i<=cnt/2;i++)
	{
		if (num[a[i]]>num[a[cnt-i+1]]) { flag=1;break;}
		if (num[a[i]]<num[a[cnt-i+1]]) break;
	}
	if (flag)
	{
		for (int i=1;i<=cnt/2;i++) swap(a[i],a[cnt-i+1]);
	}
	int now=0;
	for (int i=1;i<=cnt;i++)
	{
		int x=++now;
		for (int j=1;j<=num[a[i]];j++) printf("%d ",++now);
		printf("%d%c",x," \n"[i==cnt]);
	}
	return 0;
}
