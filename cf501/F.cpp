#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define mo 1000000007
using namespace std;
int n,len,fail[210],Go[210];
char s[210];
ll f[210][210][210][2];
void Add(ll  &x,ll y) { x=(x+y)%mo;}
void pre()
{
	fail[0]=-1;
	for (int i=1;i<=len;i++)
	{
		int id=fail[i-1];
		while (id!=-1&&s[i]!=s[id+1]) id=fail[id];
		fail[i]=id+1;
	}
	for (int i=1;i<=len-1;i++)
	{
		int id=fail[i];
		while (id!=-1&&s[id+1]==s[i+1]) id=fail[id];
		Go[i]=id+1;
	}
}
int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	len=strlen(s+1);
	pre();
	f[0][0][0][0]=1;
	for (int i=0;i<n+n;i++)
		for (int j=0;j<=min(i,n);j++)
			for (int k=0;k<=len;k++)
			{
				int A=f[i][j][k][0],B=f[i][j][k][1];
				if (k==len)
				{
					Add(f[i+1][j+1][k][1],B);
					if (j>0) Add(f[i+1][j-1][k][1],B);
					continue;
				}
				if (s[k+1]=='(')
				{
					Add(f[i+1][j+1][k+1][(k+1==len)],A);
					Add(f[i+1][j-1][Go[k]][0],A);
				}else
				{
					Add(f[i+1][j+1][Go[k]][0],A);
					Add(f[i+1][j-1][k+1][(k+1==len)],A);
				}
			}
	printf("%lld\n",f[n+n][0][len][1]);
	return 0;
}
