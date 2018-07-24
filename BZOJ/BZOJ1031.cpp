#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
char s[200010];
int n,cnta[200010],sa[200010],rank[400010],a[200010],b[200010],cntb[200010],tsa[200010];
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
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	for (int i=1;i<=n;i++) s[i+n]=s[i];
	n=n*2;
	Get_SA();
	for (int i=1;i<=n;i++)
	if (sa[i]<=(n>>1)) printf("%c",s[sa[i]+(n>>1)-1]);
	puts("");
	return 0;
}
