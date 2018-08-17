#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,K,Stack[200010],ans[200010],p[200010];
char s[200010];
int main()
{
	scanf("%d%d",&n,&K);
	scanf("%s",s+1);
	int top=0;
	for (int i=1;i<=n;i++)
	{
		if (s[i]=='(') Stack[++top]=i;
			else if (top) p[Stack[top--]]=i;
	}
	for (int i=0,j=1;i<K;j++)
		if (p[j]) ans[j]=ans[p[j]]=1,i+=2;
	for (int i=1;i<=n;i++)
		if (ans[i]) printf("%c",s[i]);
	puts("");
	return 0;
}

