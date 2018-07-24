#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=300100;
int n,A[N],f[N],pos[N];
ll Max[N],Max1[N],Min[N],Min1[N],Num[N],ans[N],Max_ans[N];
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
			for (int j=2;j<=n;j++) 
				rank[sa[j]]=rank[sa[j-1]]+(a[sa[j]]!=a[sa[j-1]]||b[sa[j]]!=b[sa[j-1]]);
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
bool cmp(int x,int y) { return S.height[x]>S.height[y];}
int get(int x)
{
	if (f[x]==x) return x;else f[x]=get(f[x]);
	return f[x];
}
int main()
{
	scanf("%d",&n);
	scanf("%s",S.s+1);
	for (int i=1;i<=n;i++) scanf("%d",&A[i]);
	S.Get_SA();
	S.Get_Height();
	for (int i=1;i<=n;i++)
	{
		f[i]=i;
		Max[i]=A[S.sa[i]];Max1[i]=-1LL<<30;
		Min[i]=A[S.sa[i]];Min1[i]=1LL<<30;
		Num[i]=1;
		pos[i]=i+1;
	}
	for (int i=0;i<=n;i++) Max_ans[i]=-1LL<<60;
	sort(pos+1,pos+n,cmp);
	for (int i=1;i<=n-1;i++)
	{
		int x=get(f[pos[i]]),y=get(f[pos[i]-1]);
		if (Max[y]>Max[x]) Max1[x]=Max[x],Max[x]=Max[y];else if (Max[y]>Max1[x]) Max1[x]=Max[y];
		if (Max1[y]>Max1[x]) Max1[x]=Max1[y];
		if (Min[y]<Min[x]) Min1[x]=Min[x],Min[x]=Min[y];else if (Min[y]<Min1[x]) Min1[x]=Min[y];
		if (Min1[y]<Min1[x]) Min1[x]=Min1[y];
		ans[S.height[pos[i]]]+=Num[y]*Num[x];
		Num[x]+=Num[y];
		if (Max1[x]!=-1LL<<30) Max_ans[S.height[pos[i]]]=max(Max_ans[S.height[pos[i]]],Max[x]*Max1[x]);
		if (Min1[x]!=1LL<<30) Max_ans[S.height[pos[i]]]=max(Max_ans[S.height[pos[i]]],Min[x]*Min1[x]);
		Max_ans[S.height[pos[i]]]=max(Max_ans[S.height[pos[i]]],Max[x]*Max1[x]);
		f[y]=x;
	}
	for (int i=n-1;i>=0;i--) ans[i]+=ans[i+1],Max_ans[i]=max(Max_ans[i],Max_ans[i+1]);
	for (int i=0;i<=n-1;i++)
		printf("%lld %lld\n",ans[i],(Max_ans[i]!=-1LL<<60)?Max_ans[i]:0LL);
	return 0;
}
