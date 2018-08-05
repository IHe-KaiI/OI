#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int T,Case,n,m,num[100010][27];
char s[100010];
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d",&n,&m);
		scanf("%s",s+1);
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=26;j++) num[i][j]=num[i-1][j];
			num[i][s[i]-'A'+1]++;
		}
		printf("Case #%d:\n",++Case);
		for (int i=1;i<=m;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			for (int j=1;j<=26;j++)
			if (num[y][j]-num[x-1][j]!=0)
			{
				printf("%d\n",num[y][j]-num[x-1][j]);
				break;
			}
		}
	}
	return 0;
}
