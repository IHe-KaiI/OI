#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,id[6010],a[6010],b[6010],p[2];
char s[6010];
string f[6010],g[6010];
int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	int numa=0,numb=0;
	for (int i=1;i<=n+n;i++)
		if (s[i]=='a') id[i]=++numa,a[numa]=i;
			else id[i]=++numb,b[numb]=i;
	int now=0;
	f[0]="";
	for (int i=n+n,j;i>=1;i=j-1)
	{
		j=i;
		p[0]=p[1]=0;
		p[s[j]-'a']=1;
		while (p[0]!=p[1]) p[s[--j]-'a']++;
		f[++now]="";
		if (s[j]=='a')
		{
			int k=j;
			while (k<=i)
			{
				if (s[k]=='b') { k++;continue;}
				f[now]=f[now]+"ab";
				k=b[id[k]]+1;
			}
		}else
		{
			int S=id[j],T=id[i];
			for (int k=T;k>=S;k--)
			{
				int x=k;
				g[k]="";
				while (x<T&&b[x+1]<a[x]) x++;
				for (int l=j;l<=i;l++)
					if (id[l]>=k&&id[l]<=x) g[k]=g[k]+s[l];
				if (x+1<=T) g[k]=g[k]+g[x+1];
				if (k+1<+T) g[k]=max(g[k],g[k+1]);
			}
			f[now]=g[S];

		}
		f[now]=max(f[now]+f[now-1],f[now-1]);
	}
	printf("%s\n",f[now].c_str());
	return 0;
}
