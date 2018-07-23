#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
char s[100],A[100];
ll f[100][100];
int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	ll ans=0;
	for (int i=0;i<(1<<n);i++)
	{
		int cnt=0;
		for (int j=1;j<=n;j++)
			if (!(i&(1<<j-1))) A[++cnt]=s[j];
		int red=cnt;
		for (int j=n;j>=1;j--)
			if (i&(1<<j-1)) A[++cnt]=s[j];
		for (int j=1;j<=n;j++) cout<<A[j];
		puts("");
		f[0][0]=1;
		for (int j=1;j<=n;j++)
			for (int k=0;k<=j;k++)
			{
				f[j][k]=0;
				if (k!=0&&s[n+j]==A[k])
					f[j][k]+=f[j-1][k-1];
				if (j!=k&&s[n+j]==A[n-(j-k)+1])
					f[j][k]+=f[j-1][k];
			}
		ans+=f[n][red];
	}
	printf("%lld\n",ans);
	return 0;
}
