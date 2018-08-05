#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define mo 998244353
using namespace std;
char s[200010];
int f[200010][4][4][2];
int main()
{
	scanf("%s",s+1);
	int len=strlen(s+1),x=0,cnt=0,ans=0;
	for (int i=1;i<=len;i++)
	{
		int y=0;
		if (s[i]=='a') y=0;
		if (s[i]=='b') y=1;
		if (s[i]=='c') y=2;
		x=(x+y)%3;
		if (i!=1&&s[i]==s[i-1]) cnt++;
	}
	if (cnt==len-1) { puts("1");return 0;}
	if (len<=3)
	{
		if (len==1) { puts("1");return 0;}
		if (len==2) { puts("2");return 0;}
		if (len==3&&!cnt&&s[1]!=s[3]) { puts("3");return 0;}
		if (len==3&&cnt==1) puts("6");
			else puts("7");
		return 0;
	}
	f[1][0][0][0]=1;
	f[1][1][1][0]=1;
	f[1][2][2][0]=1;
	for (int i=2;i<=len;i++)
		for (int j=0;j<3;j++)
			for (int k=0;k<3;k++)
				for (int l=0;l<3;l++)
				{
					(f[i][(j+l)%3][l][1]+=f[i-1][j][k][1])%=mo;
					(f[i][(j+l)%3][l][(k==l)]+=f[i-1][j][k][0])%=mo;
				}
	if (!cnt) ans++;
	for (int i=0;i<3;i++) ans=(ans+f[len][x][i][1])%mo;
	printf("%d\n",ans);
	return 0;
}
