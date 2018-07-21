#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=100100;
char s[N];
int len,cnta[N],cntb[N],sa[N],Rank[N*2],a[N],b[N],tsa[N],height[N];
void Get_SA()
{
	for (int i=0;i<=26;i++) cnta[i]=0;
	for (int i=1;i<=len;i++) cnta[s[i]-'a'+1]++;
	for (int i=1;i<=26;i++) cnta[i]+=cnta[i-1];
	for (int i=1;i<=len;i++) sa[cnta[s[i]-'a'+1]--]=i;
	Rank[sa[1]]=1;
	for (int i=2;i<=len;i++) Rank[sa[i]]=Rank[sa[i-1]]+(s[sa[i]]!=s[sa[i-1]]);
	for (int i=1;Rank[sa[len]]!=len;i<<=1)
	{
		for (int j=0;j<=len;j++) cnta[j]=cntb[j]=0;
		for (int j=1;j<=len;j++) a[j]=Rank[j],b[j]=Rank[i+j];
		for (int j=1;j<=len;j++) cnta[a[j]]++,cntb[b[j]]++;
		for (int j=1;j<=len;j++) cnta[j]+=cnta[j-1],cntb[j]+=cntb[j-1];
		for (int j=len;j>=1;j--) tsa[cntb[b[j]]--]=j;
		for (int j=len;j>=1;j--) sa[cnta[a[tsa[j]]]--]=tsa[j];
		Rank[sa[1]]=1;
		for (int j=2;j<=len;j++) Rank[sa[j]]=Rank[sa[j-1]]+(a[sa[j]]!=a[sa[j-1]]||b[sa[j]]!=b[sa[j-1]]);
	}
}
void Get_Height()
{
	int l=0;
	for (int i=1;i<=len;i++)
	{
		if (l) l--;
		while (s[i+l]==s[sa[Rank[i]-1]+l]) l++;
		height[Rank[i]]=l;
	}
}
int main()
{
	scanf("%s",s+1);
	len=strlen(s+1);
	Get_SA();
	Get_Height();
	for (int i=1;i<=len;i++) printf("%d%c",sa[i]," \n"[i==len]);
	for (int i=2;i<=len;i++) printf("%d%c",height[i]," \n"[i==len]);
	return 0;
}
