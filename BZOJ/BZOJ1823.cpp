#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int tot,cnt,top,NUM,n,m,Next[4010],head[210],tree[4010],dfn[210],low[210],Stack[210],belong[210];
bool In[210];
int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int Read()
{
	char ch=getchar();
	while (ch!='m'&&ch!='h') ch=getchar();
	return read()*2+(ch=='m');
}
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void Tarjan(int u)
{
	dfn[u]=low[u]=++cnt;Stack[++top]=u;
	In[u]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (!dfn[v])
		{
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if (In[v]) low[u]=min(low[u],dfn[v]);
	}
	if (dfn[u]==low[u])
	{
		int i;
		NUM++;
		do
		{
			i=Stack[top--];
			belong[i]=NUM;
			In[i]=0;
		}while (i!=u);
	}
}
int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		memset(head,0,sizeof(head));
		tot=cnt=top=NUM=0;
		scanf("%d%d",&n,&m);
		for (int i=1;i<=m;i++)
		{
			int x=Read(),y=Read();
			add(x^1,y);add(y^1,x);
		}
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(In,0,sizeof(In));
		for (int i=2;i<=n*2+1;i++)
			if (!dfn[i]) Tarjan(i);
		bool flag=1;
		for (int i=1;i<=n;i++)
			if (belong[i<<1]==belong[i<<1|1]) { flag=0;break;}
		if (flag) puts("GOOD");else puts("BAD");
	}
	return 0;
}
