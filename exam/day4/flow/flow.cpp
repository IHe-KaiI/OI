#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int o,T,n,A,B;
int main()
{
	freopen("flow.in","r",stdin);
	freopen("flow.out","w",stdout);
	scanf("%d",&o);
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d%d",&n,&A,&B);
		if (n==1)
		{
			if (A==0&&B==0) puts("1");
				else puts("0");
			continue;
		}
		if (n==2&&((A&1)||((!A)&&(B&1))))
		{
			puts("0");
			continue;
		}
		bool flag=0;
		for (int i=0;i<=A;i++)
		if (A-i<=B+B)
		{
			int x=A-i,y=(B+B-x)/2;
			if ((B+B-x)&1) continue;
			if (!x&&i<n&&y<n) continue;
			if ((i==1&&A==1)||(y==1&&B==1)) continue;
			if (i+x+y>=n)
			{
				if (i+x+y==n+1&&i+y>n) continue;
				flag=1;
				break;
			}
		}
		if (flag) puts("1");else puts("0");
	}
	return 0;
}
