#include<cstdio>
#include<cmath>
using namespace std;
int n;
double P[1<<21];
int main()
{
	scanf("%d",&n);
	for (int i=0;i<(1<<n);i++) scanf("%lf",&P[i]);
	for (int i=0;i<n;i++)
		for (int j=0;j<(1<<n);j++) if (j&(1<<i)) P[j]+=P[j^(1<<i)];
	for (int i=0;i<(1<<n);i++) if (P[i]+1e-9>1.0) P[i]=0.0;
		else P[i]=-1.0/(1.0-P[i]);
	for (int i=0;i<n;i++)
		for (int j=0;j<(1<<n);j++) if (j&(1<<i)) P[j]-=P[j^(1<<i)];
	if (P[(1<<n)-1]<1e-9) puts("INF");
		else printf("%.10lf\n",P[(1<<n)-1]);
	return 0;
}

