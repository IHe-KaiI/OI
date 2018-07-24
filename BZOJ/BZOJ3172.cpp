#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=2000100;
char str[1000100];
int n,len[N],pos[N];
struct SA
{
	int s[N],cnta[N],sa[N],rank[N*2],a[N],b[N],cntb[N],tsa[N],height[N];
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
}S;
int main()
{
	int T;
	scanf("%d",&T);
	n=0;
	for (int i=1;i<=T;i++)
	{
		scanf("%s",str+1);
		len[i]=strlen(str+1);
		pos[i]=n+1;
		for (int j=1;j<=len[i];j++) S.s[++n]=str[j];
		S.s[++n]=' ';
	}
	S.Get_SA();
	S.Get_Height();
	for (int i=1;i<=T;i++)
	{
		int ans=0,j;
		for (j=S.rank[pos[i]];j>=2;j--) if (S.height[j]<len[i]) break;
		ans+=S.rank[pos[i]]-j;
		for (j=S.rank[pos[i]]+1;j<=n;j++) if (S.height[j]<len[i]) break;
		ans+=j-S.rank[pos[i]];
		printf("%d\n",ans);
	}
	return 0;
}
