#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
const int N=200010;
int T,n,m,K,A,a[N],c[N],f[N];
struct node{int x,y;}b[N];
struct cmp
{
	bool operator() (node a,node b) { return a.y<b.y;}
};
priority_queue<node,vector<node>,cmp>Q;
bool cmp(node a,node b) { return a.x<b.x;}
int lowbit(int x) { return x&(-x);}
int get(int x)
{
	int ans=0;
	for (int i=x;i>=1;i-=lowbit(i)) ans+=f[i];
	return ans;
}
void add(int x,int y)
{
	for (int i=x;i<=n;i+=lowbit(i)) f[i]+=y;
}
bool check(int x)
{
	while (!Q.empty()) Q.pop();
	for (int i=1;i<=n;i++)
		c[i]=ceil((double)(max(0,x-a[i]))/A);
	for (int i=1;i<=n;i++) f[i]=0;
	int now=1,tot=0;
	for (int i=1;i<=n;i++)
	{
		while (now<=m&&b[now].x<=i) Q.push(b[now++]);
		while (!Q.empty()&&Q.top().y>=i)
		{
			if (get(i)>=c[i]) break;
			else
			{
				if (tot==K) return 0;
				node t=Q.top();
				Q.pop();
				add(t.x,1);add(t.y+1,-1);
				tot++;
			}
		}
		if (get(i)<c[i]) return 0;
	}
	return 1;
}
int erfen(int l,int r)
{
	while (l<r)
	{
		int mid=(l+r+1)>>1;
		if (check(mid)) l=mid;
			else r=mid-1;
	}
	return l;
}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d%d%d",&n,&m,&K,&A);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		for (int i=1;i<=m;i++)
			scanf("%d%d",&b[i].x,&b[i].y);
		sort(b+1,b+m+1,cmp);
		printf("%d\n",erfen(0,2e8));
	}
	return 0;
}
