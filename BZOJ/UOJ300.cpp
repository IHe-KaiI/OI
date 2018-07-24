#include<cstdio>
#include<algorithm>
#define mo 1000000007
using namespace std;
int n,ans[233335];
int main()
{
	scanf("%d",&n);
	int Ans=0;
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		int t=ans[x]+1;
		Ans=(Ans+t)%mo;
		for (int j=x;j;j=(j-1)&x)
			ans[j]=(ans[j]+t)%mo;
	}
	printf("%d\n",Ans-n);
	return 0;
}
