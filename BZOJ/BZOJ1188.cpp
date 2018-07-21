#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,a[25],sg[25];
bool flag[10010];
int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		sg[n]=0;
		for (int i=n-1;i>=1;i--)
		{
			memset(flag,0,sizeof(flag));
			for (int j=i+1;j<=n;j++)
				for (int k=j;k<=n;k++) flag[sg[j]^sg[k]]=1;
			for (int j=0;j<=10000;j++)
				if (!flag[j]) { sg[i]=j;break;}
		}
		int ans=0,tot=0;
		for (int i=1;i<=n;i++)
			if (a[i]&1) ans^=sg[i];
		if (!ans) { puts("-1 -1 -1\n0");continue;}
		for (int i=1;i<=n-1;i++)
			for (int j=i+1;j<=n;j++)
				for (int k=j;k<=n;k++)
				if (a[i]>0&&(ans^sg[i]^sg[j]^sg[k])==0)
				{
					tot++;
					if (tot==1) printf("%d %d %d\n",i-1,j-1,k-1);
				}
		printf("%d\n",tot);
	}
	return 0;
}
