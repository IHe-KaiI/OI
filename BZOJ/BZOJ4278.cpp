#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=400100;
int len1,s[N],len2,n,cnta[N],sa[N],rank[N*2],a[N],b[N],cntb[N],tsa[N];
void Get_SA()
{
	for (int i=0;i<=1010;i++) cnta[i]=0;
	for (int i=1;i<=n;i++) cnta[s[i]]++;
	for (int i=1;i<=1010;i++) cnta[i]+=cnta[i-1];
	for (int i=n;i>=1;i--) sa[cnta[s[i]]--]=i;
	rank[sa[1]]=1;
	for (int i=1;i<=n;i++) rank[sa[i]]=rank[sa[i-1]]+(s[sa[i]]!=s[sa[i-1]]);
	for (int i=1;rank[sa[n]]!=n;i<<=1)
	{
		for (int j=1;j<=n;j++) a[j]=rank[j],b[j]=rank[j+i];
		for (int j=0;j<=n;j++) cnta[j]=0,cntb[j]=0;
		for (int j=1;j<=n;j++) cnta[a[j]]++,cntb[b[j]]++;
		for (int j=1;j<=n;j++) cnta[j]+=cnta[j-1],cntb[j]+=cntb[j-1];
		for (int j=n;j>=1;j--) tsa[cntb[b[j]]--]=j;
		for (int j=n;j>=1;j--) sa[cnta[a[tsa[j]]]--]=tsa[j];
		rank[sa[1]]=1;
		for (int i=1;i<=n;i++) rank[sa[i]]=rank[sa[i-1]]+(a[sa[i]]!=a[sa[i-1]]||b[sa[i]]!=b[sa[i-1]]);
	}
}
int main()
{
	scanf("%d",&len1);
	for (int i=1;i<=len1;i++) scanf("%d",&s[i]);
	s[len1+1]=1001;
	scanf("%d",&len2);
	for (int i=1;i<=len2;i++) scanf("%d",&s[len1+i+1]);
	n=len1+len2+2;
	s[n]=1001;
	Get_SA();
	int l=1,r=len1+2;
	for (int i=1;i<=n-2;i++)
	{
		if (rank[l]<rank[r]) printf("%d%c",s[l++]," \n"[i==n]);
			else printf("%d%c",s[r++]," \n"[i==n]);
	}
	return 0;
}
