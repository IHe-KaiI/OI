#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
char S[100010],s[100010];
int n,cnt,son[100010][27],fail[100010],Q[100010],Stack[100010],danger[100010],f[100010];
void Insert(int Len)
{
	int id=1;
	for (int i=1;i<=Len;i++)
	{
		if (!son[id][s[i]-'a'+1]) son[id][s[i]-'a'+1]=++cnt;
		id=son[id][s[i]-'a'+1];
	}
	danger[id]=Len;
}
void Build_Fail()
{
	int t=0,w=1;
	Q[1]=1;fail[1]=0;
	while (t<w)
	{
		int u=Q[++t];
		for (int i=1;i<=26;i++)
		if (son[u][i])
		{
			int k=fail[u];
			fail[son[u][i]]=son[k][i];
			Q[++w]=son[u][i];
		}else son[u][i]=son[fail[u]][i];
	}
}
int main()
{
	scanf("%s",S+1);
	scanf("%d",&n);
	cnt=1;
	for (int i=1;i<=26;i++) son[0][i]=1;
	for (int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		Insert(strlen(s+1));
	}
	Build_Fail();
	int top=0,len=strlen(S+1);
	f[0]=1;
	for (int i=1;i<=len;i++)
	{
		f[i]=son[f[Stack[top]]][S[i]-'a'+1];
		Stack[++top]=i;
		top-=danger[f[i]];
	}
	for (int i=1;i<=top;i++) printf("%c",S[Stack[i]]);
	return 0;
}
