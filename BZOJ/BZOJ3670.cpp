#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 1000000007
using namespace std;
int T,n,fail[1001000],Next[1001000],num[1001000];
char s[1001000];
void Get_Next()
{
	fail[0]=-1;
	for (int i=1;i<=n;i++)
	{
		int id=fail[i-1];
		while (id!=-1&&s[i]!=s[id+1]) id=fail[id];
		fail[i]=id+1;
		num[i]=num[fail[i]]+1;
	}
}
void Get_Ans()
{
	Next[0]=-1;
	for (int i=1;i<=n;i++)
	{
		int id=Next[i-1];
		if ((id+1)*2>i) id=fail[id];
		while (id!=-1&&s[i]!=s[id+1]) id=fail[id];
		Next[i]=id+1;
	}
}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%s",s+1);
		n=strlen(s+1);
		Get_Next();
		Get_Ans();
		ll ans=1;
		for (int i=1;i<=n;i++)
			ans=ans*(num[Next[i]]+1)%mo;
		printf("%lld\n",ans);
	}
	return 0;
}
