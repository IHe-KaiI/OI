#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
int n,a[100050],p[100050],q[100050],L[100050],R[100050];
ll sum[100050];
bool calc(int x,int l,int r)
{ 
	if (l<=0||r>n) return 0;
	return (ll)(x+1)*x/2==sum[r]-sum[l-1];
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) { scanf("%d",&a[i]);sum[i]=sum[i-1]+a[i];}
	for (int i=1;i<=n;i++)
	{
		if (!p[a[i]]) L[i]=1;
			else L[i]=p[a[i]]+1;
		p[a[i]]=i;
	}
	for (int i=n;i>=1;i--)
	{
		if (!q[a[i]]) R[i]=n;
			else R[i]=q[a[i]]-1;
		q[a[i]]=i;
	}
	int ans=0;
	for (int i=1;i<=n;i++)
	if (a[i]==1)
	{
		int j=i,Max=1,Min=L[j];
		while (Min<=j)
		{
			Max=max(Max,a[j]);
			if (calc(Max,j,j+Max-1)) ans=max(Max,ans);
			Min=max(Min,L[j]);
			if (Min==j) break;else j--;
		}
		j=i;Max=1;Min=R[j];
		while (Min>=j)
		{
			Max=max(Max,a[j]);
			if (calc(Max,j-Max+1,j)) ans=max(Max,ans);
			Min=min(Min,R[j]);
			if (Min==j) break;else j++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
