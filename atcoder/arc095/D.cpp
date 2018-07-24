#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[100010];
double Abs(double x) { return (x>0)?x:-x;}
int main()
{
	scanf("%d",&n);
	int Max=-1<<29,x=-1<<29;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		Max=max(Max,a[i]);
	}
	for (int i=1;i<=n;i++)
		if (a[i]!=Max&&Abs((double)Max/2-a[i])<=Abs((double)Max/2-x)) x=a[i];
	printf("%d %d\n",Max,x);
	return 0;
}
