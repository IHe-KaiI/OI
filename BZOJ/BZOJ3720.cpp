#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;
const int N=60100;
int n,m,Stack[N],cnt,top,S,SIZE,w[N],fa[N],root[N],belong[N],number[N];
vector<int>E[N<<1],P[N];
struct node
{
	int a[800],size;
	void insert(int x,int f)
	{
		if (f==1)
		{
			if (a[size]<=x) { a[++size]=x;return;}
			int pos;
			for (int i=1;i<=size;i++)
				if (a[i]>x) { pos=i;break;}
			for (int i=size;i>=pos;i--) a[i+1]=a[i];
			size++;
			a[pos]=x;
		}else
		{
			int pos;
			for (int i=1;i<=size;i++)
				if (a[i]==x) { pos=i;break;}
			for (int i=pos;i<=size;i++) a[i]=a[i+1];
			size--;
		}
	}
	int query(int x)
	{
		return upper_bound(a+1,a+size+1,x)-a-1;
	}
}Q[5010];
void dfs(int u,int father)
{
	fa[u]=father;
	for (int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if (v==father) continue;
		if (number[belong[u]]<SIZE) belong[v]=belong[u];
			else belong[v]=++cnt,root[cnt]=v,P[belong[u]].push_back(cnt);
		number[belong[v]]++;
		Q[belong[v]].insert(w[v],1);
		dfs(v,u);
	}
}
int query(int u,int x,int id)
{
	int ans=0;
	if (!id)
	{
		ans+=(w[u]>x);
		for (int i=0;i<E[u].size();i++)
		{
			int v=E[u][i];
			if (v==fa[u]) continue;
			if (belong[v]==belong[S]) ans+=query(v,x,0);
				else ans+=query(belong[v],x,1);
		}
	}
	else
	{
		ans+=number[u]-Q[u].query(x);
		for (int i=0;i<P[u].size();i++)
		{
			int v=P[u][i];
			ans+=query(v,x,1);
		}
	}
	return ans;
}
int main()
{
	scanf("%d",&n);
	SIZE=sqrt(log(n)/log(2.0)*n);
	for (int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		E[u].push_back(v);
		E[v].push_back(u);
	}
	for (int i=1;i<=n;i++) scanf("%d",&w[i]);
	cnt=1;
	number[1]=root[1]=1;
	Q[1].insert(w[1],1);
	dfs(1,0);
	scanf("%d",&m);
	int ans=0;
	while (m--)
	{
		int id,x,y;
		scanf("%d%d%d",&id,&x,&y);
		x^=ans;y^=ans;
		if (id==0)
		{
			S=x;
			ans=query(x,y,0);
			printf("%d\n",ans);
		}
		if (id==1)
		{
			Q[belong[x]].insert(w[x],-1);
			Q[belong[x]].insert(y,1);
			w[x]=y;
		}
		if (id==2)
		{
			w[++n]=y;
			E[x].push_back(n);
			if (number[belong[x]]<SIZE) belong[n]=belong[x];
				else belong[n]=++cnt,root[cnt]=n,P[belong[x]].push_back(cnt);
			number[belong[n]]++;
			Q[belong[n]].insert(y,1);
		}
	}
	return 0;
}
