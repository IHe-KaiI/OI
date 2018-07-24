#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
int n,m,tot,Next[100100],head[100100],tree[100100],size[100100],root[100100];
ll sum[100100],ans;
struct node{int val,X,left,right,dist;}Tree[100100];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
int merge(int A,int B)
{
	if (!A||!B) return A^B;
	if (Tree[A].val<Tree[B].val) swap(A,B);
	int tmp=merge(Tree[A].right,B);
	Tree[A].right=tmp;
	if (Tree[Tree[A].left].dist<Tree[Tree[A].right].dist) swap(Tree[A].left,Tree[A].right);
	Tree[A].dist=Tree[Tree[A].right].dist+1;
	return A;
}
int POP(int A) { return merge(Tree[A].left,Tree[A].right);}
void dfs(int u)
{
	size[u]=1;sum[u]=Tree[u].val;
	for (int i=head[u];i;i=Next[i])
	{
		int v=tree[i];
		dfs(v);
		sum[u]+=sum[v];size[u]+=size[v];
		root[u]=merge(root[u],root[v]);
	}
	while (sum[u]>m)
	{	
		sum[u]-=Tree[root[u]].val;
		size[u]--;
		root[u]=POP(root[u]);
	}
	ans=max(ans,(ll)size[u]*Tree[u].X);
}
int main()
{
	scanf("%d%d",&n,&m);
	Tree[0].dist=-1;
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d%d%d",&x,&Tree[i].val,&Tree[i].X);
		root[i]=i;
		add(x,i);
	}
	ans=0;
	dfs(1);
	printf("%lld\n",ans);
	return 0;
}
