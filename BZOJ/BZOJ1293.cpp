#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,k,f[62];
struct node{int x,id;}p[1000100];
bool cmp(node a,node b) { return a.x<b.x;}
int main()
{
	scanf("%d%d",&n,&k);
	int cnt=0;
	for (int i=1;i<=k;i++)
	{
		int x,y;
		scanf("%d",&x);
		for (int j=1;j<=x;j++)
		{
			scanf("%d",&y);
			p[++cnt]=(node){y,i};
		}
	}
	sort(p+1,p+n+1,cmp);
	int head=1,ans=(1LL<<31)-1,num=0;
	for (int i=1;i<=n;i++)
	{
		f[p[i].id]++;
		if (f[p[i].id]>1)
		{
			while (f[p[head].id]>1) f[p[head].id]--,head++;
		}else num++;
		if (num==k) ans=min(ans,p[i].x-p[head].x);
	}
	printf("%d\n",ans);
	return 0;
}
