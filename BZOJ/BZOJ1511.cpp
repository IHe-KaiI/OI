#include<bits/stdc++.h>
using namespace std;
int n,fail[1000100],f[1000100];
char s[1000100];
int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	fail[0]=-1;
	for (int i=1;i<=n;i++)
	{
		int id=fail[i-1];
		while (id!=-1&&s[id+1]!=s[i]) id=fail[id];
		fail[i]=id+1;
	}
	long long ans=0;
	for (int i=1;i<=n;i++)
	{
		if (fail[i]) f[i]=fail[i];
		if (f[fail[i]]!=0) f[i]=min(f[fail[i]],fail[i]);
		if (f[i]) ans+=i-f[i];
	}
	printf("%lld\n",ans);
	return 0;
}
