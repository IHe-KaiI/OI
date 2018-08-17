#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,m;
char s[200010],t[200010];
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	scanf("%s",t+1);
	int pos=0;
	for (int i=1;i<=n;i++)
		if (s[i]=='*') { pos=i;break;}
	if (!pos)
	{
		if (n!=m) { puts("NO");return 0;}
		for (int i=1;i<=n;i++)
			if (s[i]!=t[i]) { puts("NO");return 0;}
		puts("YES");
		return 0;
	}
	if (n>m+1) { puts("NO");return 0;}
	for (int i=1,j=1;i<pos;i++,j++)
		if (s[i]!=t[j]) { puts("NO");return 0;}
	for (int i=n,j=m;i>pos;i--,j--)
		if (s[i]!=t[j]) { puts("NO");return 0;}
	puts("YES");
	return 0;
}
