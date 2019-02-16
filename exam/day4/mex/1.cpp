#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 998244353
using namespace std;
int o,ans[20000100],n,L[70010],R[70010],Q;
int main()
{
	freopen("mex.in","r",stdin);
	freopen("mex.out","w",stdout);
	int Max=0,last=0;
	ans[1]=2;ans[2]=5;
	scanf("%d%d",&o,&Q);
	for (int i=1;i<=Q;i++) scanf("%d%d",&L[i],&R[i]),Max=max(Max,R[i]);
	for (n=3;n<=Max;n++)
	{
		for (int i=max(1,last-5);i<=n;i++)
		{
			int X;
			if (ceil((double)n/(i+1))==n/(i+1)) X=n/(i+1)+1;
				else X=ceil((double)n/(i+1));
			if (n/i<X) { ans[n]=i;last=i;break;}
		}
		ans[n]=(ans[n]+ans[n-1])%mo;
	}
	for (int i=1;i<=Q;i++) printf("%d\n",(ans[R[i]]-ans[L[i]-1]+mo)%mo);
	return 0;
}

