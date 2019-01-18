#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;
char S[10],s[10];
int main()
{
	scanf("%s",S);
	for (int i=1;i<=5;i++)
	{
		scanf("%s",s);
		if (s[0]==S[0]||s[1]==S[1])
		{
			puts("YES");
			return 0;
		}
	}
	puts("NO");
	return 0;
}
