#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,m;
char s[100010],t[100010];
int GCD(int a,int b) { return (!b)?a:GCD(b,a%b);}
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	scanf("%s",t+1);
	int gcd=GCD(n,m),a=n/gcd,b=m/gcd;
	for (int i=1,j=1;i<=n&&j<=m;i+=a,j+=b)
	{
		if (s[i]!=t[j]) { puts("-1");return 0;}
	}
	printf("%lld\n",(long long)n*m/gcd);
	return 0;
}
