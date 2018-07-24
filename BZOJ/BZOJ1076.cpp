#include<cstdio>
#include<algorithm>
using namespace std;
const int N=16;
int K,n,A[N],S[N];
double f[110][1<<N];
int main()
{
	scanf("%d%d",&K,&n);
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&A[i]);
		while (1)
		{
			scanf("%d",&x);
			if (!x) break;
			S[i]|=1<<(x-1);
		}
	}
	for (int i=K;i>=1;i--)
	{
		for (int sta=0;sta<(1<<n);sta++)
		{
			for (int k=0;k<n;k++)
				if ((S[k+1]&sta)==S[k+1]) 
					f[i][sta]+=max(f[i+1][sta],f[i+1][sta|(1<<k)]+A[k+1]);
				else f[i][sta]+=f[i+1][sta];
			f[i][sta]/=n;
		}
	}
	printf("%.6lf\n",f[1][0]);
	return 0;
}
