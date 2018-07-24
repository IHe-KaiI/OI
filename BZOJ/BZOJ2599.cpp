#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=200010;
int n,k,tot,cnt,ans,Next[N<<1],head[N],tree[N<<1],val[N<<1],size[N],Min[1000100];
bool visit[N];
pair<int,int>Path[N];
void add(int x,int y,int z)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
	val[tot]=z;
}
void GetSize(int u,int fa)
{
	size[u]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa||visit[v]) continue;
		GetSize(v,u);
		size[u]+=size[v];
	}
}
int GetRoot(int u,int fa,int SIZE)
{
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa||visit[v]) continue;
		if (size[v]*2>SIZE) return GetRoot(v,u,SIZE);
	}
	return u;
}
void Work(int u,int fa,int s,int num)
{
	if (s>k) return;
	Path[++cnt]=make_pair(s,num);
	ans=min(ans,num+Min[k-s]);
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==fa||visit[v]) continue;
		Work(v,u,s+val[i],num+1);
	}
}
void Get_Ans(int U)
{
	GetSize(U,0);
	int u=GetRoot(U,0,size[U]);
	visit[u]=1;
	cnt=0;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (visit[v]) continue;
		int last=cnt;
		Work(v,u,val[i],1);
		for (int j=last+1;j<=cnt;j++) Min[Path[j].first]=min(Min[Path[j].first],Path[j].second);
	}
	for (int i=1;i<=cnt;i++) Min[Path[i].first]=1<<29;
	for (int i=head[u];i;i=Next[i])
		if (!visit[tree[i]]) Get_Ans(tree[i]);
}
int main()
{
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n-1;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		x++;y++;
		add(x,y,z);add(y,x,z);
	}
	for (int i=1;i<=k;i++) Min[i]=1<<29;
	ans=1<<29;
	Get_Ans(1);
	if (ans==1<<29) puts("-1");
		else printf("%d\n",ans);
	return 0;
}
