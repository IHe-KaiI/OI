#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,p[1000];
char s[100010];
int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	if (n==1) { puts("Yes");return 0;}
	for (int i=1;i<=n;i++)
	{
		if (p[s[i]-'a']) { puts("Yes");return 0;}
		p[s[i]-'a']++;
	}
	puts("No");
	return 0;
}
