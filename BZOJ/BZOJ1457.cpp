#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int sg[105][105],flag[10010],n;
void pre()
{
	for (int i=0;i<=99;i++) sg[0][i]=sg[i][0]=sg[i][i]=0;
	int cnt=0;
	for (int i=1;i<=99;i++)
		for (int j=1;j<=99;j++)
		{
			if (i==j) continue;
			cnt++;
			for (int k=1;i-k>0||j-k>0;k++)
			{
				if (i-k>0&&i-k!=j) flag[sg[i-k][j]]=cnt;
				if (j-k>0&&i!=j-k) flag[sg[i][j-k]]=cnt;
				if (i-k>0&&j-k>0) flag[sg[i-k][j-k]]=cnt;
			}
			for (int k=0;k<=10000;k++)
				if (flag[k]!=cnt) { sg[i][j]=k;break;}
		}
}
int main()
{
	int T;
	scanf("%d",&T);
	pre();
	while (T--)
	{
		scanf("%d",&n);
		int ans=0;
		bool flag=0;
		for (int i=1;i<=n;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			if (!x||!y||x==y) flag=1;
			ans^=sg[x][y];
		}
		if (ans||flag) puts("^o^");else puts("T_T");
	}
	return 0;
}
