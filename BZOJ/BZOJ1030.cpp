#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 10007
using namespace std;
int n,m,cnt,son[5005][27],danger[5005],Q[5005],fail[5005],f[105][5005];
char s[105];
void Insert(int Len)
{
	int id=1;
	for (int i=1;i<=Len;i++)
	{
		if (!son[id][s[i]-'A'+1]) son[id][s[i]-'A'+1]=++cnt;
		id=son[id][s[i]-'A'+1];
	}
	danger[id]=1;
}
void Build_Fail()
{
	int t=0,w=1;
	Q[1]=1;fail[1]=0;
	while (t<w)
	{
		int now=Q[++t];
		for (int i=1;i<=26;i++)
		if (son[now][i])
		{
			int j=fail[now];
			while (!son[j][i]) j=fail[j];
			fail[son[now][i]]=son[j][i];
			Q[++w]=son[now][i];
		}
		danger[now]|=danger[fail[now]];
	}
}
void DP(int x)
{
	for (int i=1;i<=cnt;i++)
	if (!danger[i]&&f[x-1][i])
	{
		for (int j=1;j<=26;j++)
		{
			int id=i;
			while (!son[id][j]) id=fail[id];
			(f[x][son[id][j]]+=f[x-1][i])%=mo;
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	cnt=1;
	for (int i=1;i<=26;i++) son[0][i]=1;
	for (int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		Insert(strlen(s+1));
	}
	Build_Fail();
	f[0][1]=1;
	for (int i=1;i<=m;i++) DP(i);
	int ans=1;
	for (int i=1;i<=m;i++) ans=ans*26%mo;
	for (int i=1;i<=cnt;i++) if (!danger[i]) ans=(ans-f[m][i]+mo)%mo;
	printf("%d\n",ans);
	return 0;
}
