#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 1000000000
using namespace std;
const int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
int n,m,In[300],A[300][300],p[15][15];
char s[15][15];
int det(int n)
{
	int ans=1;
	for (int i=1;i<=n;i++)
	{
		for (int j=i+1;j<=n;j++)
		{
			while (A[j][i])
			{
				int t=A[i][i]/A[j][i];
				for (int k=i;k<=n;k++)
				{
					A[i][k]=((ll)A[i][k]-(ll)A[j][k]*t%mo+mo)%mo;
					swap(A[i][k],A[j][k]);
				}
				ans=-ans;
			}
		}
		if (!A[i][i]) return 0;
			else ans=(ll)ans*((ll)A[i][i]%mo+mo)%mo;
	}
	return (ans%mo+mo)%mo;
}
int main()
{
	scanf("%d%d",&n,&m);
	int cnt=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
		for (int j=1;j<=m;j++) if (s[i][j]=='.') p[i][j]=++cnt;
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		if (s[i][j]=='.')
		{
			for (int k=0;k<4;k++)
			{
				int x=i+dx[k],y=j+dy[k];
				if (s[x][y]=='.') A[p[i][j]][p[i][j]]++,A[p[i][j]][p[x][y]]=-1;
			}
		}
	}
	printf("%d\n",det(cnt-1));
	return 0;
}
