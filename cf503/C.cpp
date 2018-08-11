#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#define ll long long
using namespace std;
const int N=3010;
int n,m,p[N],P[N],A[N];
struct node{int x,y;}a[N];
vector<node>q[N];
vector<int>vis[N];
bool cmp(node a,node b) { return a.y<b.y;}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		p[a[i].x]++;
		q[a[i].x].push_back(a[i]);
		vis[a[i].x].push_back(0);
	}
	for (int i=1;i<=m;i++) sort(q[i].begin(),q[i].end(),cmp);
	int Max=1;
	for (int i=2;i<=m;i++)
		if (p[i]>=p[Max]) Max=i;
	if (Max==1) { puts("0");return 0;}
	ll Min=1LL<<60;
	for (int i=max(1,p[1]);i<=n;i++)
	{
		for (int j=2;j<=m;j++) P[j]=p[j];
		for (int j=2;j<=m;j++)
			for (int k=0;k<q[j].size();k++) vis[j][k]=0;
		bool flag=1;
		ll ans=0;
		int num=0;
		for (int j=2;j<=m;j++)
		if (P[j]>=i)
		{
			int now=0;
			while (P[j]>=i)
			{
				if (now>q[j].size()) { flag=0;break;}
				vis[j][now]=1;
				ans+=q[j][now++].y;
				num++;
				P[j]--;
				if (p[1]+num>i) { flag=0;break;}
			}
			if (!flag) break;
		}
		if (!flag) continue;
		if (p[1]+num<i)
		{
			int cnt=0;
			for (int j=2;j<=m;j++)
			{
				for (int now=0;now<q[j].size();now++)
					if (!vis[j][now]) A[++cnt]=q[j][now].y;
			}
			sort(A+1,A+cnt+1);
			for (int j=1;j<=cnt&&p[1]+num<i;j++) ans+=A[j],num++;
		}
		if (p[1]+num!=i) flag=0;
		if (flag) Min=min(Min,ans);
	}
	printf("%I64d\n",Min);
	return 0;
}
