#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#define ll long long
using namespace std;
int n,k;
ll a[100010];
struct node{ll x;int y;};
struct cmp
{
	bool operator () (node a,node b)
	{
		return (a.x==b.x)?a.y>b.y:a.x>b.x;
	}
};
priority_queue<node,vector<node>,cmp>Q;
int main()
{
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		Q.push((node){a[i],1});
	}
	if ((n-1)%(k-1))
	{
		for (int i=1;i<=k-1-(n-1)%(k-1);i++) Q.push((node){0,1});
	}
	int Max=0;
	ll ans=0;
	while (Q.size()!=1)
	{
		ll tmp=0;
		int MAX=0;
		for (int i=1;i<=k;i++)
		{
			if (Q.empty()) break;
			node t=Q.top();
			Q.pop();
			tmp+=t.x;
			MAX=max(MAX,t.y);
		}
		ans+=tmp;
		Max=max(Max,MAX);
		Q.push((node){tmp,MAX+1});
	}
	printf("%lld\n%d\n",ans,Max);
	return 0;
}
