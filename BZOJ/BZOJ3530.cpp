#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 1000000007
#define ll long long
using namespace std;
char s[1500],S[1500];
int n,m,cnt,a[1510][10],danger[15100],Q[15100],fail[15100];
ll f[1500][1510][2][2];
void Insert(int len)
{
	int id=1;
	for (int i=1;i<=len;i++)
	{
		if (!a[id][S[i]-'0']) a[id][S[i]-'0']=++cnt;
		id=a[id][S[i]-'0'];
	}
	danger[id]=1;
}
void build_fail()
{
	fail[1]=0;
	for (int i=0;i<=9;i++) a[0][i]=1;
	int t=0,w=1;
	Q[1]=1;
	while (t<w)
	{
		int u=Q[++t];
		for (int i=0;i<=9;i++)
		if (a[u][i])
		{
			fail[a[u][i]]=a[fail[u]][i];
			Q[++w]=a[u][i];
		}else a[u][i]=a[fail[u]][i];
		danger[u]|=danger[fail[u]];
	}
}
ll dp(int len,int id,bool x,bool limit)
{
	if (!len) return !x;
	if (f[len][id][x][limit]!=-1) return f[len][id][x][limit];
	int up=(limit)?(s[n-len+1]-'0'):9;
	ll ans=0;
	for (int i=0;i<=up;i++)
	{
		int Go=(x&&!i)?1:a[id][i];
		if (danger[Go]) continue;
		(ans+=dp(len-1,Go,x&&(i==0),limit&&(i==up)))%=mo;
	}
	f[len][id][x][limit]=ans;
	return ans;
}
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	scanf("%d",&m);
	cnt=1;
	for (int i=1;i<=m;i++)
	{
		scanf("%s",S+1);
		int len=strlen(S+1);
		Insert(len);
	}
	build_fail();
	memset(f,-1,sizeof(f));
	printf("%lld\n",dp(n,1,1,1));
	return 0;
}
