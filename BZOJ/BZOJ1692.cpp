#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=60050;
int n;
struct SA
{
	char s[N];
	int cnta[N],sa[N],rank[N*2],a[N],b[N],cntb[N],tsa[N],height[N];
	void Get_SA()
	{
	    for (int i=1;i<=256;i++) cnta[i]=0;
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
}S;
int main()
{
	scanf("%d",&n);
	char str[10];
	for (int i=1;i<=n;i++)
	{
		scanf("%s",str);
		S.s[i]=str[0];
	}
	for (int i=1;i<=n;i++) S.s[n+n-i+1]=S.s[i];
	n*=2;
	S.Get_SA();
	int l=1,r=n/2;
	for (int i=1;i<=n/2;i++)
	{
		if (S.rank[l]<S.rank[n-r+1]) printf("%c",S.s[l++]);
			else printf("%c",S.s[r--]);
		if (i%80==0) puts("");
	}
	puts("");
	return 0;
}
