#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
char s[200010];
int f[200010];
int main()
{
	scanf("%s",s+1);
	int len=strlen(s+1),ans=1;
	for (int i=1;i<=len;i++) s[i+len]=s[i];
	f[1]=1;
	for (int i=2;i<=len+len;i++)
	{
		f[i]=(s[i]==s[i-1])?1:f[i-1]+1;
		ans=min(len,max(ans,f[i]));
	}
	printf("%d\n",ans);
	return 0;
}

