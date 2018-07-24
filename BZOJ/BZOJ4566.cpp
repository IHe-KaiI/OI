#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=200100;
char s1[N],s2[N],s[N*2];
int n,cnta[N*2],cntb[N*2],sa[N*2],rank[N*4],a[N*2],b[N*2],tsa[N*2],height[N*2],g[N*2],f[N*2],A[N*2],B[N*2];
void Get_SA()
{
	for (int i=0;i<=256;i++) cnta[i]=0;
	for (int i=1;i<=n;i++) cnta[(int)s[i]]++;
	for (int i=1;i<=256;i++) cnta[i]+=cnta[i-1];
	for (int i=n;i>=1;i--) sa[cnta[(int)s[i]]--]=i;
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
bool cmp(int a,int b) { return height[a]>height[b];}
int get(int x)
{
	if (f[x]==x) return x;else f[x]=get(f[x]);
	return f[x];
}
int main()
{
	scanf("%s",s1+1);
	int len1=strlen(s1+1);
	scanf("%s",s2+1);
	int len2=strlen(s2+1);
	n=len1+len2+1;
	for (int i=1;i<=n;i++)
	if (i==len1+1) { s[i]=27;continue;}
		else s[i]=(i<=len1)?s1[i]-'a'+1:s2[i-len1-1]-'a'+1;
	Get_SA();
	Get_Height();
	for (int i=1;i<=n;i++)
	{
		g[i]=i+1;
		f[i]=i;
		if (sa[i]<=len1) A[i]=1;
		if (sa[i]>len1+1) B[i]=1;
	}
	sort(g+1,g+n,cmp);
	ll ans=0;
	for (int i=1;i<=n-1;i++)
	{
		int x=get(g[i]),y=get(g[i]-1);
		ans+=((ll)A[y]*B[x]+(ll)A[x]*B[y])*height[g[i]];
		A[y]+=A[x];B[y]+=B[x];
		f[x]=y;
	}
	printf("%lld\n",ans);
	return 0;
}
