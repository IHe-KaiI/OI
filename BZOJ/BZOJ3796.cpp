#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=110010;
char s1[50010],s2[50010],s3[10010];
int n,Min[N*4][20],f[N],A[N];
bool P[N];
struct SA
{
	int s[N],cnta[N],sa[N],rank[N*2],a[N],b[N],cntb[N],tsa[N],height[N];
	void Get_SA()
	{
	    for (int i=1;i<=256;i++) cnta[i]=0;
	    for (int i=1;i<=n;i++) cnta[s[i]]++;
	    for (int i=1;i<=256;i++) cnta[i]+=cnta[i-1];
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
	scanf("%s",s1+1);
	int len1=strlen(s1+1);
	for (int i=1;i<=len1;i++) S.s[++n]=s1[i];
	S.s[++n]=1;
	scanf("%s",s2+1);
	int len2=strlen(s2+1);
	for (int i=1;i<=len2;i++) S.s[++n]=s2[i];
	S.s[++n]=2;
	scanf("%s",s3+1);
	int len3=strlen(s3+1);
	for (int i=1;i<=len3;i++) S.s[++n]=s3[i];
	S.Get_SA();
	S.Get_Height();
	for (int i=1;i<=n;i++) Min[i][0]=S.height[i];
	for (int i=1;i<=18;i++)
		for (int j=1;j<=n;j++) Min[j][i]=min(Min[j][i-1],Min[j+(1<<(i-1))][i-1]);
	for (int i=1;i<=len1;i++)
	{
		int x=S.rank[len1+len2+3],y=S.rank[i];
		if (x>y) swap(x,y);
		if (query(x+1,y)>=len3) P[i]=1;
	}
	f[len1+1]=1<<29;
	for (int i=len1;i>=1;i--)
		if (P[i]) f[i]=i;else f[i]=f[i+1];
	for (int i=1;i<=len2;i++) A[i]=S.rank[len1+i+1];
	sort(A+1,A+len2+1);
	int ans=0;
	for (int i=1;i<=len1;i++)
	{
		int x=lower_bound(A+1,A+len2+1,S.rank[i])-A;
		int X,Ans=0;
		if (x!=len2+1)
		{
			X=query(S.rank[i]+1,A[x]);
			Ans=max(Ans,X);
		}
		if (x!=1)
		{
			x--;
			X=query(A[x]+1,S.rank[i]);
			Ans=max(Ans,X);
		}
		ans=max(ans,min(Ans,f[i]-i+len3-1));
	}
	printf("%d\n",ans);
	return 0;
}
