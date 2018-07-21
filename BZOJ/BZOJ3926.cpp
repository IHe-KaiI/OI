#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=2000010;
int n,c,a[N],tot,Next[N*2],head[N],tree[N*2],In[N];
struct SAM
{
	int root,cnt,maxlen[N*2],a[N*2][12],father[N*2];
	SAM() { root=cnt=1;}
	int extend(int p,int c)
	{
		int np=++cnt;
		maxlen[np]=maxlen[p]+1;
		while (!a[p][c]&&p) a[p][c]=np,p=father[p];
		if (!p) father[np]=root;
		else
		{
			int q=a[p][c];
			if (maxlen[p]+1==maxlen[q]) father[np]=q;
			else
			{
				int nq=++cnt;
				maxlen[nq]=maxlen[p]+1;
				memcpy(a[nq],a[q],sizeof(a[q]));
				father[nq]=father[q];
				father[np]=father[q]=nq;
				while (a[p][c]==q) a[p][c]=nq,p=father[p];
			}
		}
		return np;
	}
	long long solve()
	{
		long long ans=0;
		for (int i=1;i<=cnt;i++) ans+=maxlen[i]-maxlen[father[i]];
		return ans;
	}
}sam;
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void dfs(int u,int fa,int last)
{
	last=sam.extend(last,a[u]);
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa) continue;
		dfs(v,u,last);
	}
}
int main()
{
	scanf("%d%d",&n,&c);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
		In[x]++;In[y]++;
	}
	for (int i=1;i<=n;i++)
		if (In[i]==1) dfs(i,0,1);
	printf("%lld\n",sam.solve());
	return 0;
}
