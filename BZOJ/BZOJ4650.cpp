#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
char s[30010];
int n,f[30010],g[30010];
struct node
{
	int cnta[30010],sa[30010],rank[60010],a[30010],b[30010],cntb[30010],tsa[30010],height[30010],Min[30010][20];
	void Get_SA()
	{
		for (int i=0;i<=256;i++) cnta[i]=0;
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
			for (int j=2;j<=n;j++) rank[sa[j]]=rank[sa[j-1]]+((a[sa[j]]!=a[sa[j-1]])||(b[sa[j]]!=b[sa[j-1]]));
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
	void pre()
	{
		int x=log(n)/log(2.0)+1;
		for (int i=1;i<=n;i++) Min[i][0]=height[i];
		for (int i=1;i<=x;i++)
			for (int j=1;j<=n;j++)
			{
				Min[j][i]=Min[j][i-1];
				if (j+(1<<(i-1))<=n) Min[j][i]=min(Min[j][i],Min[j+(1<<(i-1))][i-1]);
			}
	}
	int LCP(int x,int y)
	{
		if (rank[x]>rank[y]) swap(x,y);
		x=rank[x]+1;y=rank[y];
		int z=log(y-x+1)/log(2.0);
		return min(Min[x][z],Min[y-(1<<z)+1][z]);
	}
}A,B;
int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		scanf("%s",s+1);
		n=strlen(s+1);
		memset(A.rank,0,sizeof(A.rank));
		memset(A.sa,0,sizeof(A.sa));
		A.Get_SA();
		A.Get_Height();
		A.pre();
		for (int i=1;i<=n/2;i++) swap(s[i],s[n-i+1]);
		memset(B.rank,0,sizeof(B.rank));
		memset(B.sa,0,sizeof(B.sa));
		B.Get_SA();
		B.Get_Height();
		B.pre();
		for (int i=1;i<=n/2;i++) swap(s[i],s[n-i+1]);
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		for (int i=1;i<=n;i++)
		{
			for (int j=i;j+i<=n;j+=i)
			if (s[j]==s[j+i])
			{
				int x=min(j+i-1,j+A.LCP(j,j+i)-1),y=max(j+1,j+i-B.LCP(n-j-i+1,n-j+1)+1);
				if (x>=y-1)
				{
					f[y-1+i]++;f[x+1+i]--;
					g[y-i]++;g[x-i+2]--;
				}
			}
		}
		for (int i=1;i<=n;i++) f[i]+=f[i-1],g[i]+=g[i-1];
		long long ans=0;
		for (int i=1;i<=n-1;i++) ans+=(long long)f[i]*g[i+1];
		printf("%lld\n",ans);
	}
	return 0;
}
