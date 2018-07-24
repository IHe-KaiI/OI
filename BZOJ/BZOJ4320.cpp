#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int Size=550,Max=300000;
int n,belong[Max+10],a[Size+5],f[Max+5],g[Size+5],Min[Size+5];
void update(int x)
{
	int y=belong[x];
	for (int i=1;i<=Size;i++) Min[i]=min(Min[i],x%i);
	for (int i=a[y];i<=x;i++) f[i]=min(f[i],x);
	for (int i=1;i<=y;i++) g[i]=min(g[i],x);
}
int query(int x)
{
	if (x<=Size) return Min[x];
	else
	{
		int ans=1<<29;
		for (int i=0;i<=Max;i+=x)
		{
			int j=belong[i];
			ans=min(ans,min(f[i],g[j+1])-i);
		}
		return ans;
	}
}
int main()
{
	scanf("%d",&n);
	for (int i=0;i<=Max;i++) belong[i]=i/Size+1;
	for (int i=Max;i>=0;i--) a[belong[i]]=i;
	for (int i=1;i<=Size;i++) Min[i]=1<<29;
	for (int i=0;i<=Max;i++) f[i]=1<<29;
	for (int i=1;i<=Size;i++) g[i]=1<<29;
	for (int i=1;i<=n;i++)
	{
		char s[2];int x;
		scanf("%s%d",s,&x);
		if (s[0]=='A') update(x);
			else printf("%d\n",query(x));
	}
	return 0;
}
