#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#define mo 1000000007
using namespace std;
const int N=2000010;
char S[N],s[N];
int n,RL[N],f[N],vis[N];
vector<int>P[N],E[N];
int get(int x)
{
	if (f[x]==x) return x;else f[x]=get(f[x]);
	return f[x];
}
void Union(int x,int y)
{
	int X=get(x),Y=get(y);
	if (X!=Y) f[X]=Y;
}
void manacher()
{
	int MaxRight=0,pos=0;
	for (int i=1;i<=(n<<1|1);i++)
	{
		if (i<=MaxRight) RL[i]=min(MaxRight-i,RL[pos+pos-i]);
		while (s[i-RL[i]-1]==s[i+RL[i]+1]) { Union(i-RL[i]-1,i+RL[i]+1);RL[i]++;}
		P[i-RL[i]-1].push_back(i+RL[i]+1);
		P[i+RL[i]+1].push_back(i-RL[i]-1);
		if (i+RL[i]>MaxRight) MaxRight=i+RL[i],pos=i;
	}
}
int main()
{
	scanf("%s",S+1);
	n=strlen(S+1);
	s[0]='!';s[1]='#';
	for (int i=1;i<=n;i++) s[i<<1]=S[i],s[i<<1|1]='#';
	for (int i=1;i<=(n<<1|1);i++) f[i]=i;
	manacher();
	for (int i=1;i<=n;i++)
	{
		int u=i<<1;
		for (int j=0;j<P[u].size();j++)
			if (P[u][j]%2==0&&P[u][j]>0&&P[u][j]<(n+n+2)) E[get(u)].push_back(get(P[u][j]));
	}
	int cnt=0,ans=1;
	for (int i=1;i<=n;i++)
	{
		int x=i<<1,tot=0;
		if (f[x]!=x) continue;
		cnt++;
		for (int j=0;j<E[x].size();j++)
		{
			int y=E[x][j];
			if (vis[y]!=cnt&&y>=x) vis[y]=cnt,tot++;
		}
		ans=(long long)ans*(26-tot)%mo;
	}
	printf("%d\n",ans);
	return 0;
}
