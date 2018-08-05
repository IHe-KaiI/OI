#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,K,a[1010],vis[2000];
char s[100];
int main()
{
	int T,Case=0;
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d%d",&n,&m,&K);
		for (int i=1;i<=n;i++)
		{
			scanf("%s",s+1);
			a[i]=0;
			for (int j=1;j<=m;j++) a[i]=a[i]<<1|(s[j]=='A');
		}
		for (int i=0;i<=(1<<m)-1;i++) vis[i]=0;
		int ans=0;
		for (int i=0;i<=(1<<m)-1;i++)
		{
			int cnt=0;
			for (int j=1;j<=n;j++) vis[a[j]&i]++;
			for (int j=0;j<=(1<<m)-1;j++)
			{
				cnt+=vis[j]*(n-vis[j]);
				vis[j]=0;
			}
			if (cnt/2>=K) ans++;
		}
		printf("Case #%d: %d\n",++Case,ans);
	}
	return 0;
}
