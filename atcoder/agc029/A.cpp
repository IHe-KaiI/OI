#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=300010;
char s[N];
int a[N];
int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1);
	for (int i=n;i>=1;i--)
		a[i]=a[i+1]+(s[i]=='W');
	long long ans=0;
	for (int i=1;i<=n;i++)
		if (s[i]=='B') ans+=a[i];
	printf("%lld\n",ans);
	return 0;
}
