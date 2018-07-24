#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
char s[1000100];
int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1);
	int num=0,tot=0;
	for (int i=1;i<=n;i++)
	{
		if (s[i]=='(') num++;
			else num--;
		if (num<0) tot++,num+=2;
	}
	tot+=num/2;
	printf("%d\n",tot);
	return 0;
}
