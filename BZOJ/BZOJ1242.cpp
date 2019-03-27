#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;
const int N=1010,M=1000100;
int n,m,tot,Next[N+M],head[N+M],tree[N+M],A[N],rank[N],Q[N],p[N][N],d[N];
vector<int>E[N];
bool vis[N];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
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
		p[x][y]=p[y][x]=1;
	}
	for (int i=1;i<=n;i++) add(n+1,i);
	int Max=0;
	for (int i=n;i>=1;i--)
	{
		while (1)
		{
			int pos=0;
			for (int j=head[n+Max+1];j;j=Next[j])
			{
				int v=tree[j];
				if (v<=n&&!vis[v])
				{
					vis[v]=1;
					pos=v;
					A[i]=v;
					rank[v]=i;
					break;
				}else head[Max]=j;
			}
			if (pos)
			{
				for (int j=0;j<(int)E[pos].size();j++)
				{
					int v=E[pos][j];
					if (!vis[v])
					{
						d[v]++;
						add(d[v]+n+1,v);
						Max=max(Max,d[v]);
					}
				}
				break;
			}else Max--;
		}
	}
	for (int i=1;i<=n;i++)
	{
		int u=A[i],top=0;
		pair<int,int>Min=make_pair(1<<29,1<<29);
		for (int j=0;j<(int)E[u].size();j++)
		{
			int v=E[u][j];
			if (rank[v]>i) { Q[++top]=v;Min=min(Min,make_pair(rank[v],v));}
		}
		for (int j=1;j<=top;j++)
		if (Q[j]!=Min.second&&!p[Q[j]][Min.second])
		{
			puts("Imperfect");
			exit(0);
		}
	}
	puts("Perfect");
	return 0;
}
