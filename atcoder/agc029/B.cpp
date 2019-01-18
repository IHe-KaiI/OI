#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<map>
using namespace std;
const int N=300010;
int n,a[N];
bool vis[N];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	sort(a+1,a+n+1);
	int ans=0;
	for (int i=30;i>=0;i--)
	{
		int j=n,k=1;
		while (j>=1)
		{
			if (vis[j]) { j--;continue;}
			while (k<j)
			{
				if (a[j]+a[k]>(1<<i)) break;
				if (!vis[k]&&a[j]+a[k]==(1<<i)) { vis[j]=vis[k]=1;ans++;break;}
				k++;
			}
			j--;
		}
	}
	printf("%d\n",ans);
	return 0;
}

