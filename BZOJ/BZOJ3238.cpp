#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=500010;
int n,stack[N],f[N],g[N];
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
int main()
{
	scanf("%s",S.s+1);
	n=strlen(S.s+1);
	ll ans=0;
	for (int i=1;i<=n;i++)
	{
		ans+=(ll)(i-1)*i;
		ans+=(ll)i*(i-1)/2;
	}
	S.Get_SA();
	S.Get_Height();
	int top=0;
	for (int i=2;i<=n;i++) 
	{
		while (top>0&&S.height[i]<S.height[stack[top]]) f[stack[top--]]=i-1;
		stack[++top]=i;
	}
	while (top) f[stack[top--]]=n;
	top=0;
	for (int i=n;i>=2;i--)
	{
		while (top>0&&S.height[i]<=S.height[stack[top]]) g[stack[top--]]=i+1;
		stack[++top]=i;
	}		
	while (top) g[stack[top--]]=2;
	for (int i=2;i<=n;i++) ans-=(ll)S.height[i]*(ll)(f[i]-i+1)*(ll)(i-g[i]+1)*2;
	printf("%lld\n",ans);
	return 0;
}
