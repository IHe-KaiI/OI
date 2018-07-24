#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int len,n,cnt,son[10000010][5],dep[10000010],fa[10000010],P[10000010],Q[10000010],fail[10000010];
char S[10000010],s[200];
bool visit[10000010];
int calc(char x)
{
	if (x=='S') return 1;
	if (x=='N') return 2;
	if (x=='W') return 3;
	if (x=='E') return 4;
}
void Insert(int Len,int X)
{
	int id=1;
	for (int i=1;i<=Len;i++)
	{
		int x=calc(s[i]);
		if (!son[id][x]) { son[id][x]=++cnt;dep[cnt]=dep[id]+1;fa[cnt]=id;}
		id=son[id][x];
	}
	P[X]=id;
}
void build_fail()
{
	int t=0,w=1;
	Q[1]=1;fail[1]=0;
	while (t<w)
	{
		int u=Q[++t];
		for (int i=1;i<=4;i++)
		if (son[u][i])
		{
			fail[son[u][i]]=son[fail[u]][i];
			Q[++w]=son[u][i];
		}else son[u][i]=son[fail[u]][i];
	}
}
void Work()
{
	int id=1;
	for (int i=1;i<=len;i++)
	{
		int x=calc(S[i]);
		id=son[id][x];
		for (int j=id;j;j=fail[j])
			if (!visit[j]) visit[j]=1;else break;
	}
}
int main()
{
	scanf("%d%d",&len,&n);
	scanf("%s",S+1);
	cnt=1;
	for (int i=1;i<=4;i++) son[0][i]=1;
	for (int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		Insert(strlen(s+1),i);
	}
	build_fail();
	Work();
	for (int i=1;i<=n;i++)
	{
		int ans=0;
		for (int j=P[i];j;j=fa[j])
			if (visit[j]) { ans=dep[j];break;}
		if (ans) printf("%d\n",ans);else puts("0");
	}
	return 0;
}
