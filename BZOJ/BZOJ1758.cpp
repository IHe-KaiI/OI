#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define eps 1e-4
#define fi first
#define se second
using namespace std;
const int N=100100;
int n,L,R,tot,Next[N<<1],head[N],tree[N<<1],size[N],Q[N],MaxLen,Len;
double val[N<<1],f[N],g[N],P[N],ans;
bool visit[N];
pair<int,int>A[N];
void add(int x,int y,double z)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
	val[tot]=z;
}
void Get_Size(int u,int fa)
{
	size[u]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v!=fa&&!visit[v])
		{
			Get_Size(v,u);
			size[u]+=size[v];
		}
	}
}
int Get_Root(int u,int fa,int MaxSize)
{
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (visit[v]||v==fa) continue;
		if (size[v]+size[v]>MaxSize) return Get_Root(v,u,MaxSize);
	}
	return u;
}
void Work(int u,double s,double X,int dep,int fa)
{
	if (dep>R) return;
	Len=max(Len,dep);
	g[dep]=max(g[dep],s);
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v!=fa&&!visit[v]) Work(v,s+val[i]-X,X,dep+1,u);
	}
}
void check(int t)
{
	Get_Size(t,0);
	int u=Get_Root(t,0,size[t]),num=0;
	visit[u]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (visit[v]) continue;
		A[++num]=make_pair(size[v],i);
	}
	sort(A+1,A+num+1);
	double l=ans,r=1e6;
	while (l<r-eps)
	{
		double X=(l+r)/2;
		bool flag=0;
		MaxLen=0;
		for (int ID=1;ID<=num;ID++)
		{
			Len=0;
			Work(tree[A[ID].se],val[A[ID].se]-X,X,1,0);
			int j=MaxLen,t=1,w=0;
			for (int i=1;i<=Len;i++)
			{
				while (i+j>=L&&j>=0)
				{
					while (t<=w&&f[j]>=P[w]) w--;
					Q[++w]=j;P[w]=f[j];
					j--;
				}
				while (t<=w&&i+Q[t]>R) t++;
				if (t<=w&&g[i]+P[t]>=0) { flag=1;break;}
			}
			MaxLen=max(MaxLen,Len);
			for (int i=1;i<=Len;i++) f[i]=max(f[i],g[i]);
			for (int i=1;i<=Len;i++) g[i]=-1e18;
			if (flag) break;
		}
		for (int i=1;i<=MaxLen;i++) f[i]=-1e18;
		if (flag) l=X;else r=X;
	}
	ans=l;
	for (int i=head[u];i;i=Next[i])
		if (!visit[tree[i]]) check(tree[i]);
}
int main()
{
	scanf("%d",&n);
	scanf("%d%d",&L,&R);
	for (int i=1;i<=n-1;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);add(y,x,z);
	}
	ans=0;
	for (int i=1;i<=n;i++) f[i]=g[i]=-1e18;
	check(1);
	printf("%.3lf\n",ans);
	return 0;
}
