#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,cnt,son[30010][2],Q[30010],fail[30010];
bool danger[30010],visit[30010],In[30010];
char s[30010];
void Insert(int Len)
{
	int id=1;
	for (int i=1;i<=Len;i++)
	{
		if (!son[id][s[i]-'0']) son[id][s[i]-'0']=++cnt;
		id=son[id][s[i]-'0'];
	}
	danger[id]=1;
}
void build_fail()
{
	int t=0,w=1;
	Q[1]=1;fail[1]=0;
	while (t<w)
	{
		int u=Q[++t];
		for (int i=0;i<=1;i++)
		if (son[u][i])
		{
			int k=fail[u];
			fail[son[u][i]]=son[k][i];
			Q[++w]=son[u][i];
		}else son[u][i]=son[fail[u]][i];
		danger[u]|=danger[fail[u]];
	}
}
bool dfs(int u)
{
	visit[u]=1;In[u]=1;
	for (int i=0;i<=1;i++)
	{
		int v=son[u][i];
		if (In[v]) return 1;
		if (!danger[v]&&!visit[v])
		{
			if (dfs(v)) return 1;
		}
	}
	In[u]=0;
	return 0;
}
int main()
{
	scanf("%d",&n);
	cnt=1;
	son[0][0]=son[0][1]=1;
	for (int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		Insert(strlen(s+1));
	}
	build_fail();
	if (dfs(1)) puts("TAK");
		else puts("NIE");
	return 0;
}
