#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=20010;
int n,k,s[N],A[N],cnta[N],sa[N],rank[N*2],a[N],b[N],cntb[N],tsa[N],height[N];
void Get_SA()
{
	for (int i=1;i<=n;i++) cnta[i]=0;
	for (int i=1;i<=n;i++) cnta[s[i]]++;
	for (int i=1;i<=n;i++) cnta[i]+=cnta[i-1];
	for (int i=n;i>=1;i--) sa[cnta[s[i]]--]=i;
	rank[sa[1]]=1;
	for (int i=2;i<=n;i++) rank[sa[i]]=rank[sa[i-1]]+(s[sa[i]]!=s[sa[i-1]]);
	for (int i=1;rank[sa[n]]!=n;i<<=1)
	{
		for (int j=1;j<=n;j++) a[j]=rank[j],b[j]=rank[j+i];
		for (int j=0;j<=n;j++) cnta[j]=0,cntb[j]=0;
		for (int j=1;j<=n;j++) cnta[a[j]]++,cntb[b[j]]++;
		for (int j=1;j<=n;j++) cnta[j]+=cnta[j-1],cntb[j]+=cntb[j-1];
		for (int j=n;j>=1;j--) tsa[cntb[b[j]]--]=j;
		for (int j=n;j>=1;j--) sa[cnta[a[tsa[j]]]--]=tsa[j];
		rank[sa[1]]=1;
		for (int j=2;j<=n;j++) rank[sa[j]]=rank[sa[j-1]]+(a[sa[j]]!=a[sa[j-1]]||b[sa[j]]!=b[sa[j-1]]);
	}
}
void Get_Height()
{
	int len=0;
	for (int i=1;i<=n;i++)
	{
		if (len) len--;
		while (s[i+len]==s[sa[rank[i]-1]+len]) len++;
		height[rank[i]]=len;
	}
}
bool check(int x)
{
	int tot=0;
	for (int i=2;i<=n;i++)
	{
		if (height[i]>=x) tot++;else tot=0;
		if (tot>=k-1) return 1;
	}
	return 0;
}
int erfen(int l,int r)
{
	while (l<r)
	{
		int mid=(l+r+1)/2;
		if (check(mid)) l=mid;else r=mid-1;
	}
	return l;
}
int main()
{
	scanf("%d%d",&n,&k);
	int cnt=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&s[i]);
		A[++cnt]=s[i];
	}
	sort(A+1,A+cnt+1);
	cnt=unique(A+1,A+cnt+1)-A-1;
	for (int i=1;i<=n;i++) s[i]=lower_bound(A+1,A+n+1,s[i])-A;
	Get_SA();
	Get_Height();
	printf("%d\n",erfen(0,n));
	return 0;
}
