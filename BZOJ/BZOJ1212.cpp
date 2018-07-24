#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,m,cnt,son[1000100][26],danger[1000100],Q[1000100],fail[1000100],f[1000100];
char s[1000100];
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
			while (!son[k][i]) k=fail[k];
			fail[son[u][i]]=son[k][i];
			Q[++w]=son[u][i];
		}
	}
}
void Work(int Len)
{
	int id=1;
	for (int i=1;i<=Len;i++)
	{
		while (!son[id][s[i]-'a'+1]) id=fail[id];
		id=son[id][s[i]-'a'+1];
		for (int j=id;j;j=fail[j])
			if (danger[j]) f[i]|=f[i-danger[j]];
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
	for (int i=1;i<=m;i++)
	{
		scanf("%s",s+1);
		memset(f,0,sizeof(f));
		f[0]=1;
		int len=strlen(s+1);
		Work(len);
		for (int j=len;j>=0;j--)
			if (f[j]) { printf("%d\n",j);break;}
	}
	return 0;
}
