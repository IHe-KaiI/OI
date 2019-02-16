#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int p[2000100],n;
int main()
{
	freopen("1.in","w",stdout);
	for (n=2;n<=2000000;n++)
	{
		memset(p,0,sizeof(p));
		for (int i=1,j=1;i<=n;i=j+1)
		{
			j=n/(n/i);
			p[n/i]=1;
		}
		for (int i=1;i<=n;i++)
			if (!p[i]) { printf("%d %d\n",n,i);break;}
	}
	return 0;
}
