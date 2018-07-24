#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<map>
using namespace std;
const int N=100010;
int n,m,cnt,Q[N],ans[N],Ans[N],fail[N];
vector<int>V,M,a[N],Tree[N];
map<int,int>son[N];
bool vis[N],mark[N];
void Insert(int X)
{
	int L,x,id=1;
	scanf("%d",&L);
	for (int i=1;i<=L;i++)
	{
		scanf("%d",&x);
		if (!son[id][x]) son[id][x]=++cnt;
		id=son[id][x];
	}
	Tree[id].push_back(X);
}
void Build_Fail()
{
	int t=0,w=1;
	Q[1]=1;
	while (t!=w)
	{
		int u=Q[++t];
		for (map<int,int>::iterator i=son[u].begin();i!=son[u].end();i++)
		{
			int t=i->first,x=fail[u];
			while (!son[x][t]) x=fail[x];
			fail[i->second]=son[x][t];
			Q[++w]=i->second;
		}
	}
}
void Get(int id,int x)
{
	for (int i=x;i;i=fail[i])
	if (!vis[i])
	{
		vis[i]=1;V.push_back(i);
		for (int j=0;j<Tree[i].size();j++)
		if (!mark[Tree[i][j]])
		{
			mark[Tree[i][j]]=1;
			M.push_back(Tree[i][j]);
			ans[Tree[i][j]]++;
			Ans[id]++;
		}
	}else break;
}
void solve(int x)
{
	int now=1;
	for (int i=0;i<a[x].size();i++)
	{
		int t=a[x][i];
		while (!son[now][t]) now=fail[now];
		now=son[now][t];
		Get(x,now);
	}
	for (int i=0;i<V.size();i++) vis[V[i]]=0;
	for (int i=0;i<M.size();i++) mark[M[i]]=0;
	V.clear();M.clear();
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d",&x);
		while (x--) scanf("%d",&y),a[i].push_back(y);
		a[i].push_back(-1);
		scanf("%d",&x);
		while (x--) scanf("%d",&y),a[i].push_back(y);
	}
	cnt=1;
	for (int i=-1;i<=10000;i++) son[0][i]=1;
	fail[1]=0;
	for (int i=1;i<=m;i++) Insert(i);
	Build_Fail();
	for (int i=1;i<=n;i++) solve(i);
	for (int i=1;i<=m;i++) printf("%d\n",ans[i]);
	for (int i=1;i<=n;i++)
	{
		printf("%d",Ans[i]);
		if (i!=n) printf(" ");
	}
	return 0;
}
