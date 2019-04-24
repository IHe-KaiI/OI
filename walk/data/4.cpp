
#include<bits/stdc++.h>
#define ll long long
#define mo 998244353
using namespace std;
int n,m,f[2][100010],T;
vector<int>E[100010];
char s[100010];
void Add(int &x,int y)
{
	x+=y;
	if (x>=mo) x-=mo;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		E[x].push_back(y);
		E[y].push_back(x);
	}
	scanf("%s",s);
	int Len=strlen(s);
	for (int i=Len-1;i>=0;i--) T=T*2+s[i]-'0';
	f[0][1]=1;
	int ans=1,now=0;
	for (int i=1;i<=T;i++)
	{
		now^=1;
		for (int j=1;j<=n;j++) f[now][j]=f[now^1][j];
		for (int j=1;j<=n;j++)
			for (int k=0;k<(int)E[j].size();k++) Add(f[now][E[j][k]],f[now^1][j]);
		for (int j=1;j<=n;j++) Add(ans,f[now][j]);
	}
	printf("%d\n",ans);
	return 0;
}
