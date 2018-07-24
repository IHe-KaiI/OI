#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
char s1[1000100],s2[1000100];
int n;
int calc(char *s)
{
	int i=0,j=1,k=0;
	while (i<n&&j<n&&k<n)
	{
		if (s[(i+k)%n]==s[(j+k)%n]) { k++;continue;}
		if (s[(i+k)%n]>s[(j+k)%n]) i+=k+1;
			else j+=k+1;
		if (i==j) i++;
		k=0;
	}
	return min(i,j);
}
int main()
{
	scanf("%s",s1);
	scanf("%s",s2);
	n=strlen(s1);
	int x=calc(s1),y=calc(s2);
	for (int i=0;i<n;i++)
		if (s1[(x+i)%n]!=s2[(y+i)%n]) { puts("No");return 0;}
	puts("Yes");
	for (int i=0;i<n;i++) printf("%c",s1[(x+i)%n]);
	puts("");
	return 0;
}
