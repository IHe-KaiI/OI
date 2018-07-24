#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
const int N=400100;
int n,tot,Q,Time,Next[N],head[N],tree[N],ST[N][35],First[N],dep[N],Log[N],size[N],fa[N],NOW[N];
int MAX=0;
bool visit[N];
struct PQ
{
	priority_queue<int>heap,DelMark;
	void Insert(int x) { heap.push(x);}
	void Erase(int x) { DelMark.push(x);}
	void UPD()
	{
		while (DelMark.size()&&heap.top()==DelMark.top())
			heap.pop(),DelMark.pop();
	}
	void Pop() { UPD();heap.pop();}
	int Top() { UPD();return heap.top();}
	int se_Top()
	{ 
		int x=Top();
		Pop();
		int ans=Top();
		Insert(x);
		return ans;
	}
	int SIZE() { return heap.size()-DelMark.size();}
}Q1[N],Q2[N],Ans;
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
void pre_lca(int u,int father)
{
	ST[++Time][0]=dep[u]=dep[father]+1;
	First[u]=Time;
	for (int i=head[u];i;i=Next[i])
	if (tree[i]!=father)
	{
		pre_lca(tree[i],u);
		ST[++Time][0]=dep[u];
	}
}
void pre_ST()
{
	Log[1]=0;
	for (int i=2;i<=Time;i++) Log[i]=Log[i>>1]+1;
	for (int i=1;i<=Log[Time];i++)
		for (int j=1;j<=Time;j++) ST[j][i]=min(ST[j+(1<<(i-1))][i-1],ST[j][i-1]);
}
void Get_Size(int u,int father)
{
	size[u]=1;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==father||visit[v]) continue;
		Get_Size(v,u);
		size[u]+=size[v];
	}
}
int Get_CG(int u,int father,int MaxSize)
{
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (visit[v]||v==father) continue;
		if (size[v]+size[v]>MaxSize) return Get_CG(v,u,MaxSize);
	}
	return u;
}
void UPD_Ans(PQ &s,int opt)
{
	if (opt==1)
	{
		if (s.SIZE()>=2) Ans.Insert(s.Top()+s.se_Top());
	}else
	{
		if (s.SIZE()>=2) Ans.Erase(s.Top()+s.se_Top());
	}
}
void DFS(int u,int father,PQ &s,int depth)
{
	s.Insert(depth);
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		if (v==father||visit[v]) continue;
		DFS(v,u,s,depth+1);
	}
}
int TDC(int u)
{
	Get_Size(u,0);
	int t=Get_CG(u,0,size[u]);
	visit[t]=1;
	Q2[t].Insert(0);
	for (int i=head[t];i;i=Next[i])
	{
		int v=tree[i];
		if (visit[v]) continue;
		PQ pq;
		DFS(v,t,pq,1);
		int CG=TDC(v);
		Q1[CG]=pq;Q2[t].Insert(Q1[CG].Top());
		fa[CG]=t;
	}
	UPD_Ans(Q2[t],1);
	return t;
}
int Calc_ST(int u,int v)
{
	u=First[u];v=First[v];
	if (u>v) swap(u,v);
	int len=Log[v-u+1];
	return min(ST[u][len],ST[v-(1<<len)+1][len]);
}
int Get_dis(int u,int v)
{
	return dep[u]+dep[v]-Calc_ST(u,v)*2;
}
void change(int u,int last)
{
	UPD_Ans(Q2[u],2);
	if (last) Q2[u].Insert(0);
		else Q2[u].Erase(0); 
	UPD_Ans(Q2[u],1);
	for (int i=u;fa[i];i=fa[i])
	{
		UPD_Ans(Q2[fa[i]],2);
		if (Q1[i].SIZE()) 
		Q2[fa[i]].Erase(Q1[i].Top());
		int dis=Get_dis(u,fa[i]);
		if (last) Q1[i].Insert(dis);
			else Q1[i].Erase(dis);
		if (Q1[i].SIZE()) 
			Q2[fa[i]].Insert(Q1[i].Top());
		UPD_Ans(Q2[fa[i]],1);
	}
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	pre_lca(1,0);
	pre_ST();
	TDC(1);
	scanf("%d",&Q);
	int Off=n;
	while (Q--)
	{
		char s[2];int x;
		scanf("%s",s);
		if (s[0]=='G')
		{
			if (Off<=1) printf("%d\n",Off-1);
				else printf("%d\n",Ans.Top());
		}else
		{
			scanf("%d",&x);
			change(x,NOW[x]);
			if (NOW[x]==1) Off++;else Off--;
			NOW[x]^=1;
		}
	}
	return 0;
}
