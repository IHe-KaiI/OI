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
int n,X[500010],Y[500010];
char s[500010];
int main()
{
	scanf("%d",&n);
	int num=0,Max=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		int len=strlen(s+1),cnt=0,last=0;
		Max=max(Max,len);
		for (int j=1;j<=len;j++)
		{
			if (s[j]=='(') cnt++;
			else
			{
				if (cnt) cnt--;
					else last++;
			}
		}
		if (!cnt&&!last) { num++;continue;}
		if (!cnt) { Y[last]++;continue;}
		if (!last) { X[cnt]++;continue;}
	}
	int ans=num/2;
	for (int i=1;i<=Max;i++)
		ans+=min(X[i],Y[i]);
	printf("%d\n",ans);
	return 0;
}


