#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<set>
using namespace std;
const int N=100010;
int n,A[N],B[N],Min[N*2][20];
set<int>Q;
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
int query(int x,int y)
{
	int z=log(y-x+1)/log(2.0);
	return min(Min[x][z],Min[y-(1<<z)+1][z]);
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) { scanf("%d",&S.s[i]);A[i]=S.s[i];}
	sort(A+1,A+n+1);
	int Num=unique(A+1,A+n+1)-A-1;
	for (int i=1;i<=n;i++) B[i]=lower_bound(A+1,A+Num+1,S.s[i])-A;
	for (int i=1;i<=n;i++) S.s[i]=B[n-i+1];
	S.Get_SA();
	S.Get_Height();
	for (int i=2;i<=n;i++) Min[i][0]=S.height[i];
	for (int i=1;(1<<i)<=n;i++)
		for (int j=2;j<=n;j++) Min[j][i]=min(Min[j][i-1],Min[j+(1<<(i-1))][i-1]);
	puts("1");
	Q.insert(S.rank[n]);
	long long Ans=1;
	for (int i=2;i<=n;i++)
	{
		int ans=0;
		set<int>::iterator it=Q.lower_bound(S.rank[n-i+1]);
		if (it!=Q.end()) ans=query(S.rank[n-i+1]+1,*it);
		if (it!=Q.begin())
		{
			it--;
			ans=max(ans,query((*it)+1,S.rank[n-i+1]));
		}
		Ans+=i-ans;
		printf("%lld\n",Ans);
		Q.insert(S.rank[n-i+1]);
	}
	return 0;
}
